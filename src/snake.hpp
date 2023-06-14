
#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

#include "GameManager.hpp"
class Snake{
private:
    struct Body{
        int x;
        int y;
        Body *next;
    };
public:
    Body *head;
    int snake_size;

    //TODO : insert, refresh to map function
    void awake();
    // move snake to dest_x,y position
    void move(int dest_x, int dest_y);
    void insert();

};

void Snake::awake() {
    head = new Body;
    head->next = nullptr;
    head->x = Misc::SNAKE_START_XPOS;
    head->y = Misc::SNAKE_START_YPOS;
    snake_size = 1;
    GameManager& mg;
}

void Snake::move(int dest_x, int dest_y) {
}

void Snake::insert() {

}

#endif //SNAKE_SNAKE_HPP
