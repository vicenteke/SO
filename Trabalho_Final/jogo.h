#ifndef JOGO_H
#define JOGO_H

#define DELAY 651000

#include "window.h"
#include "thread.h"
#include "pacman.h"
#include "ghost1.h"
#include "ghost2.h"
#include "ghost3.h"
#include "ghost4.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

__USING_API

class Jogo {
public:
    Jogo() {

        // _window = Window();

        _pacman = new PacMan(_window.getPacmanSprites(), 4);
        _ghost1 = new Ghost1(&(_window.getGhostSprites(1)[2]), _window.getGhostSprites(1), 2);
        _ghost2 = new Ghost2(&(_window.getGhostSprites(2)[2]), _window.getGhostSprites(2), 2);
        _ghost3 = new Ghost3(&(_window.getGhostSprites(3)[2]), _window.getGhostSprites(3), 2);
        _ghost4 = new Ghost4(&(_window.getGhostSprites(4)[2]), _window.getGhostSprites(4), 2);
        //
        // run();

        isPaused(false);
        isStarting(true);
        _semaphore_pause.p();
    }

    ~Jogo() {
        // finishGame();
        if (_pacman) delete _pacman;
        if (_ghost1) delete _ghost1;
        if (_ghost2) delete _ghost2;
        if (_ghost3) delete _ghost3;
        if (_ghost4) delete _ghost4;
        for (int i = 0; i < 5; i++) {
            if (_ghost_threads[i]) delete _ghost_threads[i];
        }
    }

    static void run(void *) {

        // Get _highscore
        std::ifstream myFile;
        myFile.open("recorde.txt");
        std::string helper;
        getline(myFile, helper);
        _highscore = std::stoi(helper);
        myFile.close();

        // Start Threads
        _ghost_threads[4] = new Thread(runGhost);
        Thread window_thread = Thread(runWindow);
        Thread pacman_thread = Thread(runPacman);

        int ghost_status = _ghost_threads[4]->join();
        int window_status = window_thread.join();
        int pacman_status = pacman_thread.join();
    }

    static Window _window;

    // Game stats
    static int _lives;
    static int _foods;
    static int _score;
    static int _highscore;

    static void timerJail(int ghost) {

        if (ghost <= 0) return;
        _score += 200;

        switch(ghost) {
            case 1:
                timerJail_thread[0] = new Thread(Jogo::runPeriod, (int)(std::time(0) % 7) + 1, getOutJail, 1);
                break;
            case 2:
                timerJail_thread[1] = new Thread(Jogo::runPeriod, (int)(std::time(0) % 7) + 1, getOutJail, 2);
                break;
            case 3:
                timerJail_thread[2] = new Thread(Jogo::runPeriod, (int)(std::time(0) % 7) + 1, getOutJail, 3);
                break;
            case 4:
                timerJail_thread[3] = new Thread(Jogo::runPeriod, (int)(std::time(0) % 7) + 1, getOutJail, 4);
                break;
        }
    }

private:

    static sf::RenderWindow * _window_render;

    // Characters
    static PacMan * _pacman;
    static Ghost1 * _ghost1;
    static Ghost2 * _ghost2;
    static Ghost3 * _ghost3;
    static Ghost4 * _ghost4;

    static Thread * _ghost_threads[5];
    static bool _isStarting;

    static bool _isPaused;
    static Semaphore _mutex_paused;

    static Thread * stopChase_thread;
    static Thread * timerJail_thread[4];

    static Thread * _score100_thread;

    static Semaphore _semaphore_pause;

    static bool isPaused() {
        _mutex_paused.p();
        bool aux = _isPaused;
        _mutex_paused.v();
        return aux;
    }

    static bool isStarting() {
        _mutex_paused.p();
        bool aux = _isStarting;
        _mutex_paused.v();
        return aux;
    }

    static void isPaused(bool b) {
        _mutex_paused.p();
        _isPaused = b;
        _mutex_paused.v();
    }

    static void isStarting(bool b) {
        _mutex_paused.p();
        _isStarting = b;
        _mutex_paused.v();
    }

