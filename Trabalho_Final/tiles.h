#ifndef TILES_H
#define TILES_H

class Tiles {
public:

    /**
     * Tile defined as an enum where each type is defined as:
     *      W: Wall
     *      G: Ghost Pen Gate
     *      P: Portal
     *      u: Empty path
     *      o: Pill
     *      e: Eaten Pill
     *      O: Big Pill
     *      E: Eaten Big Pill
     */
     
    typedef enum {W, G, P, u, o, e, O, E, F} tile;

    // 2D array defines the size of the maze and also what each tile contains
    static tile maze[28][31];
};

#endif
