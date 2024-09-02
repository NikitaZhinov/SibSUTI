#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

class Tetris {
private:
    struct Size_t {
        int width, height;
    };

    struct Point_t {
        int x, y;
    };

    struct Color_t {
        int r, g, b;
    };

    enum Brick_n {
        RightStick,
        LeftStick,
        RightStep,
        LeftStep,
        Cube,
        Stick,
        Triangle
    };

    struct PointField {
        int x, y;
        bool i;
        sf::RectangleShape pixel;
    };

    struct Brick_t {
        PointField **matrix;
        Size_t size;
        Point_t pos;
        int rotate_mode;
        Brick_n number;
    };

    enum Scene {
        Overlay,
        Run,
        Lose,
        Pause
    };

    Scene scene = Overlay;
    const Size_t screen_size = { 400, 600 };
    Brick_t current_brick;
    Brick_t next_brick;
    int count_bricks = 7;
    int level = 1;
    sf::Clock timer;
    sf::Clock timer_move;
    sf::Clock game_time;
    bool get_last_time = true;
    int last_time = 0;
    sf::Clock pause_time;
    int last_pause_time = 0;
    int score = 0;
    int record = 0;
    const Size_t size_field = { 10, 20 };
    const Size_t size_pixel = { 13, 13 };
    const Color_t pixel_color = { 132, 161, 143 };
    PointField **field;
    sf::RectangleShape pixel;
    const int speed = 10;
    const int delay = 50;
    const int delay_move = 20;

    sf::RectangleShape brickgame_background;

    sf::CircleShape *brickgame_buttons;
    int brickgame_buttons_count = 4;
    float brickgame_buttons_radius = 30;
    Point_t brickgame_buttons_pos = { 120, 425 };
    float brickgame_buttons_distance = 70;
    Color_t brickgame_buttons_color = { 0, 0, 255 };

    sf::RectangleShape brickgame_screen;
    Color_t brickgame_screen_color = { 165, 199, 179 };
    Size_t brickgame_screen_size = { 260, 260 };
    Point_t brickgame_screen_pos = { 70, 50 };

    sf::Font font;
    sf::Text next_text;
    sf::Text score_text;
    sf::Text level_text;
    sf::Text record_text;
    sf::Text time_text;
    sf::Text start_text;
    sf::Text lose_text;
    sf::Text pause_text;
    Point_t text_pos = { brickgame_screen_pos.x + brickgame_screen_size.width / 2, brickgame_screen_pos.y };

    sf::RectangleShape line;

    void initGame();
    void draw(sf::RenderWindow &window);
    void logic();
    void getAction();
    void viewStates(sf::RenderWindow &window);

    void drawField(sf::RenderWindow &window);
    void drawBrick(sf::RenderWindow &window, const Brick_t &brick);
    void initBrickGame();
    void initBrickGameBackground();
    void initBrickGameButtons();
    void initBrickGameScreen();
    void initField();
    void initBrick(Brick_t &brick);
    void initRightStick(Brick_t &brick);
    void initLeftStick(Brick_t &brick);
    void initRightStep(Brick_t &brick);
    void initLeftStep(Brick_t &brick);
    void initCube(Brick_t &brick);
    void initStick(Brick_t &brick);
    void initTriangle(Brick_t &brick);
    void setPixelPos(Point_t pos);
    void setPixelColor(Color_t color);
    void setPixel(Point_t pos, Color_t color);
    void removeBrick(Brick_t &brick);
    void updateField();
    int updateBrick();
    void rotateBrick();
    void moveLeftBrick();
    void moveRightBrick();
    void toDownBrick();
    void updatePixelBrick(Brick_t &brick);
    void initText();

public:
    Tetris();
    ~Tetris();

    void run();
};