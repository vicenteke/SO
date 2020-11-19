#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>

#include "tiles.h"
#include "defines.h"

class Personagem {

public:
    static const int PACMAN_SPEED = 1;
    static const int GHOST_SPEED = 1;

public:
    enum Direction {UP, DOWN, LEFT, RIGHT, STOPPED};

    Personagem(int x, int y, int _speed, Direction dir) :
    _x(x), _y(y), _speed(_speed), _last_input(dir) {}

    ~Personagem(){}

    // void updateMatrix(char c); // Usa mutex

    int getX() {
        return _x;
    }

    int getY() {
        return _y;
    }

    void setX(int x) {
        _x = x;
    }

    void setY(int y) {
        _y = y;
    }

    void direction(Direction d) {
        _last_input = d;
    }

    Direction direction() {
        return _last_input;
    }

    int getTileX() {
        if ((_x - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case UP:  return -1 + (_x - 14 - 48 + 48) / 24;
                break;
            case DOWN:  return 1 + (_x - 14) / 24;
                break;
            case LEFT: return 1 + (_x - 14) / 24;
                break;
            case RIGHT: return -1 + (_x - 14 - 48 + 48) / 24;
                break;
        }

        return (_x - 3) / 24;
    }

    int getTileY() {
        if ((_y - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case DOWN:  return 2 + (710 - _y - 48 + 48) / 24;
                break;
            case UP:  return (710 - _y) / 24;
                break;
            case LEFT: return (710 - _y) / 24;
                break;
            case RIGHT: return 2 + (710 - _y - 48 + 48) / 24;
                break;
        }

        return (725 - _y) / 24;
    }

    virtual int checkPosition() = 0;

    int move() {
        // V2: Atualiza matriz e checa se há colisões

        int tile_x = getTileX();
        int tile_y = getTileY();

        switch (_last_input) {
            case UP:
                    if (_y < 14) {
                        _y = 14;
                        break;
                    }

                    if(tile_x == 0) {
                        int tmp = (_x - 14) % 24;
                        _x -= tmp;
                        if (tmp > 12)
                        _x += 24;
                        tile_x = getTileX();
                    }

                    if ((maze[tile_x][tile_y + 1] != tile::W && maze[tile_x][tile_y + 1] != tile::G) || tile_y == 0)
                        _y -= _speed;

                    break;
            case DOWN:
                    if (_y >= 734) {
                        _y = 734;
                        break;
                    }
                    if(tile_x == 0) {
                        int tmp = (_x - 14) % 24;
                        _x -= tmp;
                        if (tmp > 12)
                        _x += 24;
                        tile_x = getTileX();
                    }
                    if ((maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G) || tile_y == 0)
                        _y += _speed;
                    break;
            case LEFT:
                    if (_x < 14) {
                        _x = 14;
                        break;
                    }
                    if (_y == 326 && _x == 14) {
                        _x = 617;
                    }
                    if(tile_y == 0) {
                        int tmp = (_y - 14) % 24;
                        _y -= tmp;
                        if (tmp > 12)
                        _y += 24;
                        tile_y = getTileY();
                    }
                    if ((maze[tile_x - 1][tile_y] != tile::W && maze[tile_x - 1][tile_y] != tile::G) || tile_x == 0)
                        _x -= _speed;
                    break;
            case RIGHT:
                    if (_x > 662) {
                        _x = 662;
                        break;
                    }
                    if (_y == 374  && _x == 662) {
                        _x = 59;
                        break;
                    }
                    if(tile_y == 0) {
                        int tmp = (_y - 14) % 24;
                        _y -= tmp;
                        if (tmp > 12)
                        _y += 24;
                        tile_y = getTileY();
                    }
                    if (maze[tile_x + 1][tile_y] != tile::W || tile_x == 0)
                        _x += _speed;
                    break;
        }

        return checkPosition();
    }

protected:
    int _x;
    int _y;
    int _speed;
    Direction _last_input;
};
