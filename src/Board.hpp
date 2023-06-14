#ifndef SNAKE_BOARD_HPP
#define SNAKE_BOARD_HPP

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
    void printMap();
public:

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

//TODO: map 배열에 저장된 snake, item, gate 정보를 받아서 업데이트 한 후 출력하는 역할
void Board::update()
{

    werase(win);
    box(win, 0, 0);

    printMap();

    wrefresh(win);
}

void Board::onDisable()
{
    for(int i = 0; i < m_size; i++)
        delete[] map[i];
    delete[] map;

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
    map[0][3] = map[m_size-1][7] = BlockType::GateIn;
}

void Board::printMap()
{
    for(int i = 0; i < m_size; i++)
    {
        for(int j = 0; j < m_size; j++)
        {
            if(map[i][j] == BlockType::GateIn)
            {
                //TODO : COLOR PAIR 만들기, Snake, Gate, Item 이 프린트 될 색깔 정하기
                //wattr_on(win, COLOR_PAIR(1));
                mvwprintw(win, i, j, "O");
                //wattr_off(win, COLOR_PAIR(1));
            }
        }
    }
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

#endif