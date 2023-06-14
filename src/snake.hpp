#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include <vector>

using namespace std;

class Snake{
private:
    struct Body{
        int x;
        int y;
        Body *next;
    };
public:
    //TODO : insert, refresh to map function
    //Body snake[];
    //or
    //Bode *head; // linked list expression
    Body *head;
    int snake_size;
};

#endif //SNAKE_SNAKE_HPP
