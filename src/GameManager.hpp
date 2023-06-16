#pragma once

#include <curses.h>

class GameManager
{
private:
    chtype input{};
    Board board;
    Snake snake{};
    bool isValid{true};
    static void initSnakeGame();
    void initMisc();

    void moveSnake(chtype ch);
    void validate();
public:

    void awake(); // awake

    int update();

    void onDisable();

    void displayBoard();
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


void GameManager::initSnakeGame()
{
    //게임 초기화
    initscr(); // 터미널 초기화
    cbreak(); // 입력 연속으로 읽게 하기
    noecho(); // 입력 echo 허용안하게 하기 (화면에 입력된 키가 나오지 않게 하기)
    nodelay(stdscr, TRUE);
    keypad(stdscr, true); // 방향키 , F1 등 입력 받게 하기
    curs_set(0);
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(3));
}

void GameManager::initMisc()
{
    //set misc
    getmaxyx(stdscr, Misc::WIN_HEIGHT, Misc::WIN_WIDTH);
    Misc::DIMENSION = 48;
    Misc::SNAKE_START_XPOS = 10;
    Misc::SNAKE_START_YPOS = 10;
}


int GameManager::update()
{
    input = getch();

    //handle input
    moveSnake(input);

    //eat item

    validate();
    //check condition is valid or not

    //if valid then display and spawn item
    //spawn item and gate in valid position
    if (isValid)
        displayBoard();

    return isValid;
}

void GameManager::displayBoard() {
    board.clear();

    auto *p = snake.head;

    //Debug
    while(p)
    {
        wattron(board.getWinMap(), COLOR_PAIR(1));
        mvwprintw(board.getWinMap(), p->y, p->x, "X");
        wattroff(board.getWinMap(), COLOR_PAIR(1));
        p = p->next;
    }

    board.update();
}

void GameManager::moveSnake(chtype ch) {
    switch (ch) {
        case KEY_DOWN:
            if(snake.m_dir == Up)
                isValid = false;
            snake.move(Down);
            break;
        case KEY_UP:
            if(snake.m_dir == Down)
                isValid = false;
            snake.move(Up);
            break;
        case KEY_RIGHT:
            if(snake.m_dir == Left)
                isValid = false;
            snake.move(Right);
            break;
        case KEY_LEFT:
            if(snake.m_dir == Right)
                isValid = false;
            snake.move(Left);
            break;
        case 'q':
            isValid = false;
        default:
            snake.move(snake.m_dir);
    }
}

void GameManager::validate()
{
    if(!isValid)
        return;

    //check snake condition
    isValid = snake.isAlive();

    //check collision with wall and snake
    BlockType bt = board.getMapData(snake.head->x, snake.head->y);
    switch (bt) {
        case Wall:
        case Conner:
            isValid = false;
            break;
#ifdef DEBUG
        case Error:
            printw("snake is placed over map");
            break;
#endif
        default:
            break;
    }
}

void GameManager::onDisable()
{
    board.onDisable();
    nodelay(stdscr, false);
    clear();
}
