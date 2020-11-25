#include "ghost1.h"
#include "ghost2.h"
#include "ghost3.h"
#include "ghost4.h"
#include "jogo.h"

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

// Semaphore Ghost::_mutex_scared;// = Semaphore();
int Ghost::checkPosition(int pm_t_x, int pm_t_y) {

    int tile_x = getNearTileX();
    int tile_y = getNearTileY();

    // if (tile_x != 0 && tile_y != 0)
    if (tile_x == pm_t_x && tile_y == pm_t_y) {
        // std::cout << "you lost!!!!!!!!!!!!!!!!\n";
        _mutex.v();
        if (!_isScared)
            return 1;

        else {
            isJailed(true);
            isScared(false);
            _x = _jail_x;
            _y = _jail_y;
            _last_input = STOPPED;
            updatePosition(_x, _y);
            updateDirection();
            switch(_jail_x) {
                case 265:
                    Jogo::timerJail(1); // Ghost1
                    break;
                case 298:
                    Jogo::timerJail(2); // Ghost1
                    break;
                case 331:
                    Jogo::timerJail(3); // Ghost1
                    break;
                case 365:
                    Jogo::timerJail(4); // Ghost1
                    break;
            }
            // Jogo::timerJail();
            return -1;
        }
    }

    _mutex.v();
    return 0;
}
