#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <vector>

using namespace std;

class Snake{
private:
    struct Body{
        int dir_x;
        int dir_y;
        int x;
        int y;
    };
public:
    //TODO : insert, refresh to map function
    Body snake[];

};

#endif //SNAKE_SNAKE_HPP
