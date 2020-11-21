#ifndef GHOST_H
#define GHOST_H
#include "personagem.h"

class Ghost : public Personagem {
public:

    // starter tile: 315, 326
    Ghost(sf::Sprite * eyes = 0, sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 254, int speed = GHOST_SPEED, Direction dir = RIGHT)
    : Personagem(x, y, speed, dir, sprites, n_sprites), _eyes(eyes) {

        getTargetTile(310, 398, LEFT);

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

    static void run() {

        while (true) {

        }
        // get Keyboard
        // move()
    }

    int checkPosition(int pm_t_x, int pm_t_y) {

        int tile_x = getTileX();
        int tile_y = getTileY();

        if (tile_x != 0 && tile_y != 0)
            if (tile_x == pm_t_x && tile_y == pm_t_y) {
                std::cout << "you lost!!!!!!!!!!!!!!!!\n";
            }
    }

    int getDistance(int _x1, int _y1, int _x2, int _y2) {
        return (_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2);
    }

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

    sf::Sprite getEye() {
        _eyes[_last_input].setPosition(_x, _y);
        return _eyes[_last_input];
    }

private:
    int _target_x;
    int _target_y;
    sf::Sprite * _eyes;
};

#endif
