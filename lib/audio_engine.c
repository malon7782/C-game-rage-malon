#include <alsa/asoundlib.h>
#include <math.h>
#include <pthread.h>
#include "audio_engine.h"

static snd_pcm_t *pcm_handle;
static unsigned int sample_rate = 44100;

volatile int g_game_over = 0;
volatile int g_score = 0;

void init_audio() {
    snd_pcm_hw_params_t *params;
    int rc = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) { fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc)); exit(1); }
    
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, 1);
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &sample_rate, 0);
    rc = snd_pcm_hw_params(pcm_handle, params);
    if (rc < 0) { fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc)); exit(1); }
}

void close_audio() {
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
}


typedef enum { STATE_CALM, STATE_TENSE } MusicState;

const float CALM_CHORD[] = {261.63, 329.63, 392.00}; // C-E-G
const float TENSE_CHORD[] = {493.88, 587.33, 698.46}; // B-D-F (Bdim)

void generate_wave(short* buffer, const float* chord_freqs, int num_notes, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        float sample = 0.0;
        for (int j = 0; j < num_notes; j++) {
            sample += sin(2 * M_PI * chord_freqs[j] * i / sample_rate);
        }
        buffer[i] = (short)(10000 * (sample / num_notes));
    }
}

void* music_thread_func(void* arg) {
    MusicState current_state = STATE_CALM;
    int tempo_bpm = 100; 

    while (!g_game_over) {
        if (g_score >= 10 && current_state == STATE_CALM) {
            current_state = STATE_TENSE;
            tempo_bpm = 160; 
        } else if (g_score < 10 && current_state == STATE_TENSE) {
            current_state = STATE_CALM;
            tempo_bpm = 100; 
        }

        const float* current_chord = (current_state == STATE_CALM) ? CALM_CHORD : TENSE_CHORD;
        
        float beat_duration_sec = 60.0 / tempo_bpm;
        int num_samples = (int)(beat_duration_sec * sample_rate);
        short buffer[num_samples];
        generate_wave(buffer, current_chord, 3, num_samples);
        
        int rc = snd_pcm_writei(pcm_handle, buffer, num_samples);
        if (rc == -EPIPE) { 
            snd_pcm_prepare(pcm_handle);
        } else if (rc < 0) {
            fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
        }
    }
    return NULL;
}
