#ifndef PACMAN_H
#define PACMAN_H

#include "personagem.h"

__USING_API

class PacMan : public Personagem {
public:

    // First Tile: 14 , 14
    // Last Tile: 614 , 686
    // Tile size: 24 , 24
    // Starter Tile: 310, 398
    PacMan(sf::Sprite * sprites = 0, int n_sprites = 0, int x = 310, int y = 398, Direction dir = LEFT)
    : Personagem(x, y, dir, sprites, n_sprites) {

        pacman_x = _x;
        pacman_y = _y;
        pacman_dir = _last_input;
    }

    ~PacMan() {
    }

    /*void run() {

        while (true) {
            switch(move()) {
                case 10:
                    Jogo::_score += 10;
                    Jogo::_foods--;
                    std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                    break;
                case 20:
                    Jogo::_score += 20;
                    std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                    break;
            }
        }
    }*/

    /*static int move(int a = 0, int b = 0) {
        // V2: Atualiza matriz e checa se há colisões

        int tile_x = pacmanGetTileX();
        int tile_y = pacmanGetTileY();

        switch (pacman_dir) {
            case UP:
                    if (pacman_y < 14) {
                        pacman_y = 14;
                        break;
                    }

                    if(tile_x == 0) {
                        int tmp = (pacman_x - 14) % 24;
                        pacman_x -= tmp;
                        if (tmp > 12)
                        pacman_x += 24;
                        tile_x = pacmanGetTileX();
                    }

                    if ((maze[tile_x][tile_y + 1] != tile::W && maze[tile_x][tile_y + 1] != tile::G) || tile_y == 0)
                        pacman_y -= 1;

                    break;
            case DOWN:
                    if (pacman_y >= 734) {
                        pacman_y = 734;
                        break;
                    }
                    if(tile_x == 0) {
                        int tmp = (pacman_x - 14) % 24;
                        pacman_x -= tmp;
                        if (tmp >= 12)
                        pacman_x += 24;
                        tile_x = pacmanGetTileX();
                    }
                    if ((maze[tile_x][tile_y - 1] != tile::W && maze[tile_x][tile_y - 1] != tile::G) || tile_y == 0)
                        pacman_y += 1;
                    break;
            case LEFT:
                    if (pacman_x < 14) {
                        pacman_x = 14;
                        break;
                    }
                    if (pacman_y == 326 && pacman_x == 14) {
                        pacman_x = 617;
                    }
                    if(tile_y == 0) {
                        int tmp = (pacman_y - 14) % 24;
                        pacman_y -= tmp;
                        if (tmp > 12)
                        pacman_y += 24;
                        tile_y = pacmanGetTileY();
                    }
                    if ((maze[tile_x - 1][tile_y] != tile::W && maze[tile_x - 1][tile_y] != tile::G) || tile_x == 0)
                        pacman_x -= 1;
                    break;
            case RIGHT:
                    if (pacman_x > 662) {
                        pacman_x = 662;
                        break;
                    }
                    if (pacman_y == 374  && pacman_x == 662) {
                        pacman_x = 59;
                        break;
                    }
                    if(tile_y == 0) {
                        int tmp = (pacman_y - 14) % 24;
                        pacman_y -= tmp;
                        if (tmp > 12)
                        pacman_y += 24;
                        tile_y = pacmanGetTileY();
                    }
                    if (maze[tile_x + 1][tile_y] != tile::W || tile_x == 0)
                        pacman_x += 1;
                    break;
        }

        return checkPosition(a, b);
    }*/

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

        _mutex.v();
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

        _mutex.v();
    }

    static int pacmanGetTileX() {
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

        return (pacman_x - 3) / 24;
    }

    static int pacmanGetTileY() {
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

        return (725 - pacman_y) / 24;
    }

    int getTileX() {
        return pacmanGetTileX();
    }

    int getTileY() {
        return pacmanGetTileY();
    }

    void updatePosition(int x, int y) {
        pacman_x = x;
        pacman_y = y;
    }

    void updateDirection() {
        _last_input = pacman_dir;
    }

public:
    static int pacman_x;
    static int pacman_y;
    static Direction pacman_dir;
};



#endif
