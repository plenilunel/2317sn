#ifndef SNAKE_SNAKE_HPP
#define SNAKE_SNAKE_HPP

class Snake{
private:
    struct Body{
        int x;
        int y;
        Body *next;
    };
public:
    //TODO : insert, refresh to map function
    Snake();
    Body *head;
    int snake_size;

    // move snake to dest_x,y position
    void move(int dest_x, int dest_y);
    void insert();

};

Snake::Snake()
{
    head = new Body;
    head->next = nullptr;
    head->x = 10;
    head->y = 10;
}

#endif //SNAKE_SNAKE_HPP
