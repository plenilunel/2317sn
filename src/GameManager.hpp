#pragma once

class GameManager
{
private:
    int ch{};
    GameCondition condition{};
    Board board;
    Snake snake{};

    static void initSnakeGame();
    static void initMisc();

    GameCondition checkCondition();

    GameManager()= default;
    GameManager(const GameManager& other){};
    ~GameManager()= default;
public:
    static GameManager& getInst() { static GameManager gm; return gm; }

    void awake(); // awake

    int update();

    void onDisable();
};

void GameManager::awake()
{
    initSnakeGame();
    initMisc();

    //init mainBoard
    board.awake(Misc::MAP_SIZE,
                Misc::MAP_SIZE * 2,
                (Misc::WIN_HEIGHT - Misc::MAP_SIZE) / 2,
                (Misc::WIN_WIDTH - Misc::MAP_SIZE) / 2);

    //init snake
    snake.awake();
}

int GameManager::update()
{
    ch = getch();
    if(ch == 'q') //input test
        return 0;
    else if (ch == KEY_DOWN)
        snake.move(0, -1);
    else if (ch == KEY_UP)
        snake.move(0, 1);
    else if (ch == KEY_LEFT)
        snake.move(-1, 0);
    else if (ch == KEY_RIGHT)
        snake.move(1, 0);

    condition = checkCondition();

    //generate item
    //TODO : condition check
    board.update();

    return condition;
}

void GameManager::onDisable()
{
    board.onDisable();
    nodelay(stdscr, false);
    clear();
}

void GameManager::initSnakeGame()
{
    //게임 초기화
    initscr(); // 터미널 초기화
    refresh();
    curs_set(0);
    cbreak(); // 입력 연속으로 읽게 하기
    noecho(); // 입력 echo 허용안하게 하기 (화면에 입력된 키가 나오지 않게 하기)
    nodelay(stdscr, TRUE);
    keypad(stdscr, true); // 방향키 , F1 등 입력 받게 하기
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
}

void GameManager::initMisc()
{
    //set misc
    getmaxyx(stdscr, Misc::WIN_HEIGHT, Misc::WIN_WIDTH);
    Misc::MAP_SIZE = 21;
    Misc::SNAKE_START_XPOS = 10;
    Misc::SNAKE_START_YPOS = 10;
}

GameCondition GameManager::checkCondition()
{
    //TODO : Check snake case
    auto *p = snake.head; //Body* type

    while(p)
    {
        board.refreshMapData(p->x, p->y, SnakeBody, condition); // if can't refresh(etc. occur collapse, condition will be changed

        p = p->next;
    }

    return GameCondition::Win;
}