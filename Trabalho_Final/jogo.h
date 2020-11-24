#ifndef JOGO_H
#define JOGO_H

#define DE_LEI 950000

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

        // Thread window_thread = Thread(Window::run);
        Thread window_thread = Thread(runWindow);
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
            for (volatile unsigned int j = 0; j < DE_LEI; j++);
            Thread::yield();
        }
    }

    static void runGhost() {

        while (true) {

            _pacman._mutex.p();
            _ghost.getTargetTile(PacMan::pacman_x, PacMan::pacman_y, PacMan::pacman_dir);
            _ghost.move(PacMan::pacmanGetTileX(), PacMan::pacmanGetTileY());
            _pacman._mutex.v();
            for (volatile unsigned int j = 0; j < DE_LEI; j++);
            Thread::yield();
        }
    }

    static void runWindow()
    {
        sf::RenderWindow window(sf::VideoMode(674, 1000), "Pac Man");

        //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
        window.setKeyRepeatEnabled(false);

        int i = 0;

        while (window.isOpen())
        {
            i++;
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                     window.close();
                     break;

                // key pressed
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        // std::cout << "Keyboard esquerda!" << std::endl;
                        _window._mutex_w.p();
                        _pacman._mutex.p();
                        _pacman.changeDirection(LEFT);
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        // std::cout << "Keyboard direita!" << std::endl;
                        _window._mutex_w.p();
                        _pacman._mutex.p();
                        _pacman.changeDirection(RIGHT);
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        // std::cout << "Keyboard para baixo!" << std::endl;
                        _window._mutex_w.p();
                        _pacman._mutex.p();
                        _pacman.changeDirection(DOWN);
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        // std::cout << "Keyboard para cima!" << std::endl;
                        _window._mutex_w.p();
                        _pacman._mutex.p();
                        _pacman.changeDirection(UP);
                    } else if (event.key.code == 57) {
                        // std::cout << _ghost.getX() << ", " << _ghost.getY() << '\n';
                    } else
                        std::cout << "Keyboard pressed = " << event.key.code << std::endl;

                    // Thread::yield();
                    break;

                }
            }

            window.clear();

            for (int k = 0; k < 28; k++) {
                for (int j = 0; j < 31; j++) {
                    switch(maze[k][j]) {
                        case tile::o:
                            // draw small food
                            _window.pill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
                            window.draw(_window.pill_sprite);
                            break;
                        case tile::O:
                            // draw large food
                            _window.bigPill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
                            window.draw(_window.bigPill_sprite);
                            break;
                    }
                }
            }

            window.draw(_window.maze_sprite);
            // pac_0_sprite.setPosition(310, 398);
            // window.draw(pac_0_sprite);
            _pacman._mutex.p();
            _window._pacman_sprites[(i / 15) % 4].setPosition(PacMan::pacman_x, PacMan::pacman_y);
            _pacman._mutex.v();
            window.draw(_window._pacman_sprites[(i / 15) % 4]);

            // ghost_r_0_sprite.setPosition(315, 350);
            // window.draw(ghost_r_0_sprite);
            _window._ghost_sprites[(i / 15) % 2].setPosition(Ghost::ghost_x, Ghost::ghost_y);
            _window._ghost_sprites[2 + Ghost::ghost_dir].setPosition(Ghost::ghost_x, Ghost::ghost_y);
            window.draw(_window._ghost_sprites[(i / 15) % 2]);
            window.draw(_window._ghost_sprites[2 + Ghost::ghost_dir]);

            window.display();
            for (volatile unsigned int j = 0; j < DE_LEI; j++);

            if (i == 55440) i = 0;

            _window._mutex_w.v();
            Thread::yield();
        }
    }
};



#endif
