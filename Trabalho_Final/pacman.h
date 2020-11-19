#ifndef PACMAN_H
#define PACMAN_H
#include "personagem.h"

class PacMan : public Personagem {
public:

    // First Tile: 14 , 14
    // Last Tile: 614 , 686
    // Tile size: 24 , 24
    // Starter Tile: 310, 398
    PacMan(int x = 310, int y = 398, int speed = PACMAN_SPEED, Direction dir = LEFT)
    : Personagem(x, y, speed, dir) {}

    ~PacMan() {}

    static void run() {

        while (true) {

        }
        // get Keyboard
        // move()
    }

    int checkPosition() {

        int tile_x = getTileX();
        int tile_y = getTileY();

        switch(maze[tile_x][tile_y]) {
            case tile::o:
                maze[tile_x][tile_y] = tile::e;
                return 100;
            case tile::O:
                maze[tile_x][tile_y] = tile::E;
                return 200;
            default:
                return 0;
        }
    }
};

#endif
