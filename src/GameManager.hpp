#pragma once

class GameManager
{
private:
    int ch{};
    Board board;
    Snake snake{};

    static void initSnakeGame();
    void initMisc();
    
//    GameCondition isValid() { return 1; }
    
//    GameManager()= default;
//    GameManager(const GameManager& other){};
//    ~GameManager()= default;
public:
//    static GameManager& getInst() { static GameManager gm; return gm; }

    void awake(); // awake

    int update();

    void onDisable();
};

void GameManager::awake()
{
    initSnakeGame();
    initMisc();

    //init mainBoard
    board.awake(Misc::DIMENSION/2,
                Misc::DIMENSION,
                (Misc::WIN_HEIGHT - Misc::DIMENSION) / 2 + 10,
                (Misc::WIN_WIDTH - Misc::DIMENSION) / 2 - 20);

    //init snake
    snake.awake();
}

int GameManager::update()
{
    ch = getch();

    switch (ch) {
        case KEY_DOWN:
            if(snake.m_dir == MoveDir::Up)
                return 0;
            snake.move(MoveDir::Down);
            break;
        case KEY_UP:
            if(snake.m_dir == MoveDir::Down)
                return 0;
            snake.move(MoveDir::Up);
            break;
        case KEY_RIGHT:
            if(snake.m_dir == MoveDir::Left)
                return 0;
            snake.move(MoveDir::Right);
            break;
        case KEY_LEFT:
            if(snake.m_dir == MoveDir::Right)
                return 0;
            snake.move(MoveDir::Left);
            break;
        case 'q':
            return 0;
    }
    board.clear();

    auto *p = snake.head;

    while(p)
    {
        wattron(board.getWinMap(), COLOR_PAIR(1));
        mvwprintw(board.getWinMap(), p->y, p->x, "X");
        wattroff(board.getWinMap(), COLOR_PAIR(1));
        p = p->next;
    }

    //consume item

    //generate item

    //condition check


    board.update();
    return 1;
}

void GameManager::onDisable()
{
    board.onDisable();
    //nodelay(stdscr, false);
    clear();
}

void GameManager::initSnakeGame()
{
    //게임 초기화
    initscr(); // 터미널 초기화
    cbreak(); // 입력 연속으로 읽게 하기
    noecho(); // 입력 echo 허용안하게 하기 (화면에 입력된 키가 나오지 않게 하기)
    //nodelay(stdscr, TRUE);
    keypad(stdscr, true); // 방향키 , F1 등 입력 받게 하기
    curs_set(0);
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
}

void GameManager::initMisc()
{
    //set misc
    getmaxyx(stdscr, Misc::WIN_HEIGHT, Misc::WIN_WIDTH);
    Misc::DIMENSION = 48;
    Misc::SNAKE_START_XPOS = 10;
    Misc::SNAKE_START_YPOS = 10;
}
