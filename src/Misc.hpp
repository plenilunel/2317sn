#pragma once

struct Misc{
public:
    static int WIN_HEIGHT;
    static int WIN_WIDTH;
    static int DIMENSION;

    const static int SNAKE_START_XPOS = 10;
    const static int SNAKE_START_YPOS = 10;

    const static int GROWTH_SPAWN_DELAY = 40;
    const static int GROWTH_MAX_COUNT = 3;
    const static int GROWTH_LIFE_TIME = 50;

    const static int POISON_SPAWN_DELAY = 20;
    const static int POISON_MAX_COUNT = 4;
    const static int POISON_LIFE_TIME = 30;
};
int Misc::WIN_WIDTH = 0;
int Misc::WIN_HEIGHT = 0;
int Misc::DIMENSION = 0;

enum BlockType{
    Empty , Wall , Conner , GateIn , GateOut, Poison, Growth, SnakeHead, SnakeBody, Error
};

enum MoveDir{
    Left, Right, Up, Down
};

