#include "jogo.h"

// Initializing static attributes
Window Jogo::_window;
PacMan * Jogo::_pacman;
Ghost1 * Jogo::_ghost1;
Ghost2 * Jogo::_ghost2;
Ghost3 * Jogo::_ghost3;
Ghost4 * Jogo::_ghost4;

int Jogo::_lives = 3;
int Jogo::_foods = 240;
int Jogo::_score = 0;
int Jogo::_highscore = 0;

bool Jogo::_isStarting;
bool Jogo::_isPaused;

Thread * Jogo::_ghost_threads[5];
Thread * Jogo::timerJail_thread[4];
Thread * Jogo::stopChase_thread;
Thread * Jogo::_score100_thread;

Semaphore Personagem::_mutex_maze;
Semaphore Jogo::_semaphore_pause;
Semaphore Jogo::_mutex_paused;

sf::RenderWindow * Jogo::_window_render;

int main(void)
{
    Jogo jogo = Jogo();

    System::init(Jogo::run);

    return 0;
}
