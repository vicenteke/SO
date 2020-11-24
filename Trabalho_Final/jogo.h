#ifndef JOGO_H
#define JOGO_H

#define DE_LEI 800000

#include "thread.h"
#include "window.h"
#include "pacman.h"
#include "ghost1.h"
#include "ghost2.h"
#include "ghost3.h"
#include "ghost4.h"

__USING_API

class Jogo {
public:
    Jogo() {

        // _window = Window();
        _pacman = PacMan(_window.getPacmanSprites(), 4);
        _ghost1 = Ghost1(&(_window.getGhostSprites(1)[2]), _window.getGhostSprites(1), 2);
        _ghost2 = Ghost2(&(_window.getGhostSprites(2)[2]), _window.getGhostSprites(2), 2);
        _ghost3 = Ghost3(&(_window.getGhostSprites(3)[2]), _window.getGhostSprites(3), 2);
        _ghost4 = Ghost4(&(_window.getGhostSprites(4)[2]), _window.getGhostSprites(4), 2);
        //
        // run();

        _isPaused = false;
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
    static Ghost1 _ghost1;
    static Ghost2 _ghost2;
    static Ghost3 _ghost3;
    static Ghost4 _ghost4;

    static bool _isPaused;
    static Thread * paused_thread;

    static void runPacman() {

        while (true) {

            if (_isPaused) {
                int status = paused_thread->join();
            }

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

            if (_isPaused) {
                int status = paused_thread->join();
            }

            _pacman._mutex.p();
            int pm_x = PacMan::pacman_x;
            int pm_y = PacMan::pacman_y;
            Direction pm_d = PacMan::pacman_dir;
            int pm_t_x = PacMan::pacmanGetNearTileX();
            int pm_t_y = PacMan::pacmanGetNearTileY();
            _pacman._mutex.v();

            _ghost1.getTargetTile(pm_x, pm_y, pm_d);
            _ghost1.move(pm_t_x, pm_t_y);
            _ghost2.getTargetTile(pm_x, pm_y, pm_d);
            _ghost2.move(pm_t_x, pm_t_y);
            _ghost3.getTargetTile(pm_x, pm_y, pm_d);
            _ghost3.move(pm_t_x, pm_t_y);
            _ghost4.getTargetTile(pm_x, pm_y, pm_d);
            _ghost4.move(pm_t_x, pm_t_y);
            for (volatile unsigned int j = 0; j < DE_LEI; j++);
            Thread::yield();
        }
    }

    static void runInput(sf::RenderWindow * window) {
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                switch (event.type) {

                    case sf::Event::Closed:
                         window->close();
                         break;

                    // key pressed
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            // std::cout << "Keyboard esquerda!" << std::endl;
                            if (PacMan::pacman_dir != LEFT) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(LEFT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            // std::cout << "Keyboard direita!" << std::endl;
                            if (PacMan::pacman_dir != RIGHT) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(RIGHT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            // std::cout << "Keyboard para baixo!" << std::endl;
                            if (PacMan::pacman_dir != DOWN) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(DOWN);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            // std::cout << "Keyboard para cima!" << std::endl;
                            if (PacMan::pacman_dir != UP) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(UP);
                            }
                        } else if (event.key.code == 15) {
                            _isPaused = !_isPaused;
                            if (_isPaused) {
                                
                            } else {

                            }
                        } else if (event.key.code == 57) {
                            std::cout << _pacman.getTileX() << ", " << _pacman.getTileY() << '\n';
                        } else
                            std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                        break;

                }
            }
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

        Thread input_thread = Thread(runInput, &window);

        while (window.isOpen())
        {
            if (_isPaused) {
                int status = paused_thread->join();
            }

            i++;
            // sf::Event event;
            // while (window.pollEvent(event))
            // {
            //     switch (event.type) {
            //     case sf::Event::Closed:
            //          window.close();
            //          break;
            //
            //     // key pressed
            //     case sf::Event::KeyPressed:
            //         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            //             // std::cout << "Keyboard esquerda!" << std::endl;
            //             if (PacMan::pacman_dir != LEFT) {
            //                 _window._mutex_w.p();
            //                 _pacman._mutex.p();
            //                 _pacman.changeDirection(LEFT);
            //             }
            //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //             // std::cout << "Keyboard direita!" << std::endl;
            //             if (PacMan::pacman_dir != RIGHT) {
            //                 _window._mutex_w.p();
            //                 _pacman._mutex.p();
            //                 _pacman.changeDirection(RIGHT);
            //             }
            //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            //             // std::cout << "Keyboard para baixo!" << std::endl;
            //             if (PacMan::pacman_dir != DOWN) {
            //                 _window._mutex_w.p();
            //                 _pacman._mutex.p();
            //                 _pacman.changeDirection(DOWN);
            //             }
            //         } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //             // std::cout << "Keyboard para cima!" << std::endl;
            //             if (PacMan::pacman_dir != UP) {
            //                 _window._mutex_w.p();
            //                 _pacman._mutex.p();
            //                 _pacman.changeDirection(UP);
            //             }
            //         } else if (event.key.code == 57) {
            //             std::cout << _pacman.getTileX() << ", " << _pacman.getTileY() << '\n';
            //         } else
            //             std::cout << "Keyboard pressed = " << event.key.code << std::endl;
            //
            //         // Thread::yield();
            //         break;
            //
            //     }
            // }

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
            _window._ghost_sprites[(i / 15) % 2].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
            _window._ghost_sprites[2 + Ghost1::ghost1_dir].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
            window.draw(_window._ghost_sprites[(i / 15) % 2]);
            window.draw(_window._ghost_sprites[2 + Ghost1::ghost1_dir]);

            _window._ghost_sprites2[(i / 15) % 2].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
            _window._ghost_sprites2[2 + Ghost2::ghost2_dir].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
            window.draw(_window._ghost_sprites2[(i / 15) % 2]);
            window.draw(_window._ghost_sprites2[2 + Ghost2::ghost2_dir]);

            _window._ghost_sprites3[(i / 15) % 2].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
            _window._ghost_sprites3[2 + Ghost3::ghost3_dir].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
            window.draw(_window._ghost_sprites3[(i / 15) % 2]);
            window.draw(_window._ghost_sprites3[2 + Ghost3::ghost3_dir]);

            _window._ghost_sprites4[(i / 15) % 2].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
            _window._ghost_sprites4[2 + Ghost4::ghost4_dir].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
            window.draw(_window._ghost_sprites4[(i / 15) % 2]);
            window.draw(_window._ghost_sprites4[2 + Ghost4::ghost4_dir]);

            window.display();
            for (volatile unsigned int j = 0; j < DE_LEI; j++);

            if (i == 55440) i = 0;

            // _window._mutex_w.v();
            Thread::yield();
        }
    }
};



#endif
