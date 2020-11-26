#ifndef GHOST1_H
#define GHOST1_H

#include "ghost.h"

__USING_API

class Ghost1 : public Ghost {
public:

    Ghost1(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 422, int y = 254, Direction dir = UP)
    : Ghost(eyes, sprites, n_sprites, x, y, dir)
    {
        getTargetTile(13, 13, LEFT);
        _jail_x -= 45;
    }

    ~Ghost1() {}

    void getTargetTile(int pm_x, int pm_y, Direction dir) {

        if (isJailed()) {
            return;
        } else if (isScared()) {
            return scareRunAway(pm_x, pm_y);
        } else if (_last_input == STOPPED) {
            updateDirection(RIGHT);
        }

        int tile_x = getTileX();
        int tile_y = getTileY();

        if (tile_x == 0 || tile_y == 0)
            return;

        _target_x = pm_x;
        _target_y = pm_y;

        int dist_r = (maze[tile_x + 1][tile_y] == tile::W || _last_input == LEFT)? -1 : 1;
        int dist_l = (maze[tile_x - 1][tile_y] == tile::W  || _last_input == RIGHT)? -1 : 1;
        int dist_d = (maze[tile_x][tile_y - 1] == tile::W || maze[tile_x][tile_y - 1] == tile::G || _last_input == UP)? -1 : 1;
        int dist_u = (maze[tile_x][tile_y + 1] == tile::W  || _last_input == DOWN)? -1 : 1;

        if (dist_u > 0 && tile_y < _target_y) _last_input = UP;
        else if (dist_d > 0 && tile_y > _target_y) _last_input = DOWN;
        else if (dist_r > 0 && tile_x < _target_x) _last_input = RIGHT;
        else if (dist_l > 0) _last_input = LEFT;
        else if (dist_u > 0) _last_input = UP;
        else if (dist_d > 0) _last_input = DOWN;
        else if (dist_r > 0) _last_input = RIGHT;

        ghost1_dir = _last_input;
    }

    void updatePosition(int x, int y) {
        ghost1_x = x;
        ghost1_y = y;
    }

    void updateDirection() {
        if (_last_input == STOPPED) {
            ghost1_dir = _last_input;
        } else {
            _last_input = ghost1_dir;
        }
    }

    void updateDirection(Direction dir) {
        ghost1_dir = dir;
        _last_input = dir;
    }

    static int ghost1_x;
    static int ghost1_y;
    static Direction ghost1_dir;

};

#endif
