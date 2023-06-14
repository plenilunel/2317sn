#pragma once

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

void Snake::move(int dest_x, int dest_y) {

    int origX = head->x;
    int origY = head->y;

    Body *p = head;
    Body *q;

    while(p->next)
    {
        q = p;

        p = p->next;
    }
}

void Snake::insert() {

}

void Snake::awake() {

}

