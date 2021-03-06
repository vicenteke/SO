#include "window.h"

__USING_API

Window::Window()
{
    load_and_bind_textures();
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

    num_tex[0].loadFromFile("sprites/ui/0.png");
    num_tex[1].loadFromFile("sprites/ui/1.png");
    num_tex[2].loadFromFile("sprites/ui/2.png");
    num_tex[3].loadFromFile("sprites/ui/3.png");
    num_tex[4].loadFromFile("sprites/ui/4.png");
    num_tex[5].loadFromFile("sprites/ui/5.png");
    num_tex[6].loadFromFile("sprites/ui/6.png");
    num_tex[7].loadFromFile("sprites/ui/7.png");
    num_tex[8].loadFromFile("sprites/ui/8.png");
    num_tex[9].loadFromFile("sprites/ui/9.png");
    num_sprite[0].setTexture(num_tex[0]);
    num_sprite[0].scale(3, 3);
    num_sprite[1].setTexture(num_tex[0]);
    num_sprite[1].scale(3, 3);
    num_sprite[2].setTexture(num_tex[0]);
    num_sprite[2].scale(3, 3);
    num_sprite[3].setTexture(num_tex[0]);
    num_sprite[3].scale(3, 3);
    num_sprite[4].setTexture(num_tex[0]);
    num_sprite[4].scale(3, 3);
    num_sprite[5].setTexture(num_tex[0]);
    num_sprite[5].scale(3, 3);
    num_sprite[6].setTexture(num_tex[0]);
    num_sprite[6].scale(3, 3);
    num_sprite[7].setTexture(num_tex[0]);
    num_sprite[7].scale(3, 3);

    num_high[0].setTexture(num_tex[0]);
    num_high[0].scale(3, 3);
    num_high[1].setTexture(num_tex[0]);
    num_high[1].scale(3, 3);
    num_high[2].setTexture(num_tex[0]);
    num_high[2].scale(3, 3);
    num_high[3].setTexture(num_tex[0]);
    num_high[3].scale(3, 3);
    num_high[4].setTexture(num_tex[0]);
    num_high[4].scale(3, 3);
    num_high[5].setTexture(num_tex[0]);
    num_high[5].scale(3, 3);
    num_high[6].setTexture(num_tex[0]);
    num_high[6].scale(3, 3);
    num_high[7].setTexture(num_tex[0]);
    num_high[7].scale(3, 3);

    score_200_tex.loadFromFile("sprites/ui/200.png");
    score_200_sprite.setTexture(score_200_tex);
    score_200_sprite.scale(3, 3);
    score_400_tex.loadFromFile("sprites/ui/400.png");
    score_400_sprite.setTexture(score_400_tex);
    score_400_sprite.scale(3, 3);
    score_800_tex.loadFromFile("sprites/ui/800.png");
    score_800_sprite.setTexture(score_800_tex);
    score_800_sprite.scale(3, 3);
    score_1600_tex.loadFromFile("sprites/ui/1600.png");
    score_1600_sprite.setTexture(score_1600_tex);
    score_1600_sprite.scale(3, 3);
    ready_tex.loadFromFile("sprites/ui/ready.png");
    ready_sprite.setTexture(ready_tex);
    ready_sprite.scale(3, 3);
    gameover_tex.loadFromFile("sprites/ui/gameover.png");
    gameover_sprite.setTexture(gameover_tex);
    gameover_sprite.scale(3, 3);
    life_tex.loadFromFile("sprites/ui/life.png");
    life_sprite.setTexture(life_tex);
    life_sprite.scale(3, 3);
    score_tex.loadFromFile("sprites/ui/score_tex.png");
    score_sprite.setTexture(score_tex);
    score_sprite.scale(3, 3);
    high_tex.loadFromFile("sprites/ui/high.png");
    high_sprite.setTexture(high_tex);
    high_sprite.scale(3, 3);
    pause_tex.loadFromFile("sprites/ui/pause.png");
    pause_sprite.setTexture(pause_tex);
    pause_sprite.scale(3, 3);
    score_100_tex.loadFromFile("sprites/ui/100.png");
    score_100_sprite.setTexture(score_100_tex);
    score_300_tex.loadFromFile("sprites/ui/300.png");
    score_300_sprite.setTexture(score_300_tex);
    score_300_sprite.scale(3, 3);

    // Fruit textures
    cherry_tex.loadFromFile("sprites/fruits/cherry.png");
    cherry_sprite.setTexture(cherry_tex);
    cherry_sprite.scale(1.4, 1.4);
    strawberry_tex.loadFromFile("sprites/fruits/strawberry.png");
    strawberry_sprite.setTexture(strawberry_tex);
    strawberry_sprite.scale(1.4, 1.4);

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
