#include <unistd.h>
#include "ui.h"
#include "player.h"

int main() {

    ui_init();

    int yMax, xMax;
    WINDOW *game_win = create_game_window(&yMax, &xMax);

    Player p = {GAME_WIDTH / 2, GAME_HEIGHT - 2, 'M'};

    int ch;

    while ((ch = wgetch(game_win)) != 'q') {
        
        if (ch == KEY_RESIZE) {
            handle_resize(&game_win, &yMax, &xMax);
            continue;
        }
        
        if (ch != ERR) {
            switch (ch) {
                case 'a':
                    if (p.x > 1) p.x--;
                    break;
                case 'd':
                    if (p.x < GAME_WIDTH - 2) p.x++;
                    break;
                }

        }

        werase(game_win);
        box(game_win, 0, 0);
        mvwprintw(game_win, p.y, p.x, "%c", p.character);
        wrefresh(game_win);

        usleep(300000);

    }
    

    ui_cleanup(game_win);

    return 0;
}
