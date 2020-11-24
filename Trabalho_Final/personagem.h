#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>

#include "tiles.h"
#include "defines.h"
#include "semaphore.h"

__USING_API

class Personagem {

public:
    Semaphore _mutex;

    Personagem(int x, int y, Direction dir, sf::Sprite * sprites, int n_sprites) :
    _x(x), _y(y), _last_input(dir), _sprites(sprites), _n_sprites(n_sprites) {}

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

    virtual int getTileX() = 0;
    virtual int getTileY() = 0;

    virtual int checkPosition(int, int) = 0;

    void rotateSprite(int angle) {
        for (int i = 0; i < _n_sprites; i++) {
            _sprites[i].setRotation(angle);
        }
    }

    int move(int a = 0, int b = 0) {
        // V2: Atualiza matriz e checa se há colisões

        _mutex.p();

        int tile_x = getTileX();
        int tile_y = getTileY();

        updateDirection();

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
                        _y -= 1;

                    break;
            case DOWN:
                    if (_y >= 734) {
                        _y = 734;
                        break;
                    }
                    if(tile_x == 0) {
                        int tmp = (_x - 14) % 24;
                        _x -= tmp;
                        if (tmp > 15)
                            _x += 24;
                        tile_x = getTileX();
                    }
                    if ((maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G) || tile_y == 0)
                        _y += 1;
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
                        if (tmp > 15)
                            _y += 24;
                        tile_y = getTileY();
                    }
                    if ((maze[tile_x - 1][tile_y] != tile::W && maze[tile_x - 1][tile_y] != tile::G) || tile_x == 0)
                        _x -= 1;
                    break;
            case RIGHT:
                    if (_x > 662) {
                        _x = 662;
                        break;
                    }
                    if ((_y == 374 || _y == 326)  && _x == 662) {
                        _x = 59;
                        break;
                    }
                    if(tile_y == 0) {
                        int tmp = (_y - 14) % 24;
                        _y -= tmp;
                        if (tmp > 15)
                            _y += 24;
                        tile_y = getTileY();
                    }
                    if (maze[tile_x + 1][tile_y] != tile::W || tile_x == 0)
                        _x += 1;
                    break;
        }

        updatePosition(_x, _y);

        return checkPosition(a, b);
    }

    virtual void updatePosition(int, int) = 0;
    virtual void updateDirection() = 0;

protected:
    int _x;
    int _y;
    Direction _last_input;
    sf::Sprite *_sprites;
    int _n_sprites;
};



#endif
