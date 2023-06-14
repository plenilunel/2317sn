#ifndef SNAKE_MISC_HPP
#define SNAKE_MISC_HPP

class Misc{
private:
public:
    static int WIN_HEIGHT;
    static int WIN_WIDTH;
    static int MAP_SIZE;
};
int Misc::WIN_WIDTH = 0;
int Misc::WIN_HEIGHT = 0;
int Misc::MAP_SIZE = 0;

enum BlockType{
    Empty, Wall, Conner, Item, GateIn, GateOut
};
#endif //SNAKE_MISC_HPP
