//
// Created by Administrator on 6/17/2023.
//

#ifndef SNAKE_ITEM_HPP
#define SNAKE_ITEM_HPP

struct Item{
    explicit Item(int x = 0, int y = 0, int lifeTime = 0) : x(x), y(y), life(lifeTime) {}

    int x, y, life;
};

struct Gate : public Item{
    int out_x{};
    int out_y{};

    int dest_x{};
    int dest_y{};

    MoveDir out_dir;
    bool fixed{false};
    bool active{false};

    void fixDestination(MoveDir in_dir);
};

void Gate::fixDestination(MoveDir in_dir) {

}


#endif //SNAKE_ITEM_HPP
