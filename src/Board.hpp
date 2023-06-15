#pragma once

class Board
{
private:
    int width{}, height{};
    int start_y{}, start_x{};
    WINDOW* win_map{};
    int **map{};
    int m_size{};

    void buildMap();
    void printMap();
public:

    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    //아이템, 스네이크가 맵을 refresh할때 쓸 함수
    void refreshMapData(int x, int y, BlockType bt, GameCondition& cond);
};

void Board::awake(int h, int w, int starty, int startx)
{
    height = h;
    width = w;
    start_y = starty;
    start_x = startx;
    win_map = newwin(height, width, start_y, start_x);

    buildMap();
}

//TODO: map 배열에 저장된 snake, item, gate 정보를 받아서 업데이트 한 후 출력하는 역할
void Board::update()
{

    werase(win_map);
    box(win_map, 0, 0);

    printMap();

    wrefresh(win_map);
}

void Board::onDisable()
{
    for(int i = 0; i < m_size; i++)
        delete[] map[i];
    delete[] map;

    delwin(win_map);
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
            if(map[i][j] == BlockType::SnakeHead)
            {
                wattron(win_map, COLOR_PAIR(1));
                mvwprintw(win_map, i, j, "H");
                wattroff(win_map , COLOR_PAIR(1));
            }
            else if (map[i][j] == BlockType::SnakeBody)
            {
                wattron(win_map, COLOR_PAIR(2));
                mvwprintw(win_map, i, j, "H");
                wattroff(win_map , COLOR_PAIR(2));
            }
            else if(map[i][j] == BlockType::GateIn)
            {
                //TODO : COLOR PAIR 만들기, Snake, Gate, Item 이 프린트 될 색깔 정하기
                //wattr_on(win_map, COLOR_PAIR(1));
                mvwprintw(win_map, i, j, "O");
                //wattr_off(win_map, COLOR_PAIR(1));
            }
        }
    }
}

void Board::refreshMapData(int x, int y, BlockType bt, GameCondition& cond)
{
    if(x < 0 || y < 0 || x > m_size || y > m_size)
    {
        //invalid condition check
        //throw
        printw("Out of Range Exception");
        return;
    }
    if(map == nullptr)
    {
        //init fail exception
    }
    map[y][x] = bt;
}

