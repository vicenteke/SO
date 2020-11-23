#include "jogo.h"

Window Jogo::_window;
PacMan Jogo::_pacman;
Ghost Jogo::_ghost;
int Jogo::_lives = 3;
int Jogo::_foods = 240;
int Jogo::_score = 0;

int main(void)
{
    Jogo jogo = Jogo();

    System::init(Jogo::run);

    return 0;
}
