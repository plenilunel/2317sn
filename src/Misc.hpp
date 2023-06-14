#ifndef SNAKE_MISC_HPP
#define SNAKE_MISC_HPP

struct Misc{
public:
    static int WIN_HEIGHT;
    static int WIN_WIDTH;
    static int MAP_SIZE;
    static int SNAKE_START_XPOS;
    static int SNAKE_START_YPOS;
};
int Misc::WIN_WIDTH = 0;
int Misc::WIN_HEIGHT = 0;
int Misc::MAP_SIZE = 0;
int Misc::SNAKE_START_XPOS = 0;
int Misc::SNAKE_START_YPOS = 0;

enum BlockType{
    Empty, Wall, Conner, Item, GateIn, GateOut
};
enum GameCondition{
    Defeat, Win
};

#endif //SNAKE_MISC_HPP
