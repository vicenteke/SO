#ifndef JOGO_H
#define JOGO_H

#include "thread.h"
#include "window.h"
#include "pacman.h"
#include "ghost.h"

__USING_API

class Jogo {
public:
    Jogo() {

        // _window = Window();
        _pacman = PacMan(_window.getPacmanSprites(), 4);
        _ghost = Ghost(&(_window.getGhostSprites()[2]), _window.getGhostSprites(), 2);
        //
        // run();
    }

    ~Jogo() {

    }

    static void run(void *) {

        Thread window_thread = Thread(Window::run);
        Thread pacman_thread = Thread(runPacman);
        Thread ghost_thread = Thread(runGhost);

        int pacman_status = pacman_thread.join();
        int ghost_status = ghost_thread.join();
        int window_status = window_thread.join();

    }

    static Window _window;

    // Game stats
    static int _lives;
    static int _foods;
    static int _score;

private:

    // Characters
    static PacMan _pacman;
    static Ghost _ghost;

    static void runPacman() {

        while (true) {
            switch(_pacman.move()) {
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
            Thread::yield();
        }
    }

    static void runGhost() {

        while (true) {

            _ghost.getTargetTile(PacMan::pacman_x, PacMan::pacman_y, PacMan::pacman_dir);
            _ghost.move(PacMan::pacmanGetTileX(), PacMan::pacmanGetTileY());
            Thread::yield();
        }
    }

};



#endif
