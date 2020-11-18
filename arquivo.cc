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

void Main::run() {

    Jogo jogo = Jogo();
}

class Jogo {
public:
    Jogo(int lifes = 3, int foods = 240, int score = 0) : _lifes(lifes),
    _foods(foods), _score(score) {

        run();
    }

    ~Jogo() {

    }

    void run() {

        // Cria maze

        // Cria objetos dos personagens
        // Inicia as Threads
        // Join nas Threads?
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

    void updateScreen() {
        // int x_pm = pacman.getX();
        // if (x % resolution == 0) updateMatrix();

        // V1
        // Pega posições dos personagens
        // Atualiza matriz se necessário
        // Atualiza tela (animação)
        // Verifica colisões

        // V2
    }

    static char matriz[][];
    static Semaphore mutex;

private:
    int _lifes;
    int _foods;
    int _score;

    PacMan pacman;
    Ghost ghosts[4];
};


class Personagem {
private:
    enum Direction {UP, DOWN, LEFT, RIGHT};

public:
    Personagem(int x, int y, char* & sprite){}

    ~Personagem(){}

    // void updateMatrix(char c); // Usa mutex

    int getX() {
        return _x;
    }

    int getY() {
        return _y;
    }

private:
    int _x;
    int _y;
    sf::Sprite _sprite;

};


class PacMan : public Personagem {
public:

    PacMan() {}
    ~PacMan() {}

    static void run() {

        while (true) {

        }
        // get Keyboard
        // move()
    }

    void move(Direction d) {
        // V2: Atualiza matriz e checa se há colisões

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

private:
    Direction _last_input;

};


class Ghost : public Personagem {
public:
    static void run() {
        while (true) {
            // define target tile
            // move()
        }
        // do stuff
    }
};


class Ghost1 : public Ghost {

};
