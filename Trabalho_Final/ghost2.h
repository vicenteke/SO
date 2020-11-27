#ifndef GHOST2_H
#define GHOST2_H

#include "ghost.h"

__USING_API

class Ghost2 : public Ghost {
public:

    Ghost2(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 350, int y = 254, Direction dir = RIGHT)
    : Ghost(eyes, sprites, n_sprites, x, y, dir)
    {
        getTargetTile(13, 13, LEFT);
        _jail_x -= 12;
    }

    ~Ghost2() {}

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

        switch(dir) {
            case LEFT:
                _target_x = pm_x - 4;
                _target_y = pm_y;
                break;
            case RIGHT:
                _target_x = pm_x + 4;
                _target_y = pm_y;
                break;
            case DOWN:
                _target_x = pm_x;
                _target_y = pm_y - 4;
                break;
            case UP:
                _target_x = pm_x - 4;
                _target_y = pm_y + 4;
                break;
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

        ghost2_dir = _last_input;
    }

    void updatePosition(int x, int y) {
        ghost2_x = x;
        ghost2_y = y;
    }

    void updateDirection() {
        if (_last_input == STOPPED) {
            ghost2_dir = _last_input;
        } else {
            _last_input = ghost2_dir;
        }
    }

    void updateDirection(Direction dir) {
        ghost2_dir = dir;
        _last_input = dir;
    }

    static int ghost2_x;
    static int ghost2_y;
    static Direction ghost2_dir;

};

#endif
