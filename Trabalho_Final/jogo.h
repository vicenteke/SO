#ifndef JOGO_H
#define JOGO_H

#define DE_LEI 1000000

#include <ctime>
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

    static sf::RenderWindow * _window_render;

    // Characters
    static PacMan _pacman;
    static Ghost1 _ghost1;
    static Ghost2 _ghost2;
    static Ghost3 _ghost3;
    static Ghost4 _ghost4;

    static bool _isPaused;
    static Thread * paused_thread;
    static Thread * stopComeCuDeGhost_thread;

    static void runPeriod(int seconds, void (* callBack)()) {
        std::time_t start_time = std::time(0);
        while (std::difftime(std::time(0), start_time) < seconds) {
            Thread::yield();
        }
        return callBack();
    }

    static void startComeCuDeGhost() {
        _ghost1.isScared(true);
        _ghost2.isScared(true);
        _ghost3.isScared(true);
        _ghost4.isScared(true);

        stopComeCuDeGhost_thread = new Thread(runPeriod, 4, stopComeCuDeGhost);
    }

    static void stopComeCuDeGhost() {
        _ghost1.isScared(false);
        _ghost2.isScared(false);
        _ghost3.isScared(false);
        _ghost4.isScared(false);

        delete stopComeCuDeGhost_thread;
    }

    static void runPaused() {
        while(true) {
            if (!Traits<Timer>::preemptive) {
                Thread::yield();
            }
        }
    }

    static void loseLife() {
        if (--_lives > 0) {
            Tiles::resetTiles();

            _pacman = PacMan(_window.getPacmanSprites(), 4);
            _ghost1 = Ghost1(&(_window.getGhostSprites(1)[2]), _window.getGhostSprites(1), 2);
            _ghost2 = Ghost2(&(_window.getGhostSprites(2)[2]), _window.getGhostSprites(2), 2);
            _ghost3 = Ghost3(&(_window.getGhostSprites(3)[2]), _window.getGhostSprites(3), 2);
            _ghost4 = Ghost4(&(_window.getGhostSprites(4)[2]), _window.getGhostSprites(4), 2);
            _isPaused = false;
            _foods = 240;
        } else {
            _isPaused = true;
            paused_thread = new Thread(runPaused);
            // finishGame();
        }
    }

    static void finishGame() {
        _window_render->close();
        if (paused_thread) delete paused_thread;
        if (stopComeCuDeGhost_thread) delete stopComeCuDeGhost_thread;
    }

    static void restartGame() {
        _lives = 4;
        _score = 0;
        if (_isPaused) delete paused_thread;
        _isPaused = false;
        loseLife();
    }

    static void runPacman() {

        while (true) {

            if (_isPaused) {
                int status = paused_thread->join();
            } else {
                switch(_pacman.move()) {
                    case 10:
                        Jogo::_score += 10;
                        Jogo::_foods--;
                        std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                        break;
                    case 20:
                        Jogo::_score += 20;
                        startComeCuDeGhost();
                        std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                        break;
                }
                for (volatile unsigned int j = 0; j < DE_LEI; j++);
                Thread::yield();
            }
        }
    }

    static void runGhost() {

        int lost = 0;

        while (true) {

            if (_isPaused) {
                int status = paused_thread->join();
            } else {
                _pacman._mutex.p();
                int pm_x = PacMan::pacman_x;
                int pm_y = PacMan::pacman_y;
                Direction pm_d = PacMan::pacman_dir;
                int pm_t_x = PacMan::pacmanGetNearTileX();
                int pm_t_y = PacMan::pacmanGetNearTileY();
                _pacman._mutex.v();

                _ghost1.getTargetTile(pm_x, pm_y, pm_d);
                lost += _ghost1.move(pm_t_x, pm_t_y);
                _ghost2.getTargetTile(pm_x, pm_y, pm_d);
                lost += _ghost2.move(pm_t_x, pm_t_y);
                _ghost3.getTargetTile(pm_x, pm_y, pm_d);
                lost += _ghost3.move(pm_t_x, pm_t_y);
                _ghost4.getTargetTile(pm_x, pm_y, pm_d);
                lost += _ghost4.move(pm_t_x, pm_t_y);

                if (lost > 0) {
                    lost = 0;
                    loseLife();
                }
                for (volatile unsigned int j = 0; j < DE_LEI; j++);
                Thread::yield();
            }
        }
    }

    static void runInput() {
        while (_window_render->isOpen())
        {
            sf::Event event;
            while (_window_render->pollEvent(event))
            {
                switch (event.type) {

                    case sf::Event::Closed:
                         _window_render->close();
                         break;

                    // key pressed
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            // std::cout << "Keyboard esquerda!" << std::endl;
                            if (PacMan::pacman_dir != LEFT && !_isPaused) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(LEFT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            // std::cout << "Keyboard direita!" << std::endl;
                            if (PacMan::pacman_dir != RIGHT && !_isPaused) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(RIGHT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            // std::cout << "Keyboard para baixo!" << std::endl;
                            if (PacMan::pacman_dir != DOWN && !_isPaused) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(DOWN);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            // std::cout << "Keyboard para cima!" << std::endl;
                            if (PacMan::pacman_dir != UP && !_isPaused) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(UP);
                            }
                        } else if (event.key.code == 15) {
                            _isPaused = !_isPaused;
                            if (_isPaused) {
                                paused_thread = new Thread(runPaused);
                            } else {
                                delete paused_thread;
                            }
                            Thread::yield();
                        } else if (event.key.code == 16) {
                            finishGame();
                        } else if (event.key.code == 17) {
                            restartGame();
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
        _window_render = &window;

        //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
        window.setKeyRepeatEnabled(false);

        int i = 0;

        Thread input_thread = Thread(runInput);

        while (window.isOpen())
        {
            if (_isPaused) {
                int status = paused_thread->join();
            } else {

                i++;

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
                                if (i % 60 > 30) {
                                    _window.bigPill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
                                    window.draw(_window.bigPill_sprite);
                                }
                                break;
                        }
                    }
                }

                window.draw(_window.maze_sprite);

                // Draw PacMan
                _pacman._mutex.p();
                _window._pacman_sprites[(i / 15) % 4].setPosition(PacMan::pacman_x, PacMan::pacman_y);
                _pacman._mutex.v();
                window.draw(_window._pacman_sprites[(i / 15) % 4]);

                // Draw Ghost 1
                if (!_ghost1.isScared()) {
                    _window._ghost_sprites[(i / 15) % 2].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                    window.draw(_window._ghost_sprites[(i / 15) % 2]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }
                _window._ghost_sprites[2 + Ghost1::ghost1_dir].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                window.draw(_window._ghost_sprites[2 + Ghost1::ghost1_dir]);

                // Draw Ghost 2
                if (!_ghost2.isScared()) {
                    _window._ghost_sprites2[(i / 15) % 2].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                    window.draw(_window._ghost_sprites2[(i / 15) % 2]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }
                _window._ghost_sprites2[2 + Ghost2::ghost2_dir].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                window.draw(_window._ghost_sprites2[2 + Ghost2::ghost2_dir]);

                // Draw Ghost 3
                if (!_ghost3.isScared()) {
                    _window._ghost_sprites3[(i / 15) % 2].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                    window.draw(_window._ghost_sprites3[(i / 15) % 2]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }
                _window._ghost_sprites3[2 + Ghost3::ghost3_dir].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                window.draw(_window._ghost_sprites3[2 + Ghost3::ghost3_dir]);

                // Draw Ghost 4
                if (!_ghost4.isScared()) {
                    _window._ghost_sprites4[(i / 15) % 2].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                    window.draw(_window._ghost_sprites4[(i / 15) % 2]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }
                _window._ghost_sprites4[2 + Ghost4::ghost4_dir].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                window.draw(_window._ghost_sprites4[2 + Ghost4::ghost4_dir]);

                window.display();
                for (volatile unsigned int j = 0; j < DE_LEI; j++);

                if (i == 55440) i = 0;

                // _window._mutex_w.v();
                Thread::yield();
            }
        }
    }
};



#endif
