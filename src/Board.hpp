#pragma once

class Board
{
private:
    int width{}, height{};
    int start_y{}, start_x{};
    WINDOW* win_map{};
    int **map{};


    void printMap();
public:
    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    void clear();

    void buildMap(int stage = 1);
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

    map = new int*[height];
    for (int i = 0; i < height; i++)
        map[i] = new int[width];

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
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
                map[i][j] = BlockType::Wall;
            else
                map[i][j] = BlockType::Empty;
    map[0][0] = map[0][width - 1] = map[height - 1][0] = map[height - 1][width - 1] = BlockType::Conner;


    switch (stage_idx) {
        case 1:
            Stage::stage1(map, height, width);
            break;
        case 2:
            Stage::stage2(map, height, width);
            break;
        case 3:
            Stage::stage3(map,height, width);
            break;
        case 4:
            Stage::stage4(map, height, width);
            break;
        default:
            break;
    }
}

void Board::printMap()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(map[i][j] == BlockType::Conner || map[i][j] == BlockType::Wall) //
            {
                wattron(win_map, COLOR_PAIR(3));
                mvwaddch(win_map, i, j, ' ');
                wattroff(win_map , COLOR_PAIR(3));
            }
            else if (map[i][j] == BlockType::GateIn)
            {
                wattron(win_map, COLOR_PAIR(4) | A_UNDERLINE);
                mvwaddch(win_map, i, j, 'O');
                wattroff(win_map , COLOR_PAIR(4)| A_UNDERLINE);
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
    if (x < 0 || y < 0 || x > width || y > height)
        return BlockType::Error;


    return (BlockType)map[y][x];
}

void Board::setMapData(int x, int y, BlockType block)
{
    if (x < 0 || y < 0 || x > width || y > height)
        return;

    if(x == 0 && y == 0)
        return;
    map[y][x] = block;
}

