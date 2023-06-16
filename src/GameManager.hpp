#pragma once

class GameManager
{
private:
    chtype input{};
    Board board;
    Snake snake{};
    Spawner spawner;
    bool isValid{true};
    static void initSnakeGame();
    void initMisc();

    void moveSnake(chtype ch);
    void validate(BlockType bt);
    void applyItemBlock(BlockType block);
public:

    void awake(); // awake

    int update();

    void onDisable();

    void displayBoard();

    void spawnItem();
};

void GameManager::awake()
{
    initSnakeGame();
    initMisc();

    //init mainBoard
    board.awake(Misc::DIMENSION,
                Misc::DIMENSION + Misc::DIMENSION/2,
                (Misc::WIN_HEIGHT - Misc::DIMENSION) / 2,
                (Misc::WIN_WIDTH - Misc::DIMENSION) / 2 - Misc::DIMENSION);

    //init snake
    snake.awake();
}

void GameManager::initSnakeGame()
{
    //게임 초기화
    initscr(); // 터미널 초기화
    cbreak(); // 입력 연속으로 읽게 하기
    noecho(); // 입력 echo 허용안하게 하기 (화면에 입력된 키가 나오지 않게 하기)
    nodelay(stdscr, TRUE); //입력 없을때도 getch() err으로 리턴하게 하기
    keypad(stdscr, true); // 방향키 , F1 등 입력 받게 하기
    curs_set(0);
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_YELLOW); //snake head
    init_pair(2, COLOR_BLUE, COLOR_BLUE); // snake body
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // bg
    init_pair(4, COLOR_WHITE, COLOR_WHITE); // wall and conner
    init_pair(5, COLOR_GREEN, COLOR_WHITE); // gate in color
    wbkgd(stdscr, COLOR_PAIR(3));
}

void GameManager::initMisc()
{
    //set misc
    getmaxyx(stdscr, Misc::WIN_HEIGHT, Misc::WIN_WIDTH);
    Misc::DIMENSION = Misc::WIN_HEIGHT - 5;
}

int GameManager::update()
{
    input = getch();

    moveSnake(input);

    BlockType block = board.getMapData(snake.head->x, snake.head->y);

    applyItemBlock(block);

    //check condition is valid or not
    validate(block);


    //if valid then display and spawn item
    //spawn item and gate in valid position
    if (isValid)
    {
        spawnItem();
        displayBoard();
    }


    return isValid;
}

void GameManager::onDisable()
{
    board.onDisable();
    nodelay(stdscr, false);
    clear();
}

//handle input
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

void GameManager::applyItemBlock(BlockType block) {
    if (block == BlockType::Growth)
    {
        snake.insert();
        board.setMapData(snake.head->x, snake.head->y, Empty);
    }
    else if (block == BlockType::Poison)
    {
        snake.remove();
        board.setMapData(snake.head->x, snake.head->y, Empty);
    }
    else if (block == BlockType::GateIn)
    {
        //TODO : get Gate Out position and Move snake head to that pos
        //by inverting move direction
    }
}

void GameManager::validate(BlockType bt)
{
    if(!isValid)
        return;

    //check snake condition
    isValid = snake.isAlive();

    //check collision with wall and snake
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

void GameManager::displayBoard() {
    board.clear();
    WINDOW* window_map = board.getWinMap();

    //print snake head
    auto *p = snake.head;
    wattron(window_map, COLOR_PAIR(1));
    mvwaddch(window_map, p->y, p->x, ' ');
    wattroff(window_map, COLOR_PAIR(1));
    p = p->next;
    //print snake body
    while(p)
    {
        wattron(window_map, COLOR_PAIR(2));
        mvwaddch(window_map, p->y, p->x, ' ');
        wattroff(window_map, COLOR_PAIR(2));
        p = p->next;
    }

    //TODO : print item
    //TODO : print Gate
    board.update();
}

void GameManager::spawnItem() {

}
