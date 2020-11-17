

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

private:
    int _lifes;
    int _foods;
    int _score;

}
