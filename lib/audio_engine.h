#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <pthread.h>

extern volatile int g_game_over;
extern volatile int g_score;

void init_audio();
void close_audio();
void* music_thread_func(void* arg);

#endif
