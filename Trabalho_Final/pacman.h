#ifndef PACMAN_H
#define PACMAN_H
#include "personagem.h"

class PacMan : public Personagem {
public:

    // First Tile: 14 , 14
    // Last Tile: 614 , 686
    // Tile size: 24 , 24
    // Starter Tile: 310, 398
    PacMan(sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 398, int speed = PACMAN_SPEED, Direction dir = LEFT)
    : Personagem(x, y, speed, dir, sprites, n_sprites) {}

    ~PacMan() {}

    static void run() {

        while (true) {

        }
        // get Keyboard
        // move()
    }

    int checkPosition(int a = 0, int b = 0) {

        int tile_x = getTileX();
        int tile_y = getTileY();

        tile current_tile = maze[tile_x][tile_y];
        // maze[tile_x][tile_y] = tile::P;
        // switch(_last_input) {
        //     case LEFT:
        //         if (maze[tile_x + 1][tile_y] == tile::P)
        //             maze[tile_x + 1][tile_y] = tile::u;
        //         break;
        //     case RIGHT:
        //         if (maze[tile_x - 1][tile_y] == tile::P)
        //             maze[tile_x - 1][tile_y] = tile::u;
        //         break;
        //     case DOWN:
        //         if (maze[tile_x][tile_y - 1] == tile::P)
        //             maze[tile_x][tile_y - 1] = tile::u;
        //         break;
        //     case UP:
        //         if (maze[tile_x][tile_y + 1] == tile::P)
        //             maze[tile_x][tile_y + 1] = tile::u;
        //         break;
        // }

        switch(current_tile) {
            case tile::o:
                    maze[tile_x][tile_y] = tile::e;
                return 10;
            case tile::O:
                    maze[tile_x][tile_y] = tile::E;
                return 20;
            default:
                return 0;
        }
    }

    void changeDirection(Direction direction) {
        switch (direction) {
            case LEFT:
                rotateSprite(0);

                switch(_last_input) {
                    case Personagem::Direction::RIGHT:
                        _x -= 45;
                        _y -= 45;
                        break;
                    case Personagem::Direction::UP:
                        _x -= 45;
                        break;
                    case Personagem::Direction::DOWN:
                        _y -= 45;
                        break;
                }
                break;
            case RIGHT:
                rotateSprite(180);

                switch(_last_input) {
                    case Personagem::Direction::LEFT:
                        _x += 45;
                        _y += 45;
                        break;
                    case Personagem::Direction::DOWN:
                        _x += 45;
                        break;
                    case Personagem::Direction::UP:
                        _y += 45;
                        break;
                }
                break;
            case DOWN:
                rotateSprite(270);

                switch(_last_input) {
                    case Personagem::Direction::UP:
                        _x -= 45;
                        _y += 45;
                        break;
                    case Personagem::Direction::RIGHT:
                        _x -= 45;
                        break;
                    case Personagem::Direction::LEFT:
                        _y += 45;
                        break;
                }
                break;
            case UP:
                rotateSprite(90);

                switch(_last_input) {
                    case Personagem::Direction::DOWN:
                        _x += 45;
                        _y -= 45;
                        break;
                    case Personagem::Direction::LEFT:
                        _x += 45;
                        break;
                    case Personagem::Direction::RIGHT:
                        _y -= 45;
                        break;
                }
                break;
        }

        _last_input = direction;
    }

    int getTileX() {
        if ((_x - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case UP:  return -1 + (_x - 14) / 24;
                break;
            case DOWN:  return 1 + (_x - 14) / 24;
                break;
            case LEFT: return 1 + (_x - 14) / 24;
                break;
            case RIGHT: return -1 + (_x - 14) / 24;
                break;
        }

        return (_x - 3) / 24;
    }

    int getTileY() {
        if ((_y - 14) % 24 != 0)
            return 0;

        switch (_last_input) {
            case DOWN:  return 2 + (710 - _y) / 24;
                break;
            case UP:  return (710 - _y) / 24;
                break;
            case LEFT: return (710 - _y) / 24;
                break;
            case RIGHT: return 2 + (710 - _y) / 24;
                break;
        }

        return (725 - _y) / 24;
    }
};

#endif
