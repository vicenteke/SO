#ifndef GHOST_H
#define GHOST_H

#include "personagem.h"

__USING_API

class Ghost : public Personagem {
public:

    Semaphore _mutex_scared;

    Ghost(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 254, Direction dir = RIGHT)
    : Personagem(x, y, dir, sprites, n_sprites), _eyes(eyes) {

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

    int checkPosition(int pm_t_x, int pm_t_y) {

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
                return -1;
            }
        }

        _mutex.v();
        return 0;

        // if (abs(_x - pm_t_x) < 50 && abs(_y - pm_t_y) < 50) {
        //     std::cout << "you lost!!!!!!!!!!!!!!!!\n";
        // }

    }

    int getDistance(int _x1, int _y1, int _x2, int _y2) {
        return (_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2);
    }

    virtual void getTargetTile(int pm_x, int pm_y, Direction dir) = 0;
    // {
    //
    //     int tile_x = getTileX();
    //     int tile_y = getTileY();
    //
    //     int dist = getDistance(_x, _y, pm_x, pm_y);
    //
    //     _target_x = pm_x;
    //     _target_y = pm_y;
    //
    //     // Problemas:
    //     // 1) Ghost trava no portal
    //     // 2) Dependendo da esquina em que o pacman fica parado ele vai pra muito longe ou nunca chega no pacman
    //     // 3) Deveria seguir diretamente o pacman, mas ta fazendo umas escolhas burras
    //     // 4) Nunca deveria inverter a direção (ex: da direita pra esquerda)
    //     if (tile_x != 0 && tile_y != 0) {
    //         if (getDistance(_x + 24, _y, pm_x, pm_y) < dist && maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT) {
    //             _last_input = RIGHT;
    //        } else if (getDistance(_x - 24, _y, pm_x, pm_y) < dist && maze[tile_x - 1][tile_y] != tile::W  && _last_input != RIGHT) {
    //             _last_input = LEFT;
    //         } else if (getDistance(_x, _y - 24, pm_x, pm_y) < dist && maze[tile_x][tile_y + 1] != tile::W  && _last_input != DOWN) {
    //             _last_input = UP;
    //         } else if (getDistance(_x, _y + 24, pm_x, pm_y) < dist && maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
    //             _last_input = DOWN;
    //         } else {
    //             if (maze[tile_x + 1][tile_y] == tile::W && _last_input == RIGHT) {
    //                 if (maze[tile_x][tile_y + 1] != tile::W && tile_y > _target_y) _last_input = UP;
    //                 else _last_input = DOWN;
    //             }
    //             else if (maze[tile_x - 1][tile_y] == tile::W && _last_input == LEFT) {
    //                 if (maze[tile_x][tile_y - 1] != tile::W  && tile_y < _target_y) _last_input = DOWN;
    //                 else _last_input = UP;
    //             }
    //             else if (maze[tile_x][tile_y - 1] == tile::W && _last_input == DOWN) {
    //                 if (maze[tile_x + 1][tile_y] != tile::W && tile_x < _target_x) _last_input = RIGHT;
    //                 else _last_input = LEFT;
    //             }
    //             else if (maze[tile_x][tile_y + 1] == tile::W && _last_input == UP) {
    //                 if (maze[tile_x - 1][tile_y] != tile::W && tile_x > _target_x) _last_input = LEFT;
    //                 else _last_input = RIGHT;
    //             }
    //         }
    //     }
    //
    //     ghost_dir = _last_input;
    //
    //     // if (tile_x != 0 && tile_y != 0)
    //     //     if (tile_x < _target_x && maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT)
    //     //         _last_input = RIGHT;
    //     //     else if (tile_x >= _target_x && maze[tile_x - 1][tile_y] != tile::W && _last_input != RIGHT)
    //     //         _last_input = LEFT;
    //     //     else if (tile_y <= _target_y && maze[tile_x][tile_y - 1] != tile::W && _last_input != UP)
    //     //         _last_input = DOWN;
    //     //     else if (tile_y > _target_y && maze[tile_x][tile_y + 1] != tile::W && _last_input != DOWN)
    //     //         _last_input = UP;
    //     //     else {
    //     //         if (maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT) _last_input = RIGHT;
    //     //         else if (maze[tile_x - 1][tile_y] != tile::W && _last_input != RIGHT) _last_input = LEFT;
    //     //         else if (maze[tile_x][tile_y - 1] != tile::W && _last_input != UP) _last_input = DOWN;
    //     //         else if (maze[tile_x][tile_y + 1] != tile::W && _last_input != DOWN) _last_input = UP;
    //     //     }
    //     //     // else {
    //     //     //     if (maze[tile_x + 1][tile_y] == tile::W && _last_input == RIGHT) {
    //     //     //         if (maze[tile_x][tile_y + 1] != tile::W && tile_y > _target_y) _last_input = UP;
    //     //     //         else _last_input = DOWN;
    //     //     //     }
    //     //     //     else if (maze[tile_x - 1][tile_y] == tile::W && _last_input == LEFT) {
    //     //     //         if (maze[tile_x][tile_y - 1] != tile::W  && tile_y < _target_y) _last_input = DOWN;
    //     //     //         else _last_input = UP;
    //     //     //     }
    //     //     //     else if (maze[tile_x][tile_y - 1] == tile::W && _last_input == DOWN) {
    //     //     //         if (maze[tile_x + 1][tile_y] != tile::W && tile_x < _target_x) _last_input = RIGHT;
    //     //     //         else _last_input = LEFT;
    //     //     //     }
    //     //     //     else if (maze[tile_x][tile_y + 1] == tile::W && _last_input == UP) {
    //     //     //         if (maze[tile_x - 1][tile_y] != tile::W && tile_x > _target_x) _last_input = LEFT;
    //     //     //         else _last_input = RIGHT;
    //     //     //     }
    //     //     // }
    // }

    /*sf::Sprite getEye() {
        return _eyes[_last_input];
    }

    sf::Sprite getSprite() {
        return _sprites[(_i / 15) % 2];
    }

    void setPositions() {
        _sprites[(_i / 15) % 2].setPosition(_x, _y);
        _eyes[_last_input].setPosition(_x, _y);
    }

    void count() {
        _i++;
        if (_i == 55440) _i = 0;
    }*/

    virtual void updatePosition(int x, int y) {}

    virtual void updateDirection() {}

    void scareRunAway(int pm_x, int pm_y) {
        // Used instead of getTargetTile when _isScared = true

        _mutex.p();

        int tile_x = getTileX();
        int tile_y = getTileY();

        int dist = getDistance(_x, _y, pm_x, pm_y);
        int dist_r = getDistance(_x + 24, _y, pm_x, pm_y);
        int dist_l = getDistance(_x - 24, _y, pm_x, pm_y);
        int dist_d = getDistance(_x, _y + 24, pm_x, pm_y);
        int dist_u = getDistance(_x, _y - 24, pm_x, pm_y);

        _target_x = pm_x;
        _target_y = pm_y;

        if (dist_r >= dist_l) {
            if (dist_r >= dist_u) {
                if (dist_r >= dist_d && maze[tile_x + 1][tile_y] != tile::W && _last_input != LEFT) {
                    _last_input = RIGHT;
                } else if (maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
                    _last_input = DOWN;
                } else {
                    goto GET_ANY;
                }
            } else {
                if (dist_u >= dist_d && maze[tile_x][tile_y + 1] != tile::W  && _last_input != DOWN) {
                    _last_input = UP;
                } else if (maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
                    _last_input = DOWN;
                } else {
                    goto GET_ANY;
                }
            }
        } else {
            if (dist_l >= dist_u) {
                if (dist_l >= dist_d && maze[tile_x - 1][tile_y] != tile::W  && _last_input != RIGHT) {
                    _last_input = LEFT;
                } else if (maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
                    _last_input = DOWN;
                } else {
                    goto GET_ANY;
                }
            } else {
                if (dist_u >= dist_d && maze[tile_x][tile_y + 1] != tile::W  && _last_input != DOWN) {
                    _last_input = UP;
                } else if (maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G && _last_input != UP) {
                    _last_input = DOWN;
                } else {
                    GET_ANY:
                    if (maze[tile_x][tile_y + 1] != tile::W) // && _last_input != DOWN)
                        _last_input = UP;
                    else if (maze[tile_x - 1][tile_y] != tile::W) // && _last_input != RIGHT)
                        _last_input = LEFT;
                    else if (maze[tile_x + 1][tile_y] != tile::W) // && _last_input != LEFT)
                        _last_input = RIGHT;
                    else {
                        std::cout << "Não faz sentido\n";
                        _last_input = DOWN;
                    }
                }
            }
        }

        updateDirection();

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
