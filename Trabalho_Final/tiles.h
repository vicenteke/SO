#ifndef TILES_H
#define TILES_H

class Tiles {
public:
    typedef enum {W, G, P, u, o, e, O, E, F} tile;

    // 2D array defines the size of the maze and also what each tile contains
    static tile maze[28][31];
};

#endif
