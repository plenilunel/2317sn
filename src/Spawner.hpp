//
// Created by Administrator on 6/16/2023.
//

#pragma once

#include <cstdlib>
#include <ctime>

class Spawner{
private:

struct Item{
    explicit Item(int x, int y, int lifeTime) : x(x), y(y), life(lifeTime) {}

    int x, y, life;
};

struct Gate : Item{

    int out_x;
    int out_y;
    MoveDir in_dir;
    MoveDir out_dir;
    bool fixed;
};

    int range_x;
    int range_y;

    int growth_cnt;
    int growth_spawn_timer;
    deque<Item> growth_items;

    int poison_cnt;
    int poison_spawn_timer;
    deque<Item> poison_items;

    bool canGateSpawn;
    Gate gate;

public:
    void awake(int, int);
    void getRandomPosition(int& x, int& y) const;

    void update();

    void spawnGrowthItem(int x, int y);
    bool getRottenGrowth(int& rotten_x, int& rotten_y);

    void spawnPoisonItem(int x, int y);
    bool getRottenPoison(int& rotten_x, int& rotten_y);

    void spawnGate(int in_x, int in_y, int outX, int outY);

    [[nodiscard]] bool canSpawn(BlockType block) const;
};

void Spawner::awake(int height, int width) {
    srand(time(NULL));

    range_x = width;
    range_y = height;

    growth_cnt = growth_spawn_timer = 0;
    poison_cnt = poison_spawn_timer = 0;
    canGateSpawn = true;
}

void Spawner::getRandomPosition(int &x, int &y) const
{
    x = rand() % range_x;
    y = rand() % range_y;
}

void Spawner::update() {

    growth_spawn_timer--;
    poison_spawn_timer--;

    if(!growth_items.empty())
    {
        for(auto & item : growth_items)
            item.life--;
    }
    if(!poison_items.empty())
    {
        for(auto & item : poison_items)
            item.life--;
    }
    if(gate.life > 0)
    {
        gate.life--;
    }
}

void Spawner::spawnGrowthItem(int x, int y)
{
    growth_spawn_timer = Misc::GROWTH_SPAWN_DELAY;
    growth_items.push_back(Item(x, y, Misc::GROWTH_LIFE_TIME));
    growth_cnt++;
}

void Spawner::spawnPoisonItem(int x, int y)
{
    poison_spawn_timer = Misc::POISON_SPAWN_DELAY;
    poison_items.push_back(Item(x, y, Misc::POISON_LIFE_TIME));
    poison_cnt++;
}

bool Spawner::canSpawn(BlockType block) const {
    switch (block) {
        case Growth:
            if (growth_spawn_timer > 0 || growth_cnt >= Misc::GROWTH_MAX_COUNT)
                return false;
            break;

        case Poison:
            if (poison_spawn_timer > 0 || poison_cnt >= Misc::POISON_MAX_COUNT)
                return false;
            break;
        case GateIn:

            break;
        //TODO : case gate
        default:
            break;
    }
    return true;
}

bool Spawner::getRottenGrowth(int &rotten_x, int &rotten_y) {
    if(growth_items.empty())
        return false;

    if(growth_items.front().life <= 0)
    {
        rotten_x = growth_items.front().x;
        rotten_y = growth_items.front().y;
        growth_items.pop_front();
        growth_cnt--;
        return true;
    }

    return false;
}

bool Spawner::getRottenPoison(int &rotten_x, int &rotten_y) {
    if(poison_items.empty())
        return false;

    if(poison_items.front().life <= 0)
    {
        rotten_x = poison_items.front().x;
        rotten_y = poison_items.front().y;
        poison_items.pop_front();
        poison_cnt--;
        return true;
    }

    return false;
}

void Spawner::spawnGate(int in_x, int in_y, int outX, int outY) {
    gate.x = in_x;
    gate.y = in_y;

    gate.out_x = outX;
    gate.out_y = outY;

    gate.fixed = false;
    //TODO : 생성확인
    //TODO : 기능구현

    if(outX == 0) // in left wall
    {
        gate.fixed = true;
        gate.out_dir = MoveDir::Right;
        gate.out_x = 1;
    }
}