    static void runPeriod(int seconds, void (* callBack)(int), int a = 0) {
        std::time_t start_time = std::time(0);
        std::time_t paused_time = start_time;
        while (std::difftime(std::time(0), start_time) < seconds) {
            if(isPaused() && a >= 0) {
                if (int aux = std::difftime(std::time(0), paused_time) > 0) {
                    seconds += aux;
                    paused_time = std::time(0);
                }
            }
            if (Traits<Timer>::preemptive)
                for (volatile int i = 0; i < 50000; i++);
            Thread::yield();
        }
        return callBack(a);
    }

    static void getOutJail(int ghost) {

        // isPaused(true);
        // if (Traits<Timer>::preemptive) {
        //     paused_thread = new Thread(runPaused);
        //     // Thread::yield();
        // }
        // _window._mutex_w.p();
        switch(ghost) {
            case 1:
                // _ghost1->_mutex.p();
                delete _ghost1;
                _ghost1 = new Ghost1(&(_window.getGhostSprites(1)[2]), _window.getGhostSprites(1), 2);
                // _ghost1->_mutex.v();
                break;
            case 2:
                // _ghost2->_mutex.p();
                delete _ghost2;
                _ghost2 = new Ghost2(&(_window.getGhostSprites(2)[2]), _window.getGhostSprites(2), 2);
                // _ghost2->_mutex.v();
                break;
            case 3:
                // _ghost3->_mutex.p();
                delete _ghost3;
                _ghost3 = new Ghost3(&(_window.getGhostSprites(3)[2]), _window.getGhostSprites(3), 2);
                // _ghost3->_mutex.v();
                break;
            case 4:
                // _ghost4->_mutex.p();
                delete _ghost4;
                _ghost4 = new Ghost4(&(_window.getGhostSprites(4)[2]), _window.getGhostSprites(4), 2);
                // _ghost4->_mutex.v();
                break;
        }
        // _window._mutex_w.v();
        delete timerJail_thread[ghost - 1];
        // if (!Traits<Timer>::preemptive)
        //     _semaphore_pause.wakeup_all();
        // else delete paused_thread;
    }

    static void startChase() {
        _ghost1->isScared(true);
        _ghost2->isScared(true);
        _ghost3->isScared(true);
        _ghost4->isScared(true);

        stopChase_thread = new Thread(runPeriod, 4, stopChase, 0);
    }

    static void stopChase(int) {
        _ghost1->isScared(false);
        _ghost2->isScared(false);
        _ghost3->isScared(false);
        _ghost4->isScared(false);

        delete stopChase_thread;
    }

    static void remove100(int) {
        Personagem::setTile(13, 13, tiles::u);
        if (_score100_thread) delete _score100_thread;
    }

    static void loseLife() {

        if (--_lives > 0) {

            tiles aux = Personagem::getTile(13, 13);
            if(aux == tiles::F || aux == tiles::f)
                Personagem::setTile(13, 13, tiles::u);

            // _window._mutex_w.p();
            delete _pacman;
            _pacman = new PacMan(_window.getPacmanSprites(), 4);
            delete _ghost1;
            _ghost1 = new Ghost1(&(_window.getGhostSprites(1)[2]), _window.getGhostSprites(1), 2);
            delete _ghost2;
            _ghost2 = new Ghost2(&(_window.getGhostSprites(2)[2]), _window.getGhostSprites(2), 2);
            delete _ghost3;
            _ghost3 = new Ghost3(&(_window.getGhostSprites(3)[2]), _window.getGhostSprites(3), 2);
            delete _ghost4;
            _ghost4 = new Ghost4(&(_window.getGhostSprites(4)[2]), _window.getGhostSprites(4), 2);
            // _window._mutex_w.v();

            isPaused(false);
            _semaphore_pause.wakeup_all();

            _ghost1->updatePosition(265, 334);
            _ghost2->updatePosition(298, 334);
            _ghost3->updatePosition(331, 334);
            _ghost4->updatePosition(365, 334);

            isStarting(true);

            for (volatile int j = 0; j < 100; j++) {
                for (volatile int k = 0; k < DELAY * 2; k++);
                Thread::yield();
            }

            isStarting(false);
            // Thread::yield();
        } else {
            if (!isPaused()) {
                isPaused(true);
                for (volatile int i = 0; i < DELAY * 6; i++);
                if (_score > _highscore) {
                    std::ofstream myFile;
                    myFile.open("recorde.txt", std::ofstream::trunc);
                    myFile << std::to_string(_score);
                    myFile.close();
                    _highscore = _score;
                }
            }
            Thread::yield();
            // finishGame();
        }
    }

