#include "jogo.h"

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

bool Jogo::_isPaused;
// Thread * Jogo::paused_thread;
Thread * Jogo::stopChase_thread;
Semaphore Jogo::_semaphore_pause;
Semaphore Jogo::_mutex_paused;
Thread * Jogo::timerJail_thread[4];
Thread * Jogo::_ghost_threads[5];
bool Jogo::_isStarting;

Semaphore Personagem::_mutex_maze;

sf::RenderWindow * Jogo::_window_render;

int main(void)
{
    Jogo jogo = Jogo();

    System::init(Jogo::run);

    return 0;
}
