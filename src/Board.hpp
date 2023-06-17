#pragma once

class Board
{
private:
    int width{}, height{};
    int start_y{}, start_x{};
    WINDOW* win_map{};
    int **map{};

    void buildMap(int stage = 1);
    void printMap();
public:
    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    void clear();
    //아이템, 스네이크가 맵을 refresh할때 쓸 함수
    BlockType getMapData(int x, int y);
    void setMapData(int x, int y, BlockType block);
    WINDOW*& getWinMap() { return win_map; }

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

void Board::update()
{
    printMap();

    wrefresh(win_map);
}

void Board::onDisable()
{
    for(int i = 0; i < height; i++)
        delete[] map[i];
    delete[] map;

    delwin(win_map);
}

void Board::clear()
{
    werase(win_map);
    box(win_map, 0, 0);
}

void Board::buildMap(int stage_idx) {
    mvprintw(0,0,"%d %d",height,width);
    map = new int*[height];
    for (int i = 0; i < height; i++)
        map[i] = new int[width];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
                map[i][j] = BlockType::Wall;
            else
                map[i][j] = BlockType::Empty;

    map[0][0] = map[0][width - 1] = map[height - 1][0] = map[height - 1][width - 1] = BlockType::Conner;

// 스테이지 만드는 문법
//    map[0][3] = BlockType::GateIn;
//    map[height - 1][7] = BlockType::GateOut;
}

void Board::printMap()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(map[i][j] == BlockType::Conner || map[i][j] == BlockType::Wall)
            {
//                wattron(win_map, COLOR_PAIR(3));
//                mvwaddch(win_map, i, j, ' ');
//                wattroff(win_map , COLOR_PAIR(3));
            }
            else if (map[i][j] == BlockType::GateIn)
            {
                wattron(win_map, COLOR_PAIR(4) | A_UNDERLINE | A_HORIZONTAL | A_BOLD);
                mvwaddch(win_map, i, j, 'O');
                wattroff(win_map , COLOR_PAIR(4)| A_UNDERLINE| A_HORIZONTAL | A_BOLD);
            }
            else if (map[i][j] == BlockType::GateOut)
            {
                wattron(win_map, COLOR_PAIR(5) | A_UNDERLINE);
                mvwaddch(win_map, i, j, 'O');
                wattroff(win_map , COLOR_PAIR(5)| A_UNDERLINE);
            }
            else if(map[i][j] == BlockType::Growth)
            {
                wattron(win_map, COLOR_PAIR(6) | A_VERTICAL | A_BOLD | A_BLINK);
                mvwaddch(win_map, i, j, 'G');
                wattroff(win_map , COLOR_PAIR(6) | A_VERTICAL | A_BOLD | A_BLINK);
            }
            else if(map[i][j] == BlockType::Poison)
            {
                wattron(win_map, COLOR_PAIR(7) | A_VERTICAL | A_BOLD | A_BLINK);
                mvwaddch(win_map, i, j, 'P');
                wattroff(win_map , COLOR_PAIR(7) | A_VERTICAL | A_BOLD | A_BLINK);
            }
        }
    }
}

BlockType Board::getMapData(int x, int y)
{
    if(x < 0 || y < 0 || x > width || y > height)
    {
        printw("Get Out of Range [%d, %d]", x, y);
        return BlockType::Error;
    }

    return (BlockType)map[y][x];
}

void Board::setMapData(int x, int y, BlockType block)
{
    if(x < 0 || y < 0 || x > width || y > height)
    {
        printw("Set Out of Range [%d, %d]", x, y);
        return;
    }

    map[y][x] = block;
}