    static void drawLives() {
        // _window._mutex_w.p();
        if (_lives > 0) {
            _window.life_sprite.setPosition(625, 750);
            _window_render->draw(_window.life_sprite);
            if (_lives > 1) {
                _window.life_sprite.setPosition(580, 750);
                _window_render->draw(_window.life_sprite);
                if (_lives > 2) {
                    _window.life_sprite.setPosition(535, 750);
                    _window_render->draw(_window.life_sprite);
                }
            }
        }
        // _window._mutex_w.v();
    }

    static void finishGame() {
        _window_render->close();
        // _window._mutex_w.v();
        // if (_ghost1) delete _ghost1;
        // if (_ghost2) delete _ghost2;
        // if (_ghost3) delete _ghost3;
        // if (_ghost4) delete _ghost4;
        // if (paused_thread) delete paused_thread;
        if (stopChase_thread) delete stopChase_thread;
        for (int i = 0; i < 4; i++) {
            if (timerJail_thread[i]) delete timerJail_thread[i];
        }
    }

    static void restartGame() {
        Tiles::resetTiles();
        _lives = 4;
        _score = 0;
        _foods = 240;
        // if (Traits<Timer>::preemptive && paused_thread) delete paused_thread;
        // isPaused(false);
        // if (!Traits<Timer>::preemptive)
        //     _semaphore_pause.wakeup_all();
        //
        // if (_ghost_threads[3]) delete _ghost_threads[3];
        // if (_ghost_threads[2]) delete _ghost_threads[2];
        // if (_ghost_threads[1]) delete _ghost_threads[1];
        // if (_ghost_threads[0]) delete _ghost_threads[0];

        loseLife();
    }

