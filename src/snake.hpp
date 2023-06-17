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
    MoveDir m_dir{Right};
    int snake_size;
    //TODO : insert, refresh to map function
    void awake();
    // move snake to dir_x,y position
    void move(MoveDir moveDir);
    void move(int destX, int destY) const;

    bool isAlive() const;
    [[nodiscard]] bool isInSnake(const int& x, const int& y) const;
    void insert();
    void remove();
};

void Snake::awake() {
    //처음 진행방향 ->오른쪽(KEY_RIGHT)
    head = new Body(Misc::SNAKE_START_XPOS,
                    Misc::SNAKE_START_YPOS);
    tail = head;
    for(int i = 1; i < 5; i++)
    {
        Body *t = new Body(tail->x-1, tail->y);
        t->prev = tail;
        tail->next = t;
        tail = t;
    }

    snake_size = 3;
}

void Snake::move(MoveDir moveDir) {
#ifdef DEBUG
    mvprintw(LINES-1, 0, "Head : <%d,%d>, Tail : <%d,%d>", head->x, head->y, tail->x, tail->y);
#endif

    m_dir = moveDir;
    Body *p = tail;

    while(p->prev)
    {
        p->x = p->prev->x;
        p->y = p->prev->y;
        p = p->prev;
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

void Snake::move(int destX, int destY) const {
    head->x = destX;
    head->y = destY;
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

bool Snake::isAlive() const
{
    if(snake_size < 3)
        return false;

    Body* p = head->next;

    while(p)
    {
        if(p->x == head->x && p->y == head->y)
            return false;
        p = p->next;
    }

    return true;
}

void Snake::remove() {
    Body *p = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete p;
    snake_size--;
}

bool Snake::isInSnake(const int &x, const int &y) const
{
    Body *p = head;
    while(p)
    {
        if(p->x == x && p->y == y)
            return true;
        p = p->next;
    }
    return false;
}
