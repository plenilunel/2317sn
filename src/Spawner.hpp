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
    int range_x;
    int range_y;

    int growth_cnt;
    int growth_spawn_timer;
    deque<Item> growth_items;

    int poison_cnt;
    int poison_spawn_timer;
public:
    void awake(int, int);
    void getRandomPosition(int& x, int& y) const;

    void update();

    void spawnGrowthItem(int x, int y);

    bool getRottenGrowth(int& rotten_x, int& rotten_y);

    [[nodiscard]] bool canSpawn(BlockType block) const;
};

void Spawner::awake(int height, int width) {
    srand(time(NULL));

    range_x = width - 2;
    range_y = height - 2;

    growth_cnt = poison_cnt = growth_spawn_timer = poison_spawn_timer = 0;
}

void Spawner::getRandomPosition(int &x, int &y) const
{
    x = rand() % range_x + 1;
    y = rand() % range_y + 1;
}

void Spawner::spawnGrowthItem(int x, int y)
{
    growth_spawn_timer = Misc::GROWTH_SPAWN_DELAY;
    growth_items.push_back(Item(x, y, Misc::GROWTH_LIFE_TIME));
    growth_cnt++;
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

void Spawner::update() {

    growth_spawn_timer--;

    if(!growth_items.empty())
    {
        for(auto & item : growth_items)
            item.life--;
    }
}
