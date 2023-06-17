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

    int growth_cnt;
    int growth_spawn_timer;
    deque<Item> growth_items;

    int poison_cnt;
    int poison_spawn_timer;
    deque<Item> poison_items;

    bool isGateSpawn;
    Gate gate;

public:
    void awake(int, int);
    void getRandomPosition(int& x, int& y) const;

    void update();

    void spawnGrowthItem(int x, int y);
    bool getRottenGrowth(int& rotten_x, int& rotten_y);

    void spawnPoisonItem(int x, int y);
    bool getRottenPoison(int& rotten_x, int& rotten_y);

    void spawnGate(int inX, int inY, int outX, int outY);
    bool getRottenGate(Gate& result);
    void setGateActive(int second);
    void getGateDestination(int& destX, int& destY);

    [[nodiscard]] bool canSpawn(BlockType block) const;
};

void Spawner::awake(int height, int width) {
    srand(time(NULL));

    range_x = width;
    range_y = height;

    growth_cnt = growth_spawn_timer = 0;
    poison_cnt = poison_spawn_timer = 0;
    isGateSpawn = false;
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
    if(isGateSpawn)
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
            if (isGateSpawn)
                return false;
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

void Spawner::spawnGate(int inX, int inY, int outX, int outY) {

    isGateSpawn = true;
    gate.active = false;
    gate.fixed = false;
    gate.life = Misc::GATE_LIFE_TIME;

    gate.x = inX;
    gate.y = inY;

    gate.out_x = outX;
    gate.out_y = outY;

    //TODO : 생성확인
    //TODO : 기능구현

    if (outX == 0) // in left wall
    {
        gate.fixed = true;
        gate.out_dir = MoveDir::Right;
        gate.dest_x = 1;
        gate.dest_y = outY;
    }
    if (outX == range_x - 1)
    {
        gate.fixed = true;
        gate.out_dir = MoveDir::Left;
        gate.dest_x = range_x - 2;
        gate.dest_y = outY;
    }
    if (outY == 0)
    {
        gate.fixed = true;
        gate.out_dir = MoveDir::Down;
        gate.dest_x = outX;
        gate.dest_y = 1;
    }
    if (outY == range_y - 1)
    {
        gate.fixed = true;
        gate.out_dir = MoveDir::Up;
        gate.dest_x = outX;
        gate.dest_y = range_y-2;
    }
}

bool Spawner::getRottenGate(Gate &result) {

    if (gate.life <= 0 && !gate.active)
    {
        result = gate;
        isGateSpawn = false;
        return true;
    }
    return false;
}

void Spawner::setGateActive(int second) {
    gate.life = second + 2;
    gate.active = true;
}

void Spawner::getGateDestination(int &destX, int &destY) {

    destY = gate.dest_y;
    destX = gate.dest_x;
}
