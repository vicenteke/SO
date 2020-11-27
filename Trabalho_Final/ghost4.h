#ifndef GHOST4_H
#define GHOST4_H

#include "ghost.h"

__USING_API

class Ghost4 : public Ghost {
public:

    Ghost4(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 206, int y = 254, Direction dir = DOWN)
    : Ghost(eyes, sprites, n_sprites, x, y, dir)
    {
        getTargetTile(13, 13, LEFT);
        _jail_x += 55;
    }

    ~Ghost4() {}

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

        if (getDistance(tile_x, tile_y, pm_x, pm_y) < 6) {
            _target_x = pm_x;
            _target_y = pm_y;
        } else if(getDistance(tile_x, tile_y, 0, 0) > 20){
            _target_x = 0;
            _target_y = 0;
        } else {
            _target_x = 28;
            _target_y = 15;
        }

        int dist_r = (getTile(tile_x + 1, tile_y) == tiles::W || _last_input == LEFT)? -1 : 1;
        int dist_l = (getTile(tile_x - 1, tile_y) == tiles::W  || _last_input == RIGHT)? -1 : 1;
        int dist_d = (getTile(tile_x, tile_y - 1) == tiles::W || getTile(tile_x, tile_y - 1) == tiles::G || _last_input == UP)? -1 : 1;
        int dist_u = (getTile(tile_x, tile_y + 1) == tiles::W  || _last_input == DOWN)? -1 : 1;

        if (dist_u > 0 && tile_y < _target_y) _last_input = UP;
        else if (dist_d > 0 && tile_y > _target_y) _last_input = DOWN;
        else if (dist_r > 0 && tile_x < _target_x) _last_input = RIGHT;
        else if (dist_l > 0) _last_input = LEFT;
        else if (dist_u > 0) _last_input = UP;
        else if (dist_d > 0) _last_input = DOWN;
        else if (dist_r > 0) _last_input = RIGHT;

        ghost4_dir = _last_input;
    }

    void updatePosition(int x, int y) {
        ghost4_x = x;
        ghost4_y = y;
    }

    void updateDirection() {
        if (_last_input == STOPPED) {
            ghost4_dir = _last_input;
        } else {
            _last_input = ghost4_dir;
        }
    }

    void updateDirection(Direction dir) {
        ghost4_dir = dir;
        _last_input = dir;
    }

    static int ghost4_x;
    static int ghost4_y;
    static Direction ghost4_dir;

};

#endif
