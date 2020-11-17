/* IDEIAS

matriz de posições compartilhada (como?) -> mutex
quando move, verifica posição


*/

class Main {
public:
    Main() {

    }

    ~Main() {}

    static int run();
};

int Main::run() {

    bool win = false;

    Jogo jogo = Jogo();

    return win;
}


// Jogo e Tela são uma só
class Jogo {
public:
    Jogo(int lifes = 3, int foods = 240, int score = 0) : _lifes(lifes),
    _foods(foods), _score(score) {

    }

    ~Jogo() {

    }

    void addScore (int i) {
        _score += i;
    }

    void decreaseLife() {
        _lives--;
    }

    void decreaseFood() {
        _food--;
    }

    static char matriz[][];
    static Semaphore mutex;

private:
    int _lifes;
    int _foods;
    int _score;


};


class Tela {
public:

    Tela() {
        // Cria maze

        // Cria objetos dos personagens
        // Inicia as Threads
        // Join nas Threads
    }

    void updateScreen() {
        // int x_pm = pacman.getX();
        // if (x % resolution == 0) updateMatrix();

        // Pega posições dos personagens
        // Atualiza matriz se necessário
        // Atualiza tela (animação)
        // Verifica colisões
    }

private:
    PacMan pacman;
    Ghost ghosts[4];

}


class Personagem {
private:
    enum Direction {UP, DOWN, LEFT, RIGHT};

public:
    Personagem(int x, int y, char* & sprite){}

    ~Personagem(){}

    void move(Direction d) {
        switch (d) {
            case UP: _y++;
                    break;
            case DOWN: _y--;
                        break;
            case LEFT: _x--;
                        break;
            case RIGHT: _x++;
                        break;
        }

        if (x < 0) x = 0;
        else if (x > limite) x = limite; // same for y

        // if (pos % resolution) updateMatrix();
    }

    // void updateMatrix(); // Usa mutex

    int getX() {
        return _x;
    }

    int getY() {
        return _y;
    }

private:
    int _x;
    int _y;
    char* _sprite;

};


class PacMan : public Personagem {
public:
    static void run() {
        // do stuff
    }
};


class Ghost : public Personagem {
public:
    static void run() {
        // do stuff
    }
};


class Ghost1 : public Ghost {

}


class Pause {
public:
    Pause() {
        char last = ' ';
        while (getChar == ' ');
        if
    }
}
