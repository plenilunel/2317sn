#pragma once

class Snake{
private:
    struct Body{
        explicit Body(int x = -1, int y = -1) : x(x), y(y), next(nullptr) {}
        int x;
        int y;
        Body *next;
    };
public:
    Body *head;
    int snake_size;

    //TODO : insert, refresh to map function
    void awake();
    // move snake to dir_x,y position
    void move(int dir_x, int dest_y);
    void insert();

};

void Snake::move(int dir_x, int dir_y) {

    int origX = head->x;
    int origY = head->y;

    Body *p = head;
    Body *q = nullptr;

    while(p->next)
    {
        q = p;
        p = p->next;
        p->x = q->x;
        p->y = q->y;
    }

    if(q)
    {
        p->x = q->x;
        p->y = q->y;
    }

    head->x = origX + dir_x;
    head->y = origY + dir_y;
}

void Snake::insert() {
    if(head == nullptr)
    {
        //throw exception
    }

    Body *p = head;

    while (p->next)
        p = p->next;


}

void Snake::awake() {

    head = new Body(Misc::SNAKE_START_XPOS,
                    Misc::SNAKE_START_YPOS);
    snake_size = 1;
}

