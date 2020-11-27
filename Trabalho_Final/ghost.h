#ifndef GHOST_H
#define GHOST_H

#include "personagem.h"

__USING_API

class Ghost : public Personagem {
public:

    Semaphore _mutex_scared;

    Ghost(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 254, Direction dir = RIGHT)
    : Personagem(x, y, dir, sprites, n_sprites), _eyes(eyes) {

        updatePosition(x, y);
        updateDirection();
        _i = 0;
        _isScared = false;
        _jail_x = 310;
        _jail_y = 334;
        _isJailed = false;
    }

    ~Ghost() {}

    int getTileX() {
        if ((_x - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case UP:  return 1 + (_x - 14) / 24;
                break;
            case DOWN:  return 1 + (_x - 14) / 24;
                break;
            case LEFT: return 1 + (_x - 14) / 24;
                break;
            case RIGHT: return 1 + (_x - 14) / 24;
                break;
        }

        return 1 + (_x - 14) / 24;
    }

    int getTileY() {
        if ((_y - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case DOWN:  return (710 - _y) / 24;
                break;
            case UP:  return (710 - _y) / 24;
                break;
            case LEFT: return (710 - _y) / 24;
                break;
            case RIGHT: return (710 - _y) / 24;
                break;
        }

        return (710 - _y) / 24;
    }

    int getNearTileX() {
        int tile_x = getTileX();

        if (tile_x == 0 ){
            int tmp = (_x - 14) % 24;
            if (tmp > 12) tmp -= 24;

            switch (_last_input) {
                case UP:  tile_x = 1 + (_x - tmp - 14) / 24;
                    break;
                case DOWN:  tile_x = 1 + (_x - tmp - 14) / 24;
                    break;
                case LEFT: tile_x = 1 + (_x - tmp - 14) / 24;
                    break;
                case RIGHT: tile_x = 1 + (_x - tmp - 14) / 24;
                    break;
            }
        }

        return tile_x;
    }

    int getNearTileY() {
        int tile_y = getTileY();

        if (tile_y == 0) {
            int tmp = (_y - 14) % 24;
            if (tmp > 12) tmp -= 24;

            switch (_last_input) {
                case DOWN:  tile_y = (710 - _y + tmp) / 24;
                    break;
                case UP:  tile_y = (710 - _y + tmp) / 24;
                    break;
                case LEFT: tile_y = (710 - _y + tmp) / 24;
                    break;
                case RIGHT: tile_y = (710 - _y + tmp) / 24;
                    break;
            }
        }

        return tile_y;
    }

    int checkPosition(int pm_t_x, int pm_t_y);

    int getDistance(int _x1, int _y1, int _x2, int _y2) {
        return abs(_x1 - _x2) + abs(_y1 - _y2);
    }

    virtual void getTargetTile(int, int, Direction) = 0;

    virtual void updatePosition(int x, int y) {}

    virtual void updateDirection() {}
    virtual void updateDirection(Direction) {}

    void scareRunAway(int pm_x, int pm_y) {
        // Used instead of getTargetTile when _isScared = true

        _mutex.p();

        int tile_x = getTileX();
        int tile_y = getTileY();

        _target_x = pm_x;
        _target_y = pm_y;

        int dist_r = (getTile(tile_x + 1, tile_y) == tiles::W || _last_input == LEFT)? -1 : 1;
        int dist_l = (getTile(tile_x - 1, tile_y) == tiles::W  || _last_input == RIGHT)? -1 : 1;
        int dist_d = (getTile(tile_x, tile_y - 1) == tiles::W || getTile(tile_x, tile_y - 1) == tiles::G || _last_input == UP)? -1 : 1;
        int dist_u = (getTile(tile_x, tile_y + 1) == tiles::W  || _last_input == DOWN)? -1 : 1;

        if (dist_u > 0 && tile_y >= _target_y) _last_input = UP;
        else if (dist_d > 0 && tile_y < _target_y) _last_input = DOWN;
        else if (dist_r > 0 && tile_x >= _target_x) _last_input = RIGHT;
        else if (dist_l > 0) _last_input = LEFT;
        else if (dist_u > 0) _last_input = UP;
        else if (dist_d > 0) _last_input = DOWN;
        else if (dist_r > 0) _last_input = RIGHT;

        updateDirection(_last_input);

        _mutex.v();
    }

    void isScared(bool b) {
        _isScared = b;
    }

    bool isScared() {
        _mutex_scared.p();
        bool tmp = _isScared;
        _mutex_scared.v();
        return tmp;
    }

    void isJailed(bool b) {
        _isJailed = b;
    }

    bool isJailed() {
        _mutex_scared.p();
        bool tmp = _isJailed;
        _mutex_scared.v();
        return tmp;
    }

protected:
    int _target_x;
    int _target_y;
    sf::Sprite * _eyes;
    int _i;

    bool _isScared;
    int _jail_x;
    int _jail_y;
    bool _isJailed;
};



#endif
