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

    typedef enum {W, G, P, u, o, e, O, E, F, f} tiles;

    // 2D array defines the size of the maze and also what each tile contains
    static tiles maze[28][31];
    static void resetTiles() {
        tiles buf[28][31] =
         {
                 {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W},
                 {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                 {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                 {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                 {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                 {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                 {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                 {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                 {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                 {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                 {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                 {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W}
            };
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 31; j++) {
                maze[i][j] = buf[i][j];
            }
        }
    }
};

#endif
