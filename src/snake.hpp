#pragma once

class Snake{
private:
    struct Body{
        explicit Body(int x = -1, int y = -1) : x(x), y(y), next(nullptr) , prev(nullptr){}
        int x;
        int y;
        Body *next;
        Body *prev;
    };
public:
    Body *head;
    Body *tail;
    int snake_size;
    MoveDir m_dir{Right};
    //TODO : insert, refresh to map function
    void awake();
    // move snake to dir_x,y position
    void move(MoveDir moveDir);
    bool isAlive();
    void insert();

};

void Snake::move(MoveDir moveDir) {
    m_dir = moveDir;
    Body *p = head;
    int dx = 0;
    int dy = 0;
    switch (moveDir) {
        case Up:
            dy = -1;
            break;
        case Down:
            dy = 1;
            break;
        case Right:
            dx = 1;
            break;
        case Left:
            dx = -1;
            break;
    }
    while(p)
    {
        p->x += dx;
        p->y += dy;
        p = p->next;
    }
}

void Snake::insert() {
    if (head == nullptr || tail == nullptr) {
        //throw exception
    }

    Body *tmp = new Body(tail->x, tail->y);
    switch (m_dir) {
        case Up:
            tmp->y += 1;
            break;
        case Down:
            tmp->y -= 1;
            break;
        case Right:
            tmp->x -= 1;
            break;
        case Left:
            tmp->x += 1;
            break;
    }
    tmp->prev = tail;
    tail->next = tmp;
    tail = tmp;
    snake_size++;
}

void Snake::awake() {
    //처음 진행방향 ->오른쪽(KEY_RIGHT)
    head = new Body(Misc::SNAKE_START_XPOS,
                    Misc::SNAKE_START_YPOS);
    tail = head;
    for(int i = 1; i < 5; i++)
    {
        Body *t = new Body(tail->x-2, tail->y);
        tail->next = t;
        tail = t;
    }

    snake_size = 3;
}

bool Snake::isAlive()
{
    return false;
}