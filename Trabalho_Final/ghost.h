#ifndef GHOST_H
#define GHOST_H
#include "personagem.h"

class Ghost : public Personagem {
public:

    // starter tile: 315, 326
    Ghost(sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 254, int speed = GHOST_SPEED, Direction dir = RIGHT)
    : Personagem(x, y, speed, dir, sprites, n_sprites) {

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

    void getTargetTile(int pm_x, int pm_y, Direction dir) {

        _target_x = pm_x;
        _target_y = pm_y;

        int tile_x = getTileX();
        int tile_y = getTileY();

        if (tile_x != 0 && tile_y != 0)
            if (_x < _target_x && (maze[tile_x + 1][tile_y] != tile::W))
                _last_input = RIGHT;
            else if (_x > _target_x && (maze[tile_x - 1][tile_y] != tile::W))
                _last_input = LEFT;
            else if (_y < _target_y && (maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G))
                _last_input = DOWN;
            else if (_y > _target_y && (maze[tile_x][tile_y + 1] != tile::W && maze[tile_x][tile_y + 1] != tile::G))
                _last_input = UP;
    }

private:
    int _target_x;
    int _target_y;
};

#endif
