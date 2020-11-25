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
#include <iostream>
#include <fstream>
#include <string>

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
        _semaphore_pause.p();
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
    static int _highscore;

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
    static Semaphore fuck_this;

    static bool isPaused() {
        fuck_this.p();
        bool aux = _isPaused;
        fuck_this.v();
        return aux;
    }

    static Semaphore _semaphore_pause;

    static void runPeriod(int seconds, void (* callBack)()) {
        std::time_t start_time = std::time(0);
        std::time_t paused_time = start_time;
        while (std::difftime(std::time(0), start_time) < seconds) {
            if(isPaused()) {
                if (int aux = std::difftime(std::time(0), paused_time) > 0) {
                    seconds += aux;
                    paused_time = std::time(0);
                }
            }
            if (Traits<Timer>::preemptive)
                for (volatile int i = 0; i < 50000; i++);
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
            if (Traits<Timer>::preemptive)
                for (volatile int i = 0; i < 50000; i++);
            else Thread::yield();
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
            if (Traits<Timer>::preemptive)
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
        if (Traits<Timer>::preemptive && isPaused()) delete paused_thread;
        _isPaused = false;
        loseLife();
    }

    static void runPacman() {

        while (true) {

            if (isPaused()) {
                if (Traits<Timer>::preemptive)
                    int status = paused_thread->join();
                else
                // std::cout << '2';
                    _semaphore_pause.p();
                // std::cout << '3';
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

            if (isPaused()) {
                if (Traits<Timer>::preemptive)
                    int status = paused_thread->join();
                else
                // std::cout << '4';
                _semaphore_pause.p();
                // std::cout << '5';
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
                            if (PacMan::pacman_dir != LEFT && !isPaused()) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(LEFT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            // std::cout << "Keyboard direita!" << std::endl;
                            if (PacMan::pacman_dir != RIGHT && !isPaused()) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(RIGHT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            // std::cout << "Keyboard para baixo!" << std::endl;
                            if (PacMan::pacman_dir != DOWN && !isPaused()) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(DOWN);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            // std::cout << "Keyboard para cima!" << std::endl;
                            if (PacMan::pacman_dir != UP && !isPaused()) {
                                // _window._mutex_w.p();
                                _pacman._mutex.p();
                                _pacman.changeDirection(UP);
                            }
                        } else if (event.key.code == 15) {
                            _isPaused = !isPaused();
                            if (isPaused()) {
                                if (Traits<Timer>::preemptive) {
                                    paused_thread = new Thread(runPaused);
                                    // Thread::yield();
                                }
                                // _semaphore_pause.p();
                            } else {
                                if (!Traits<Timer>::preemptive)
                                    _semaphore_pause.wakeup_all();
                                else delete paused_thread;
                            }
                            // Thread::yield();
                        } else if (event.key.code == 16) {
                            finishGame();
                        } else if (event.key.code == 17) {
                            restartGame();
                        } else if (event.key.code == 57) {
                            // std::cout << _pacman.getTileX() << ", " << _pacman.getTileY() << '\n';
                        } else
                            std::cout << "Keyboard pressed = " << event.key.code << std::endl;
                        break;

                }
            }
            if (Traits<Timer>::preemptive && isPaused())
                for (volatile int i = 0; i < DE_LEI; i++);
            // std::cout << '9';
            Thread::yield();
        }
    }

    static void runWindow()
    {
        sf::RenderWindow window(sf::VideoMode(674, 810), "Pac Man");
        _window_render = &window;

        //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
        window.setKeyRepeatEnabled(false);

        std::ifstream myFile;
        myFile.open("recorde.txt");
        std::string helper;
        getline(myFile, helper);
        _highscore = std::stoi(helper);
        std::cout << _highscore;

        int i = 0;

        Thread input_thread = Thread(runInput);

        while (window.isOpen())
        {
            if (isPaused()) {
                _window.pause_sprite.setPosition(288,405);
                window.draw(_window.pause_sprite);
                window.display();
                if (Traits<Timer>::preemptive)
                    int status = paused_thread->join();
                else
                // std::cout << '0';
                    _semaphore_pause.p();
                // std::cout << '1';
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

                //Draw Score
                _window.score_sprite.setPosition(0,745);
                window.draw(_window.score_sprite);
                int _score_held = _score;
                for (int aa = 0; aa < 8; aa++){
                    int digito = _score_held % 10;
                    _score_held /= 10;
                    _window.num_sprite[aa].setTexture(_window.num_tex[digito]);
                    _window.num_sprite[aa].setPosition((125+ 7*24 - aa*24 ),745);
                    window.draw(_window.num_sprite[aa]);
                }

                // Draw PacMan
                _pacman._mutex.p();
                _window._pacman_sprites[(i / 15) % 4].setPosition(PacMan::pacman_x, PacMan::pacman_y);
                _pacman._mutex.v();
                window.draw(_window._pacman_sprites[(i / 15) % 4]);

                // Draw Ghost 1
                if (!_ghost1.isScared()) {
                    _window._ghost_sprites[(i / 15) % 2].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                    window.draw(_window._ghost_sprites[(i / 15) % 2]);
                    _window._ghost_sprites[2 + Ghost1::ghost1_dir - (Ghost1::ghost1_dir == STOPPED)].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                    window.draw(_window._ghost_sprites[2 + Ghost1::ghost1_dir - (Ghost1::ghost1_dir == STOPPED)]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }

                // Draw Ghost 2
                if (!_ghost2.isScared()) {
                    _window._ghost_sprites2[(i / 15) % 2].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                    window.draw(_window._ghost_sprites2[(i / 15) % 2]);
                    _window._ghost_sprites2[2 + Ghost2::ghost2_dir - (Ghost2::ghost2_dir == STOPPED)].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                    window.draw(_window._ghost_sprites2[2 + Ghost2::ghost2_dir - (Ghost2::ghost2_dir == STOPPED)]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }

                // Draw Ghost 3
                if (!_ghost3.isScared()) {
                    _window._ghost_sprites3[(i / 15) % 2].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                    window.draw(_window._ghost_sprites3[(i / 15) % 2]);
                    _window._ghost_sprites3[2 + Ghost3::ghost3_dir - (Ghost3::ghost3_dir == STOPPED)].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                    window.draw(_window._ghost_sprites3[2 + Ghost3::ghost3_dir - (Ghost3::ghost3_dir == STOPPED)]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }

                // Draw Ghost 4
                if (!_ghost4.isScared()) {
                    _window._ghost_sprites4[(i / 15) % 2].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                    window.draw(_window._ghost_sprites4[(i / 15) % 2]);
                    _window._ghost_sprites4[2 + Ghost4::ghost4_dir - (Ghost4::ghost4_dir == STOPPED)].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                    window.draw(_window._ghost_sprites4[2 + Ghost4::ghost4_dir - (Ghost4::ghost4_dir == STOPPED)]);
                } else {
                    _window._scared_sprites[(i / 15) % 4].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                    window.draw(_window._scared_sprites[(i / 15) % 4]);
                }

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
