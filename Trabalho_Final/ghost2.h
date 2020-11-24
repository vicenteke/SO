#ifndef GHOST2_H
#define GHOST2_H

#include "ghost.h"

__USING_API

class Ghost2 : public Ghost {
public:

    Ghost2(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 254, Direction dir = RIGHT)
    : Ghost(eyes, sprites, n_sprites, x, y, dir)
    {
        getTargetTile(310, 398, LEFT);
    }

    ~Ghost2() {}

    void getTargetTile(int pm_x, int pm_y, Direction dir) {

        int tile_x = getTileX();
        int tile_y = getTileY();

        int dist = getDistance(_x, _y, pm_x, pm_y);

        _target_x = pm_x;
        _target_y = pm_y;

        // Problemas:
        // 1) Ghost trava no portal
        // 2) Dependendo da esquina em que o pacman fica parado ele vai pra muito longe ou nunca chega no pacman
        // 3) Deveria seguir diretamente o pacman, mas ta fazendo umas escolhas burras
        // 4) Nunca deveria inverter a direção (ex: da direita pra esquerda)
        if (tile_x != 0 && tile_y != 0) {
            if (getDistance(_x + 24, _y, pm_x, pm_y) < dist && maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT) {
                _last_input = RIGHT;
           } else if (getDistance(_x - 24, _y, pm_x, pm_y) < dist && maze[tile_x - 1][tile_y] != tile::W  && _last_input != RIGHT) {
                _last_input = LEFT;
            } else if (getDistance(_x, _y - 24, pm_x, pm_y) < dist && maze[tile_x][tile_y + 1] != tile::W  && _last_input != DOWN) {
                _last_input = UP;
            } else if (getDistance(_x, _y + 24, pm_x, pm_y) < dist && maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
                _last_input = DOWN;
            } else {
                if (maze[tile_x + 1][tile_y] == tile::W && _last_input == RIGHT) {
                    if (maze[tile_x][tile_y + 1] != tile::W && tile_y > _target_y) _last_input = UP;
                    else _last_input = DOWN;
                }
                else if (maze[tile_x - 1][tile_y] == tile::W && _last_input == LEFT) {
                    if (maze[tile_x][tile_y - 1] != tile::W  && tile_y < _target_y) _last_input = DOWN;
                    else _last_input = UP;
                }
                else if (maze[tile_x][tile_y - 1] == tile::W && _last_input == DOWN) {
                    if (maze[tile_x + 1][tile_y] != tile::W && tile_x < _target_x) _last_input = RIGHT;
                    else _last_input = LEFT;
                }
                else if (maze[tile_x][tile_y + 1] == tile::W && _last_input == UP) {
                    if (maze[tile_x - 1][tile_y] != tile::W && tile_x > _target_x) _last_input = LEFT;
                    else _last_input = RIGHT;
                }
            }
        }

        ghost2_dir = _last_input;

        // if (tile_x != 0 && tile_y != 0)
        //     if (tile_x < _target_x && maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT)
        //         _last_input = RIGHT;
        //     else if (tile_x >= _target_x && maze[tile_x - 1][tile_y] != tile::W && _last_input != RIGHT)
        //         _last_input = LEFT;
        //     else if (tile_y <= _target_y && maze[tile_x][tile_y - 1] != tile::W && _last_input != UP)
        //         _last_input = DOWN;
        //     else if (tile_y > _target_y && maze[tile_x][tile_y + 1] != tile::W && _last_input != DOWN)
        //         _last_input = UP;
        //     else {
        //         if (maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT) _last_input = RIGHT;
        //         else if (maze[tile_x - 1][tile_y] != tile::W && _last_input != RIGHT) _last_input = LEFT;
        //         else if (maze[tile_x][tile_y - 1] != tile::W && _last_input != UP) _last_input = DOWN;
        //         else if (maze[tile_x][tile_y + 1] != tile::W && _last_input != DOWN) _last_input = UP;
        //     }
        //     // else {
        //     //     if (maze[tile_x + 1][tile_y] == tile::W && _last_input == RIGHT) {
        //     //         if (maze[tile_x][tile_y + 1] != tile::W && tile_y > _target_y) _last_input = UP;
        //     //         else _last_input = DOWN;
        //     //     }
        //     //     else if (maze[tile_x - 1][tile_y] == tile::W && _last_input == LEFT) {
        //     //         if (maze[tile_x][tile_y - 1] != tile::W  && tile_y < _target_y) _last_input = DOWN;
        //     //         else _last_input = UP;
        //     //     }
        //     //     else if (maze[tile_x][tile_y - 1] == tile::W && _last_input == DOWN) {
        //     //         if (maze[tile_x + 1][tile_y] != tile::W && tile_x < _target_x) _last_input = RIGHT;
        //     //         else _last_input = LEFT;
        //     //     }
        //     //     else if (maze[tile_x][tile_y + 1] == tile::W && _last_input == UP) {
        //     //         if (maze[tile_x - 1][tile_y] != tile::W && tile_x > _target_x) _last_input = LEFT;
        //     //         else _last_input = RIGHT;
        //     //     }
        //     // }
    }

    void updatePosition(int x, int y) {
        ghost2_x = x;
        ghost2_y = y;
    }

    void updateDirection() {
        _last_input = ghost2_dir;
    }

    static int ghost2_x;
    static int ghost2_y;
    static Direction ghost2_dir;

};

#endif
