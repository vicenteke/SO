#ifndef PACMAN_H
#define PACMAN_H
#include "personagem.h"
#include "tiles.h"

#define tile Tiles::tile
#define maze Tiles::maze

class PacMan : public Personagem {
public:

    // First Tile: 14 , 14
    // Last Tile: 614 , 686
    // Tile size: 24 , 24
    // Starter Tile: 310, 398
    PacMan(int x = 310, int y = 398, Direction dir = LEFT)
    : Personagem(x, y), _last_input(dir) {

    }
    ~PacMan() {}

    static void run() {

        while (true) {

        }
        // get Keyboard
        // move()
    }

    void move() {
        // V2: Atualiza matriz e checa se há colisões

        switch (_last_input) {
            case UP:
                    if (_y <= 14) {
                        _y = 14;
                        break;
                    }
                    if (maze[getTileX()][getTileY() + 1] != tile::W || getTileY() == 0)
                        _y -= SPEED;
                    if(getTileX() == 0) {
                        int tmp = (_x - 14) % 24;
                        _x -= tmp;
                        if (tmp > 12)
                            _x += 24;
                    }

                    break;
            case DOWN:
                    if (_y >= 734) {
                        _y = 734;
                        break;
                    }
                    if (maze[getTileX()][getTileY() - 1] != tile::W || getTileY() == 0)
                        _y += SPEED;
                    if(getTileX() == 0) {
                        int tmp = (_x - 14) % 24;
                        _x -= tmp;
                        if (tmp > 12)
                            _x += 24;
                    }
                    break;
            case LEFT:
                    if (_x <= 14) {
                        _x = 14;
                        break;
                    }
                    if (maze[getTileX() - 1][getTileY()] != tile::W || getTileX() == 0)
                        _x -= SPEED;
                    if(getTileY() == 0) {
                        int tmp = (_y - 14) % 24;
                        _y -= tmp;
                        if (tmp > 12)
                            _y += 24;
                    }
                    break;
            case RIGHT:
                    if (_x >= 662) {
                        _x = 662;
                        break;
                    }
                    if (maze[getTileX() + 1][getTileY()] != tile::W || getTileX() == 0)
                        _x += SPEED;
                    if(getTileY() == 0) {
                        int tmp = (_y - 14) % 24;
                        _y -= tmp;
                        if (tmp > 12)
                            _y += 24;
                    }
                    break;
        }
    }

    void direction(Direction d) {
        _last_input = d;
    }

    Direction direction() {
        return _last_input;
    }

    // Not Working
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

    // Not Working
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

private:
    Direction _last_input;
    static const int SPEED;
};

#endif
