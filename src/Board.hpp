#pragma once

#include <ncurses.h>
#include "Misc.hpp"

class Board
{
private:
    int width{}, height{};
    int start_y{}, start_x{};
    WINDOW* win{};

    int **map{};
    int m_size{};

    void buildMap();
public:
    Board() = default;

    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    //아이템, 스네이크가 맵을 refresh할때 쓸 함수
     void changeMapData(int x, int y, BlockType bt);
};

void Board::awake(int h, int w, int starty, int startx)
{
    height = h;
    width = w;
    start_y = starty;
    start_x = startx;
    win = newwin(height, width, start_y, start_x);

    buildMap();
}

void Board::update()
{
    // 순서 - ls - rs - ts - bs -|| tl - tr - bl - br
    werase(win);
    box(win, 0, 0);

    for(int j = 0; j < m_size; j++)
        if(map[0][j] == BlockType::GateIn)
        {
            //TODO : COLOR PAIR 만들기, Snake, Gate, Item 이 프린트 될 색깔 정하기
            //wattr_on(win, COLOR_PAIR(1));
            mvwprintw(win, 0, j, "O");
            //wattr_off(win, COLOR_PAIR(1));
        }
    wrefresh(win);
}

void Board::onDisable()
{
    delwin(win);
}

void Board::buildMap() {
    m_size = Misc::MAP_SIZE;
    map = new int*[m_size];
    for (int i = 0; i < m_size; i++)
        map[i] = new int[m_size];

    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
            if (i == 0 || j == 0 || i == m_size-1 || j == m_size-1)
                map[i][j] = BlockType::Wall;
            else
                map[i][j] = BlockType::Empty;

    map[0][0] = map[0][m_size-1] = map[m_size-1][0] = map[m_size-1][m_size-1] = BlockType::Conner;
    //TODO: finish debugging
    map[0][3] = BlockType::GateIn;
}

void Board::changeMapData(int x, int y, BlockType bt)
{
    if(x < 0 || y < 0 || x > m_size || y > m_size)
    {
        //invalid condition check
        printw("Out of Range Exception");
        return;
    }

    map[y][x] = bt;
}