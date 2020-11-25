#include "window.h"

__USING_API

Window::Window()
{
    load_and_bind_textures();
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::run()
{
    // sf::RenderWindow window(sf::VideoMode(674, 1000), "Pac Man");
    //
    // //Link: https://www.sfml-dev.org/tutorials/2.5/window-events.php
    // //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php
    // window.setKeyRepeatEnabled(false);
    //
    // int i = 0;
    //
    // while (window.isOpen())
    // {
    //     i++;
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         switch (event.type) {
    //         case sf::Event::Closed:
    //              window.close();
    //              break;
    //
    //         // key pressed
    //         case sf::Event::KeyPressed:
    //             if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    //                 // std::cout << "Keyboard esquerda!" << std::endl;
    //                 // _pacman.changeDirection(Personagem::Direction::LEFT);
    //                 PacMan::pacman_dir = LEFT;
    //             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    //                 // std::cout << "Keyboard direita!" << std::endl;
    //                 // _pacman.changeDirection(Personagem::Direction::RIGHT);
    //                 PacMan::pacman_dir = RIGHT;
    //             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    //                 // std::cout << "Keyboard para baixo!" << std::endl;
    //                 // _pacman.changeDirection(Personagem::Direction::DOWN);
    //                 PacMan::pacman_dir = DOWN;
    //             } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    //                 // std::cout << "Keyboard para cima!" << std::endl;
    //                 // _pacman.changeDirection(Personagem::Direction::UP);
    //                 PacMan::pacman_dir = UP;
    //             } else if (event.key.code == 57) {
    //                 // std::cout << _ghost.direction() << ' ' << _ghost.getTileX() << ", " << _ghost.getTileY() << '\n';
    //             } else if (event.key.code == 42) {
    //                 // std::cout << _pacman.getTileX() << ", " << _pacman.getTileY() << '\n';
    //             } else
    //                 std::cout << "Keyboard pressed = " << event.key.code << std::endl;
    //             break;
    //
    //         }
    //     }
    //
    //     window.clear();
    //
    //     for (int k = 0; k < 28; k++) {
    //         for (int j = 0; j < 31; j++) {
    //             switch(maze[k][j]) {
    //                 case tile::o:
    //                     // draw small food
    //                     pill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
    //                     window.draw(pill_sprite);
    //                     break;
    //                 case tile::O:
    //                     // draw large food
    //                     bigPill_sprite.setPosition(24 * k + 3, 725 - 24 * j);
    //                     window.draw(bigPill_sprite);
    //                     break;
    //             }
    //         }
    //     }
    //
    //     window.draw(maze_sprite);
    //     // pac_0_sprite.setPosition(310, 398);
    //     // window.draw(pac_0_sprite);
    //     _pacman_sprites[(i / 15) % 4].setPosition(PacMan::pacman_x, PacMan::pacman_y);
    //     window.draw(_pacman_sprites[(i / 15) % 4]);
    //
    //     // ghost_r_0_sprite.setPosition(315, 350);
    //     // window.draw(ghost_r_0_sprite);
    //     _ghost_sprites[(i / 15) % 2].setPosition(Ghost::ghost_x, Ghost::ghost_y);
    //     _ghost_sprites[2 + Ghost::ghost_dir].setPosition(Ghost::ghost_x, Ghost::ghost_y);
    //     window.draw(_ghost_sprites[(i / 15) % 2]);
    //     window.draw(_ghost_sprites[2 + Ghost::ghost_dir]);
    //
    //     window.display();
    //     window.display();
    //     std::cout << '1';
    //     for (volatile unsigned int j = 0; j < 25000000; j++);
    //
    //     if (i == 55440) i = 0;
    //     Thread::yield();
    // }
}

void Window::load_and_bind_textures()
{
    // Bind map textures
    maze_tex.loadFromFile("sprites/maze/maze.png");
    maze_sprite.setTexture(maze_tex);
    maze_sprite.scale(3, 3);
    pill_tex.loadFromFile("sprites/maze/p-0.png");
    pill_sprite.setTexture(pill_tex);
    pill_sprite.scale(2, 2);
    bigPill_tex.loadFromFile("sprites/maze/p-1.png");
    bigPill_sprite.setTexture(bigPill_tex);
    bigPill_sprite.scale(2, 2);

    // Bind Pacman textures
    pac_0_tex.loadFromFile("sprites/pacman/0.png");
    pac_0_sprite.setTexture(pac_0_tex);
    pac_0_sprite.scale(3, 3);
    pac_1_tex.loadFromFile("sprites/pacman/1.png");
    pac_1_sprite.setTexture(pac_1_tex);
    pac_1_sprite.scale(3, 3);
    pac_2_tex.loadFromFile("sprites/pacman/2.png");
    pac_2_sprite.setTexture(pac_2_tex);
    pac_2_sprite.scale(3, 3);
    dead_0_tex.loadFromFile("sprites/pacman/d-0.png");
    dead_0_sprite.setTexture(dead_0_tex);
    dead_1_tex.loadFromFile("sprites/pacman/d-1.png");
    dead_1_sprite.setTexture(dead_1_tex);
    dead_2_tex.loadFromFile("sprites/pacman/d-2.png");
    dead_2_sprite.setTexture(dead_2_tex);
    dead_3_tex.loadFromFile("sprites/pacman/d-3.png");
    dead_3_sprite.setTexture(dead_3_tex);
    dead_4_tex.loadFromFile("sprites/pacman/d-4.png");
    dead_4_sprite.setTexture(dead_4_tex);
    dead_5_tex.loadFromFile("sprites/pacman/d-5.png");
    dead_5_sprite.setTexture(dead_5_tex);
    dead_6_tex.loadFromFile("sprites/pacman/d-6.png");
    dead_6_sprite.setTexture(dead_6_tex);
    dead_7_tex.loadFromFile("sprites/pacman/d-7.png");
    dead_7_sprite.setTexture(dead_7_tex);
    dead_8_tex.loadFromFile("sprites/pacman/d-8.png");
    dead_8_sprite.setTexture(dead_8_tex);
    dead_9_tex.loadFromFile("sprites/pacman/d-9.png");
    dead_9_sprite.setTexture(dead_9_tex);
    dead_10_tex.loadFromFile("sprites/pacman/d-10.png");
    dead_10_sprite.setTexture(dead_10_tex);

    // Bind ghost textures
    ghost_r_0_tex.loadFromFile("sprites/ghosts/r-0.png");
    ghost_r_0_sprite.setTexture(ghost_r_0_tex);
    ghost_r_0_sprite.scale(3, 3);
    ghost_r_1_tex.loadFromFile("sprites/ghosts/r-1.png");
    ghost_r_1_sprite.setTexture(ghost_r_1_tex);
    ghost_r_1_sprite.scale(3, 3);
    ghost_p_0_tex.loadFromFile("sprites/ghosts/p-0.png");
    ghost_p_0_sprite.setTexture(ghost_p_0_tex);
    ghost_p_0_sprite.scale(3, 3);
    ghost_p_1_tex.loadFromFile("sprites/ghosts/p-1.png");
    ghost_p_1_sprite.setTexture(ghost_p_1_tex);
    ghost_p_1_sprite.scale(3, 3);
    ghost_b_0_tex.loadFromFile("sprites/ghosts/b-0.png");
    ghost_b_0_sprite.setTexture(ghost_b_0_tex);
    ghost_b_0_sprite.scale(3, 3);
    ghost_b_1_tex.loadFromFile("sprites/ghosts/b-1.png");
    ghost_b_1_sprite.setTexture(ghost_b_1_tex);
    ghost_b_1_sprite.scale(3, 3);
    ghost_y_0_tex.loadFromFile("sprites/ghosts/y-0.png");
    ghost_y_0_sprite.setTexture(ghost_y_0_tex);
    ghost_y_0_sprite.scale(3, 3);
    ghost_y_1_tex.loadFromFile("sprites/ghosts/y-1.png");
    ghost_y_1_sprite.setTexture(ghost_y_1_tex);
    ghost_y_1_sprite.scale(3, 3);
    ghost_scared_0_tex.loadFromFile("sprites/ghosts/s-0.png");
    ghost_scared_0_sprite.setTexture(ghost_scared_0_tex);
    ghost_scared_0_sprite.scale(3, 3);
    ghost_scared_1_tex.loadFromFile("sprites/ghosts/s-1.png");
    ghost_scared_1_sprite.setTexture(ghost_scared_1_tex);
    ghost_scared_1_sprite.scale(3, 3);
    ghost_scared_2_tex.loadFromFile("sprites/ghosts/s-2.png");
    ghost_scared_2_sprite.setTexture(ghost_scared_2_tex);
    ghost_scared_2_sprite.scale(3, 3);
    ghost_scared_3_tex.loadFromFile("sprites/ghosts/s-3.png");
    ghost_scared_3_sprite.setTexture(ghost_scared_3_tex);
    ghost_scared_3_sprite.scale(3, 3);

     // Bind ghost eye textures
    eye_up_tex.loadFromFile("sprites/eyes/up.png");
    eye_up_sprite.setTexture(eye_up_tex);
    eye_up_sprite.scale(3, 3);
    eye_right_tex.loadFromFile("sprites/eyes/right.png");
    eye_right_sprite.setTexture(eye_right_tex);
    eye_right_sprite.scale(3, 3);
    eye_down_tex.loadFromFile("sprites/eyes/down.png");
    eye_down_sprite.setTexture(eye_down_tex);
    eye_down_sprite.scale(3, 3);
    eye_left_tex.loadFromFile("sprites/eyes/left.png");
    eye_left_sprite.setTexture(eye_left_tex);
    eye_left_sprite.scale(3, 3);


    // Bind UI textures
    num_0_tex.loadFromFile("sprites/ui/0.png");
    num_0_sprite.setTexture(num_0_tex);
    num_1_tex.loadFromFile("sprites/ui/1.png");
    num_1_sprite.setTexture(num_1_tex);
    num_2_tex.loadFromFile("sprites/ui/2.png");
    num_2_sprite.setTexture(num_2_tex);
    num_3_tex.loadFromFile("sprites/ui/3.png");
    num_3_sprite.setTexture(num_3_tex);
    num_4_tex.loadFromFile("sprites/ui/4.png");
    num_4_sprite.setTexture(num_4_tex);
    num_5_tex.loadFromFile("sprites/ui/5.png");
    num_5_sprite.setTexture(num_5_tex);
    num_6_tex.loadFromFile("sprites/ui/6.png");
    num_6_sprite.setTexture(num_6_tex);
    num_7_tex.loadFromFile("sprites/ui/7.png");
    num_7_sprite.setTexture(num_7_tex);
    num_8_tex.loadFromFile("sprites/ui/8.png");
    num_8_sprite.setTexture(num_8_tex);
    num_9_tex.loadFromFile("sprites/ui/9.png");
    num_9_sprite.setTexture(num_9_tex);
    score_200_tex.loadFromFile("sprites/ui/200.png");
    score_200_sprite.setTexture(score_200_tex);
    score_400_tex.loadFromFile("sprites/ui/400.png");
    score_400_sprite.setTexture(score_400_tex);
    score_800_tex.loadFromFile("sprites/ui/800.png");
    score_800_sprite.setTexture(score_800_tex);
    score_1600_tex.loadFromFile("sprites/ui/1600.png");
    score_1600_sprite.setTexture(score_1600_tex);
    ready_tex.loadFromFile("sprites/ui/ready.png");
    ready_sprite.setTexture(ready_tex);
    gameover_tex.loadFromFile("sprites/ui/gameover.png");
    gameover_sprite.setTexture(gameover_tex);
    life_tex.loadFromFile("sprites/ui/life.png");
    life_sprite.setTexture(life_tex);
    score_tex.loadFromFile("sprites/ui/score_tex.png");
    score_sprite.setTexture(score_tex);
    high_tex.loadFromFile("sprites/ui/high.png");
    high_sprite.setTexture(high_tex);
    score_100_tex.loadFromFile("sprites/ui/100.png");
    score_100_sprite.setTexture(score_100_tex);
    score_300_tex.loadFromFile("sprites/ui/300.png");
    score_300_sprite.setTexture(score_300_tex);

    // Fruit textures
    cherry_tex.loadFromFile("sprites/fruits/cherry.png");
    cherry_sprite.setTexture(cherry_tex);
    strawberry_tex.loadFromFile("sprites/fruits/strawberry.png");
    strawberry_sprite.setTexture(strawberry_tex);

    //Set theme song
    theme_msc.openFromFile("sprites/theme.ogg");
    theme_msc.setVolume(0);
    theme_msc.play();

    // Sprites arrays for objects
    _pacman_sprites[0] = pac_0_sprite;
    _pacman_sprites[1] = pac_1_sprite;
    _pacman_sprites[2] = pac_2_sprite;
    _pacman_sprites[3] = pac_1_sprite;

    _ghost_sprites[0] = ghost_r_0_sprite;
    _ghost_sprites[1] = ghost_r_1_sprite;
    _ghost_sprites[2] = eye_up_sprite;
    _ghost_sprites[3] = eye_down_sprite;
    _ghost_sprites[4] = eye_left_sprite;
    _ghost_sprites[5] = eye_right_sprite;

    _ghost_sprites2[0] = ghost_b_0_sprite;
    _ghost_sprites2[1] = ghost_b_1_sprite;
    _ghost_sprites2[2] = eye_up_sprite;
    _ghost_sprites2[3] = eye_down_sprite;
    _ghost_sprites2[4] = eye_left_sprite;
    _ghost_sprites2[5] = eye_right_sprite;

    _ghost_sprites3[0] = ghost_p_0_sprite;
    _ghost_sprites3[1] = ghost_p_1_sprite;
    _ghost_sprites3[2] = eye_up_sprite;
    _ghost_sprites3[3] = eye_down_sprite;
    _ghost_sprites3[4] = eye_left_sprite;
    _ghost_sprites3[5] = eye_right_sprite;

    _ghost_sprites4[0] = ghost_y_0_sprite;
    _ghost_sprites4[1] = ghost_y_1_sprite;
    _ghost_sprites4[2] = eye_up_sprite;
    _ghost_sprites4[3] = eye_down_sprite;
    _ghost_sprites4[4] = eye_left_sprite;
    _ghost_sprites4[5] = eye_right_sprite;

    _scared_sprites[0] = ghost_scared_0_sprite;
    _scared_sprites[1] = ghost_scared_1_sprite;
    _scared_sprites[2] = ghost_scared_2_sprite;
    _scared_sprites[3] = ghost_scared_3_sprite;
}
