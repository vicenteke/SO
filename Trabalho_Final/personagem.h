#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>

class Personagem {
public:
    enum Direction {UP, DOWN, LEFT, RIGHT, STOPPED};

    Personagem(int x, int y) : _x(x), _y(y) {}

    ~Personagem(){}

    // void updateMatrix(char c); // Usa mutex

    int getX() {
        return _x;
    }

    int getY() {
        return _y;
    }

    void setX(int x) {
        _x = x;
    }

    void setY(int y) {
        _y = y;
    }

protected:
    int _x;
    int _y;
};
