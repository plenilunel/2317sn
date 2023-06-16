//
// Created by Administrator on 6/16/2023.
//

#pragma once

#include <cstdlib>
#include <ctime>

class Spawner{
private:
    int range_x;
    int range_y;

    int pos1;
    int pos2;

    int growth_cnt;
    int growth_spawn_timer;

    int poison_cnt;
    int poison_spawn_timer;

    void spawnItem();
    void spawnGate();
public:
    void awake(int, int);
    void spawn(Board& board, Snake& snake);
};

void Spawner::awake(int dimX, int dimY) {
    srand(time(NULL));

    range_x = dimX - 1;
    range_y = dimY - 1;
    growth_cnt = poison_cnt = growth_spawn_timer = poison_spawn_timer = 0;
}

void Spawner::spawn() {


}
