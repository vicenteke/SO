#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include "tiles.h"
#include "defines.h"
#include "pacman.h"
#include "ghost.h"
#include "thread.h"

__USING_API

class Window
{
public:
    Window();

    static void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

    sf::Sprite * getPacmanSprites() {
        return _pacman_sprites;
    }

    sf::Sprite * getGhostSprites() {
        return _ghost_sprites;
    }

private:
    void load_and_bind_textures();

    // Game characters
    static sf::Sprite _pacman_sprites[4];
    static sf::Sprite _ghost_sprites[6];

    // Fruit fruit: thread that checks _foods?

private:

    // Maze Textures
    sf::Texture maze_tex;
    static sf::Sprite maze_sprite;
    sf::Texture pill_tex;
    static sf::Sprite pill_sprite;
    sf::Texture bigPill_tex;
    static sf::Sprite bigPill_sprite;

    // Pacman Textures
    sf::Texture pac_0_tex;
    static sf::Sprite pac_0_sprite;
    sf::Texture pac_1_tex;
    static sf::Sprite pac_1_sprite;
    sf::Texture pac_2_tex;
    static sf::Sprite pac_2_sprite;
    sf::Texture dead_0_tex;
    static sf::Sprite dead_0_sprite;
    sf::Texture dead_1_tex;
    static sf::Sprite dead_1_sprite;
    sf::Texture dead_2_tex;
    static sf::Sprite dead_2_sprite;
    sf::Texture dead_3_tex;
    static sf::Sprite dead_3_sprite;
    sf::Texture dead_4_tex;
    static sf::Sprite dead_4_sprite;
    sf::Texture dead_5_tex;
    static sf::Sprite dead_5_sprite;
    sf::Texture dead_6_tex;
    static sf::Sprite dead_6_sprite;
    sf::Texture dead_7_tex;
    static sf::Sprite dead_7_sprite;
    sf::Texture dead_8_tex;
    static sf::Sprite dead_8_sprite;
    sf::Texture dead_9_tex;
    static sf::Sprite dead_9_sprite;
    sf::Texture dead_10_tex;
    static sf::Sprite dead_10_sprite;

    // Ghost Textures
    sf::Texture ghost_r_0_tex;
    static sf::Sprite ghost_r_0_sprite;
    sf::Texture ghost_r_1_tex;
    static sf::Sprite ghost_r_1_sprite;
    sf::Texture ghost_p_0_tex;
    static sf::Sprite ghost_p_0_sprite;
    sf::Texture ghost_p_1_tex;
    static sf::Sprite ghost_p_1_sprite;
    sf::Texture ghost_b_0_tex;
    static sf::Sprite ghost_b_0_sprite;
    sf::Texture ghost_b_1_tex;
    static sf::Sprite ghost_b_1_sprite;
    sf::Texture ghost_y_0_tex;
    static sf::Sprite ghost_y_0_sprite;
    sf::Texture ghost_y_1_tex;
    static sf::Sprite ghost_y_1_sprite;
    sf::Texture ghost_scared_0_tex;
    static sf::Sprite ghost_scared_0_sprite;
    sf::Texture ghost_scared_1_tex;
    static sf::Sprite ghost_scared_1_sprite;
    sf::Texture ghost_scared_2_tex;
    static sf::Sprite ghost_scared_2_sprite;
    sf::Texture ghost_scared_3_tex;
    static sf::Sprite ghost_scared_3_sprite;

    // Eye Textures
    sf::Texture eye_up_tex;
    static sf::Sprite eye_up_sprite;
    sf::Texture eye_right_tex;
    static sf::Sprite eye_right_sprite;
    sf::Texture eye_down_tex;
    static sf::Sprite eye_down_sprite;
    sf::Texture eye_left_tex;
    static sf::Sprite eye_left_sprite;

    // UI Textures
    sf::Texture num_0_tex;
    static sf::Sprite num_0_sprite;
    sf::Texture num_1_tex;
    static sf::Sprite num_1_sprite;
    sf::Texture num_2_tex;
    static sf::Sprite num_2_sprite;
    sf::Texture num_3_tex;
    static sf::Sprite num_3_sprite;
    sf::Texture num_4_tex;
    static sf::Sprite num_4_sprite;
    sf::Texture num_5_tex;
    static sf::Sprite num_5_sprite;
    sf::Texture num_6_tex;
    static sf::Sprite num_6_sprite;
    sf::Texture num_7_tex;
    static sf::Sprite num_7_sprite;
    sf::Texture num_8_tex;
    static sf::Sprite num_8_sprite;
    sf::Texture num_9_tex;
    static sf::Sprite num_9_sprite;
    sf::Texture score_200_tex;
    static sf::Sprite score_200_sprite;
    sf::Texture score_400_tex;
    static sf::Sprite score_400_sprite;
    sf::Texture score_800_tex;
    static sf::Sprite score_800_sprite;
    sf::Texture score_1600_tex;
    static sf::Sprite score_1600_sprite;
    sf::Texture ready_tex;
    static sf::Sprite ready_sprite;
    sf::Texture gameover_tex;
    static sf::Sprite gameover_sprite;
    sf::Texture life_tex;
    static sf::Sprite life_sprite;
    sf::Texture score_tex;
    static sf::Sprite score_sprite;
    sf::Texture high_tex;
    static sf::Sprite high_sprite;
    sf::Texture score_100_tex;
    static sf::Sprite score_100_sprite;
    sf::Texture score_300_tex;
    static sf::Sprite score_300_sprite;

    // Fruit Textures
    sf::Texture cherry_tex;
    static sf::Sprite cherry_sprite;
    sf::Texture strawberry_tex;
    static sf::Sprite strawberry_sprite;

    //Sounds
    sf::Music theme_msc;
};



#endif