    static void runPacman() {

        bool done = false;

        while (true) {

            if (isStarting()) {
                while (isStarting()) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }
            }

            if (isPaused()) {
                if (!done) {
                    done = true;
                    // if (Traits<Timer>::preemptive)
                    // int status = paused_thread->join();
                    // else
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    // for (volatile int k = 0; k < DELAY * 4; k++);
                }
            }
            done = false;
            switch(_pacman->move()) {
                case 1:
                    Jogo::_score += 10;
                    Jogo::_foods--;
                    // std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                    break;
                case 2:
                    Jogo::_score += 50;
                    startChase();
                    // std::cout << "Score: " << Jogo::_score << " | Foods: " << Jogo::_foods << " | Lives: " << Jogo::_lives << '\n';
                    break;
                case 3:
                    Jogo::_score += 100;
                    _score100_thread = new Thread(runPeriod, 2, remove100, 0);
                    break;
            }

            if (_foods == 170 || _foods == 70)
                Personagem::setTile(13, 13, tiles::F);
            else if (_foods <= 0)
                isPaused(true);

            for (volatile unsigned int j = 0; j < DELAY; j++);
            Thread::yield();
        }
    }

    static void runGhost() {

        _ghost1->updatePosition(265, 334);
        _ghost2->updatePosition(298, 334);
        _ghost3->updatePosition(331, 334);
        _ghost4->updatePosition(365, 334);

        // if (_ghost_threads[3]) delete _ghost_threads[3];
        // if (_ghost_threads[2]) delete _ghost_threads[2];
        // if (_ghost_threads[1]) delete _ghost_threads[1];
        // if (_ghost_threads[0]) delete _ghost_threads[0];

        for (volatile int j = 0; j < 40; j++) {
            for (volatile int k = 0; k < DELAY * 5; k++);
            Thread::yield();
        }

        isStarting(false);
        _ghost_threads[0] = new Thread(runGhost1);
        // for (volatile int j = 0; j < 67; j++) {
        //     for (volatile int k = 0; k < DELAY; k++);
        //     Thread::yield();
        // }

        _ghost_threads[1] = new Thread(runGhost2);
        // for (volatile int j = 0; j < 133; j++) {
        //     for (volatile int k = 0; k < DELAY * 2 / 3; k++);
        //     Thread::yield();
        // }

        _ghost_threads[2] = new Thread(runGhost3);
        // for (volatile int j = 0; j < 200; j++) {
        //     for (volatile int k = 0; k < DELAY / 3; k++);
        //     Thread::yield();
        // }

        _ghost_threads[3] = new Thread(runGhost4);

        int status;
        status = _ghost_threads[0] ? _ghost_threads[0]->join() : 0;
        status = _ghost_threads[1] ? _ghost_threads[1]->join() : 0;
        status = _ghost_threads[2] ? _ghost_threads[2]->join() : 0;
        status = _ghost_threads[3] ? _ghost_threads[3]->join() : 0;
    }

    static void runGhost1() {
        int lost = 0;
        bool done = false;

        // for (volatile int j = 0; j < 200; j++) {
        //     for (volatile int k = 0; k < DELAY / 3; k++);
        //     Thread::yield();
        // }

        while (true) {

            if (isStarting()) {
                _ghost1->updatePosition(265, 334);
                STARTING:
                while (isStarting()) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }

                // for (volatile int j = 0; j < 200; j++) {
                //     for (volatile int k = 0; k < DELAY / 3; k++);
                //     Thread::yield();
                // }
            }

            if (isPaused()) {
                if (!done) {
                    done = true;
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    for (volatile int k = 0; k < DELAY * 4; k++);
                }
            } else {
                done = false;
                // if (_pacman) _pacman->_mutex.p();
                Direction pm_d = PacMan::pacman_dir;
                int pm_t_x = PacMan::pacmanGetNearTileX();
                int pm_t_y = PacMan::pacmanGetNearTileY();
                // _pacman->_mutex.v();

                _ghost1->getTargetTile(pm_t_x, pm_t_y, pm_d);
                lost = _ghost1->move(pm_t_x, pm_t_y);

                if (lost == 1) {
                    lost = 0;
                    _ghost1->updatePosition(265, 334);
                    loseLife();
                    goto STARTING;
                }
            }
            for (volatile unsigned int j = 0; j < DELAY / 3; j++);
            Thread::yield();
        }
    }

    static void runGhost2() {
        int lost = 0;
        bool done = false;

        for (volatile int j = 0; j < 200; j++) {
            for (volatile int k = 0; k < DELAY / 3; k++);
            Thread::yield();
        }

        while (true) {

            if (isStarting()) {
                _ghost2->updatePosition(298, 334);
                STARTING:
                while (isStarting()) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }

                for (volatile int j = 0; j < 200; j++) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }
            }

            if (isPaused()) {
                if (!done) {
                    done = true;
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    for (volatile int k = 0; k < DELAY * 4; k++);
                }
            } else {
                done = false;
                // _pacman->_mutex.p();
                Direction pm_d = PacMan::pacman_dir;
                int pm_t_x = PacMan::pacmanGetNearTileX();
                int pm_t_y = PacMan::pacmanGetNearTileY();
                // _pacman->_mutex.v();

                _ghost2->getTargetTile(pm_t_x, pm_t_y, pm_d);
                lost = _ghost2->move(pm_t_x, pm_t_y);

                if (lost == 1) {
                    lost = 0;
                    _ghost2->updatePosition(298, 334);
                    loseLife();
                    goto STARTING;
                }
            }
            for (volatile unsigned int j = 0; j < DELAY / 3; j++);
            Thread::yield();
        }
    }

    static void runGhost3() {
        int lost = 0;
        bool done = false;

        for (volatile int j = 0; j < 400; j++) {
            for (volatile int k = 0; k < DELAY / 3; k++);
            Thread::yield();
        }

        while (true) {

            if (isStarting()) {
                _ghost3->updatePosition(331, 334);
                STARTING:
                while (isStarting()) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }

                for (volatile int j = 0; j < 400; j++) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }
            }

            if (isPaused()) {
                if (!done) {
                    done = true;
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    for (volatile int k = 0; k < DELAY * 4; k++);
                }
            } else {
                done = false;
                // _pacman->_mutex.p();
                Direction pm_d = PacMan::pacman_dir;
                int pm_t_x = PacMan::pacmanGetNearTileX();
                int pm_t_y = PacMan::pacmanGetNearTileY();
                // _pacman->_mutex.v();

                _ghost3->getTargetTile(pm_t_x, pm_t_y, pm_d);
                lost = _ghost3->move(pm_t_x, pm_t_y);

                if (lost == 1) {
                    lost = 0;
                    _ghost3->updatePosition(331, 334);
                    loseLife();
                    goto STARTING;
                }
            }
            for (volatile unsigned int j = 0; j < DELAY / 3; j++);
            Thread::yield();
        }
    }

    static void runGhost4() {
        int lost = 0;
        bool done = false;

        for (volatile int j = 0; j < 600; j++) {
            for (volatile int k = 0; k < DELAY / 3; k++);
            Thread::yield();
        }

        while (true) {

            if (isStarting()) {
                _ghost4->updatePosition(365, 334);
                STARTING:
                while (isStarting()) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }

                for (volatile int j = 0; j < 600; j++) {
                    for (volatile int k = 0; k < DELAY / 3; k++);
                    Thread::yield();
                }
            }

            if (isPaused()) {
                if (!done) {
                    done = true;
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    for (volatile int k = 0; k < DELAY * 4; k++);
                }
            } else {
                done = false;
                // _pacman->_mutex.p();
                Direction pm_d = PacMan::pacman_dir;
                int pm_t_x = PacMan::pacmanGetNearTileX();
                int pm_t_y = PacMan::pacmanGetNearTileY();
                // _pacman->_mutex.v();

                _ghost4->getTargetTile(pm_t_x, pm_t_y, pm_d);
                lost = _ghost4->move(pm_t_x, pm_t_y);

                if (lost == 1) {
                    lost = 0;
                    _ghost4->updatePosition(365, 334);
                    loseLife();
                    goto STARTING;
                }
            }
            for (volatile unsigned int j = 0; j < DELAY / 3; j++);
            Thread::yield();
        }
    }

    static void runInput() {
        while (_window_render->isOpen())
        {
            // _window._mutex_w.p();
            sf::Event event;
            while (_window_render->pollEvent(event))
            {
                switch (event.type) {

                    case sf::Event::Closed:
                         // _window_render->close();
                         finishGame();
                         break;

                    // key pressed
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            // std::cout << "Keyboard esquerda!" << std::endl;
                            if (PacMan::pacman_dir != LEFT && !isPaused()) {
                                // _window._mutex_w.p();
                                // _pacman->_mutex.p();
                                _pacman->changeDirection(LEFT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            // std::cout << "Keyboard direita!" << std::endl;
                            if (PacMan::pacman_dir != RIGHT && !isPaused()) {
                                // _window._mutex_w.p();
                                // _pacman->_mutex.p();
                                _pacman->changeDirection(RIGHT);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            // std::cout << "Keyboard para baixo!" << std::endl;
                            if (PacMan::pacman_dir != DOWN && !isPaused()) {
                                // _window._mutex_w.p();
                                // _pacman->_mutex.p();
                                _pacman->changeDirection(DOWN);
                            }
                        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            // std::cout << "Keyboard para cima!" << std::endl;
                            if (PacMan::pacman_dir != UP && !isPaused()) {
                                // _window._mutex_w.p();
                                // _pacman->_mutex.p();
                                _pacman->changeDirection(UP);
                            }
                        } else if (event.key.code == 15) {
                            _isPaused = !isPaused();
                            if (isPaused()) {

                                // if (Traits<Timer>::preemptive) {
                                    // paused_thread = new Thread(runPaused);
                                    // Thread::yield();
                                // }
                                // _semaphore_pause.p();
                            } else {
                                // if (!Traits<Timer>::preemptive)
                                    _semaphore_pause.wakeup_all();
                                // else {
                                    // delete paused_thread;
                                // }
                                if (_lives <= 0 || _foods <= 0) {
                                   restartGame();
                               }
                            }
                            // Thread::yield();
                        } else if (event.key.code == 16) {
                            finishGame();
                        } else if (event.key.code == 17) {
                            restartGame();
                        }
                        break;

                }
            }
            // if (Traits<Timer>::preemptive)
            // _window._mutex_w.v();
            for (volatile int i = 0; i < DELAY + ((_isPaused || _isStarting) * 5 * DELAY); i++);
            Thread::yield();
        }
    }

    static void runWindow() {
        sf::RenderWindow window(sf::VideoMode(674, 860), "Pac Man");
        _window_render = &window;

        //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
        window.setKeyRepeatEnabled(false);

        int i = 0;
        bool done = false;

        Thread input_thread = Thread(runInput);

        while (window.isOpen())
        {
            // _window._mutex_w.p();
            if (isPaused()) {
                if (!done) {
                    if (_lives > 0) {
                        _window.pause_sprite.setPosition(288,405);
                        window.draw(_window.pause_sprite);
                    } else {
                        _window.gameover_sprite.setPosition(212,405);
                        window.draw(_window.gameover_sprite);
                    }
                    // drawLives();
                    window.display();
                    // _window._mutex_w.v();
                    done = true;
                    // if (Traits<Timer>::preemptive)
                    //     int status = paused_thread->join();
                    // else
                    for (volatile int k = 0; k < DELAY * 10; k++);
                    _semaphore_pause.p();
                    for (volatile int k = 0; k < DELAY * 4; k++);
                }
            }

            i++;
            done = false;

            window.clear();

            if (isStarting()) {
                _window.ready_sprite.setPosition(265, 407);
                window.draw(_window.ready_sprite);
                i--;
            }

            for (int k = 0; k < 28; k++) {
                for (int j = 0; j < 31; j++) {
                    switch(Personagem::getTile(k, j)) {
                        case tiles::o:
                            // draw small food
                            _window.pill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
                            window.draw(_window.pill_sprite);
                            break;
                        case tiles::O:
                            // draw large food
                            if (i % 60 > 30) {
                                _window.bigPill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
                                window.draw(_window.bigPill_sprite);
                            }
                            break;
                    }
                }
            }

            // Draw Fruits
            if(Personagem::getTile(13, 13) == tiles::F) {
                if (_foods > 70) {
                    _window.cherry_sprite.setPosition(315, 398);
                    window.draw(_window.cherry_sprite);
                } else {
                    _window.strawberry_sprite.setPosition(315, 398);
                    window.draw(_window.strawberry_sprite);
                }
            } else if (Personagem::getTile(13, 13) == tiles::f) {
                if (i % 60 > 30){
                    _window.score_100_sprite.setPosition(315, 415);
                    window.draw(_window.score_100_sprite);
                }
            }

            if (_foods > 70) {
                _window.strawberry_sprite.setPosition(627, 795);
                window.draw(_window.strawberry_sprite);
                if (_foods > 170) {
                    _window.cherry_sprite.setPosition(582, 795);
                    window.draw(_window.cherry_sprite);
                }

            }

            // Draw Lives
            drawLives();

            window.draw(_window.maze_sprite);

            //Draw Score
            _window.score_sprite.setPosition(5,760);
            window.draw(_window.score_sprite);

            _window.high_sprite.setPosition(5,795);
            window.draw(_window.high_sprite);

            int _score_held = _score;
            for (int aa = 0; aa < 8; aa++){
                int digito = _score_held % 10;
                _score_held /= 10;
                _window.num_sprite[aa].setTexture(_window.num_tex[digito]);
                _window.num_sprite[aa].setPosition((140+ 7*24 - aa*24 ),760);
                window.draw(_window.num_sprite[aa]);
            }
            _score_held = (_highscore > _score) ? _highscore : _score;
            for (int bb = 0; bb < 8; bb++){
                int digito = _score_held % 10;
                _score_held /= 10;
                _window.num_sprite[bb].setTexture(_window.num_tex[digito]);
                _window.num_sprite[bb].setPosition((140+ 7*24 - bb*24 ),795);
                window.draw(_window.num_sprite[bb]);
            }

            // Draw PacMan
            _pacman->_mutex.p();
            _window._pacman_sprites[(i / 15) % 4].setPosition(PacMan::pacman_x, PacMan::pacman_y);
            _pacman->_mutex.v();
            window.draw(_window._pacman_sprites[(i / 15) % 4]);

            // Draw Ghost 1
            if (!_ghost1->isScared()) {
                _window._ghost_sprites[(i / 15) % 2].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                window.draw(_window._ghost_sprites[(i / 15) % 2]);
                _window._ghost_sprites[2 + Ghost1::ghost1_dir - (Ghost1::ghost1_dir == STOPPED)].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                window.draw(_window._ghost_sprites[2 + Ghost1::ghost1_dir - (Ghost1::ghost1_dir == STOPPED)]);
            } else {
                _window._scared_sprites[(i / 15) % 4].setPosition(Ghost1::ghost1_x, Ghost1::ghost1_y);
                window.draw(_window._scared_sprites[(i / 15) % 4]);
            }

            // Draw Ghost 2
            if (!_ghost2->isScared()) {
                _window._ghost_sprites2[(i / 15) % 2].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                window.draw(_window._ghost_sprites2[(i / 15) % 2]);
                _window._ghost_sprites2[2 + Ghost2::ghost2_dir - (Ghost2::ghost2_dir == STOPPED)].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                window.draw(_window._ghost_sprites2[2 + Ghost2::ghost2_dir - (Ghost2::ghost2_dir == STOPPED)]);
            } else {
                _window._scared_sprites[(i / 15) % 4].setPosition(Ghost2::ghost2_x, Ghost2::ghost2_y);
                window.draw(_window._scared_sprites[(i / 15) % 4]);
            }

            // Draw Ghost 3
            if (!_ghost3->isScared()) {
                _window._ghost_sprites3[(i / 15) % 2].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                window.draw(_window._ghost_sprites3[(i / 15) % 2]);
                _window._ghost_sprites3[2 + Ghost3::ghost3_dir - (Ghost3::ghost3_dir == STOPPED)].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                window.draw(_window._ghost_sprites3[2 + Ghost3::ghost3_dir - (Ghost3::ghost3_dir == STOPPED)]);
            } else {
                _window._scared_sprites[(i / 15) % 4].setPosition(Ghost3::ghost3_x, Ghost3::ghost3_y);
                window.draw(_window._scared_sprites[(i / 15) % 4]);
            }

            // Draw Ghost 4
            if (!_ghost4->isScared()) {
                _window._ghost_sprites4[(i / 15) % 2].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                window.draw(_window._ghost_sprites4[(i / 15) % 2]);
                _window._ghost_sprites4[2 + Ghost4::ghost4_dir - (Ghost4::ghost4_dir == STOPPED)].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                window.draw(_window._ghost_sprites4[2 + Ghost4::ghost4_dir - (Ghost4::ghost4_dir == STOPPED)]);
            } else {
                _window._scared_sprites[(i / 15) % 4].setPosition(Ghost4::ghost4_x, Ghost4::ghost4_y);
                window.draw(_window._scared_sprites[(i / 15) % 4]);
            }

            window.display();
            // _window._mutex_w.v();
            for (volatile unsigned int j = 0; j < DELAY; j++);

            if (i == 55440) i = 0;

            Thread::yield();
        }
    }
};



#endif
