#include "ghost1.h"
#include "ghost2.h"
#include "ghost3.h"
#include "ghost4.h"
#include "jogo.h"

// Initializes Ghosts static attributes
int Ghost1::ghost1_x;
int Ghost1::ghost1_y;
Direction Ghost1::ghost1_dir;
int Ghost2::ghost2_x;
int Ghost2::ghost2_y;
Direction Ghost2::ghost2_dir;
int Ghost3::ghost3_x;
int Ghost3::ghost3_y;
Direction Ghost3::ghost3_dir;
int Ghost4::ghost4_x;
int Ghost4::ghost4_y;
Direction Ghost4::ghost4_dir;

int Ghost::checkPosition(int pm_t_x, int pm_t_y) {
// Checks if ghost has been eaten or if it got PacMan

    int tile_x = getNearTileX();
    int tile_y = getNearTileY();

    if (tile_x == pm_t_x && tile_y == pm_t_y) {
        _mutex.v();
        if (!_isScared) // Got PacMan
            return 1;

        else { // Was eaten
            isJailed(true);
            isScared(false);
            _x = _jail_x;
            _y = _jail_y;
            _last_input = STOPPED;
            updatePosition(_x, _y);
            updateDirection();
            switch(_jail_x) { // Starts timer for each ghost in jail
                case 265:
                    Jogo::timerJail(1); // Ghost1
                    break;
                case 298:
                    Jogo::timerJail(2); // Ghost2
                    break;
                case 331:
                    Jogo::timerJail(3); // Ghost3
                    break;
                case 365:
                    Jogo::timerJail(4); // Ghost4
                    break;
            }
            return -1;
        }
    }

    _mutex.v();
    return 0;
}
