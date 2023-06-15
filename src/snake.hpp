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

    switch (moveDir) {
        case Up:
            head->y -= 1;
            break;
        case Down:
            head->y += 1;
            break;
        case Right:
            head->x += 1;
            break;
        case Left:
            head->x -= 1;
            break;
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
    tail->next = tmp;
    tail = tmp;
    snake_size++;
}

void Snake::awake() {
    //처음 진행방향 ->오른쪽(KEY_RIGHT)
    head = new Body(Misc::SNAKE_START_XPOS,
                    Misc::SNAKE_START_YPOS);
    tail = head;

    insert();
    insert();

    snake_size = 3;
}

bool Snake::isAlive()
{
    return false;
}