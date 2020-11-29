#ifndef PACMAN_H
#define PACMAN_H

#include "personagem.h"

__USING_API

class PacMan : public Personagem {
public:

    PacMan(sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 542, Direction dir = LEFT)
    : Personagem(x, y, dir, sprites, n_sprites) {

        pacman_x = x;
        pacman_y = y;
        pacman_dir = dir;

        rotateSprite(0);
    }

    ~PacMan() {
    }

    int checkPosition(int a = 0, int b = 0) {
        // Checks if PacMan has eaten something except ghosts (they check it)

        int tile_x = getTileX();
        int tile_y = getTileY();

        tiles current_tile = getTile(tile_x, tile_y);

        _mutex.v();
        switch(current_tile) {
            case tiles::o:
                    setTile(tile_x, tile_y, tiles::e);
                return 1;
            case tiles::O:
                    setTile(tile_x, tile_y, tiles::E);
                return 2;
            case tiles::F:
                setTile(tile_x, tile_y, tiles::f);
                return 3;
            default:
                return 0;
        }
    }

    void changeDirection(Direction direction) {
        // Called by input to change PacMan's direction

        if (direction == _last_input)
            return;

        pacman_dir = direction;

        switch (direction) {
            case LEFT:
                rotateSprite(0);

                switch(_last_input) {
                    case RIGHT:
                        _x -= 45;
                        _y -= 45;
                        break;
                    case UP:
                        _x -= 45;
                        break;
                    case DOWN:
                        _y -= 45;
                        break;
                }
                break;
            case RIGHT:
                rotateSprite(180);

                switch(_last_input) {
                    case LEFT:
                        _x += 45;
                        _y += 45;
                        break;
                    case DOWN:
                        _x += 45;
                        break;
                    case UP:
                        _y += 45;
                        break;
                }
                break;
            case DOWN:
                rotateSprite(270);

                switch(_last_input) {
                    case UP:
                        _x -= 45;
                        _y += 45;
                        break;
                    case RIGHT:
                        _x -= 45;
                        break;
                    case LEFT:
                        _y += 45;
                        break;
                }
                break;
            case UP:
                rotateSprite(90);

                switch(_last_input) {
                    case DOWN:
                        _x += 45;
                        _y -= 45;
                        break;
                    case LEFT:
                        _x += 45;
                        break;
                    case RIGHT:
                        _y -= 45;
                        break;
                }
                break;
        }

        _last_input = direction;
        pacman_x = _x;
        pacman_y = _y;
    }

    static int pacmanGetTileX() {
        // Returns tile based on static attribute

        if ((pacman_x - 14) % 24 != 0)
            return 0;

        switch (pacman_dir) {
            case UP:  return -1 + (pacman_x - 14) / 24;
                break;
            case DOWN:  return 1 + (pacman_x - 14) / 24;
                break;
            case LEFT: return 1 + (pacman_x - 14) / 24;
                break;
            case RIGHT: return -1 + (pacman_x - 14) / 24;
                break;
        }
    }

    static int pacmanGetTileY() {
        // Returns tile based on static attribute. 0 if not centralized

        if ((pacman_y - 14) % 24 != 0)
            return 0;

        switch (pacman_dir) {
            case DOWN:  return 2 + (710 - pacman_y) / 24;
                break;
            case UP:  return (710 - pacman_y) / 24;
                break;
            case LEFT: return (710 - pacman_y) / 24;
                break;
            case RIGHT: return 2 + (710 - pacman_y) / 24;
                break;
        }
    }

    int getTileX() {
        // Function overwrite
        return pacmanGetTileX();
    }

    int getTileY() {
        // Function overwrite
        return pacmanGetTileY();
    }

    void updatePosition(int x, int y) {
        // Returns tile based on static attribute
        pacman_x = x;
        pacman_y = y;
    }

    void updateDirection() {
        // Updates static values or sets _last_input in special case
        if (_last_input == STOPPED) {
            pacman_dir = _last_input;
        } else {
            _last_input = pacman_dir;
        }
    }

    static int pacmanGetNearTileX() {
        // Returns near tile based on static attribute

        int tile_x = pacmanGetTileX();

        if (tile_x == 0) {
            int tmp = (pacman_x - 14) % 24;
            if (tmp > 12)
                tmp -= 24;

            switch (pacman_dir) {
                case UP:  tile_x = -1 + (pacman_x - tmp - 14) / 24;
                    break;
                case DOWN:  tile_x = 1 + (pacman_x - tmp - 14) / 24;
                    break;
                case LEFT: tile_x = 1 + (pacman_x - tmp - 14) / 24;
                    break;
                case RIGHT: tile_x = -1 + (pacman_x - tmp - 14) / 24;
                    break;
            }
        }

        return tile_x;
    }

    static int pacmanGetNearTileY() {
        // Returns near tile based on static attribute

        int tile_y = pacmanGetTileY();

        if (tile_y == 0) {
            int tmp = (734 - pacman_y) % 24;
            if (tmp > 12)
                tmp -= 24;

            switch (pacman_dir) {
                case DOWN:  tile_y = 2 + (710 - pacman_y + tmp) / 24;
                    break;
                case UP:  tile_y = (710 - pacman_y + tmp) / 24;
                    break;
                case LEFT: tile_y = (710 - pacman_y + tmp) / 24;
                    break;
                case RIGHT: tile_y = 2 + (710 - pacman_y + tmp) / 24;
                    break;
            }
        }

        return tile_y;
    }

public:
    static int pacman_x;
    static int pacman_y;
    static Direction pacman_dir;
};



#endif
