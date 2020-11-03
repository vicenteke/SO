

class Jogo {
public:
    Jogo(int points = 0, int lifes = 3, int foods = 240) : _points(points), _lifes(lifes),
    _foods(foods) {

    }

    ~Jogo() {

    }
private:
    int _points;
    int _lifes;
    int _foods;
    
}
