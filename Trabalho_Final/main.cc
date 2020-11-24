#include "jogo.h"

Window Jogo::_window;
PacMan Jogo::_pacman;
Ghost1 Jogo::_ghost1;
Ghost2 Jogo::_ghost2;
Ghost3 Jogo::_ghost3;
Ghost4 Jogo::_ghost4;
int Jogo::_lives = 3;
int Jogo::_foods = 240;
int Jogo::_score = 0;

int main(void)
{
    Jogo jogo = Jogo();

    System::init(Jogo::run);

    return 0;
}
