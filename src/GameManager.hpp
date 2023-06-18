#pragma once

class GameManager
{
private:
    chtype input{};
    Board board;
    ScoreBoard score;
    Snake snake{};
    Spawner spawner;
    int condition{1};
    int curr_stage{1};

    static void initSnakeGame();
    void initMisc();

    void moveSnake(chtype ch);
    void validate(BlockType bt);

    void applyItemBlock(BlockType block);
    void spawnItem();
    void updateItemInfo();

    void updateScoreInfo();

    void displayBoard();
    void displayScore();
public:

    void awake(); // awake

    int update();

    void onDisable();
};

void GameManager::awake()
{
    initSnakeGame();
    initMisc();

    //init mainBoard
    board.awake(Misc::DIMENSION,
                Misc::DIMENSION + Misc::DIMENSION/2,
                (Misc::WIN_HEIGHT - Misc::DIMENSION) / 2,
                (Misc::WIN_WIDTH - Misc::DIMENSION) / 2 - Misc::DIMENSION - Misc::DIMENSION/4);

    score.awake(Misc::DIMENSION/2,
                (Misc::DIMENSION + Misc::DIMENSION/2),
                (Misc::WIN_HEIGHT - Misc::DIMENSION) / 2 + 1,
                (Misc::WIN_WIDTH - Misc::DIMENSION) / 2 + Misc::DIMENSION/3);

    spawner.awake(Misc::DIMENSION,Misc::DIMENSION + Misc::DIMENSION/2);

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
    use_default_colors();

    init_pair(1, COLOR_CYAN, COLOR_CYAN); //snake head
    init_pair(2, COLOR_BLUE, COLOR_BLUE); // snake body
    init_pair(3, COLOR_WHITE, COLOR_WHITE); // wall and conner
    init_pair(4, COLOR_BLUE, COLOR_WHITE); // gate in color
    init_pair(5, COLOR_RED, COLOR_WHITE); // gate out color
    init_pair(6, COLOR_GREEN, COLOR_BLACK); // Growth Item Color
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); // Poison Item Color

    init_pair(10, COLOR_BLACK, COLOR_WHITE); // bg
    wbkgd(stdscr, COLOR_PAIR(10));
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

    if (condition)
    {
        updateScoreInfo();
        updateItemInfo();
        spawnItem();
        displayScore();
        displayBoard();

        if (curr_stage != score.getCurrStage())
        {
            curr_stage = score.getCurrStage();
            board.buildMap(curr_stage);
        }

        if (curr_stage == 0)
            return 2;


    }

    return condition;
}

void GameManager::onDisable()
{
    board.onDisable();
    score.onDisable();
    nodelay(stdscr, false);
    clear();
}

//handle input
void GameManager::moveSnake(chtype ch) {
    switch (ch) {
        case KEY_DOWN:
            if(snake.m_dir == Up)
                condition = false;
            snake.move(Down);
            break;
        case KEY_UP:
            if(snake.m_dir == Down)
                condition = false;
            snake.move(Up);
            break;
        case KEY_RIGHT:
            if(snake.m_dir == Left)
                condition = false;
            snake.move(Right);
            break;
        case KEY_LEFT:
            if(snake.m_dir == Right)
                condition = false;
            snake.move(Left);
            break;
        case 'q':
            condition = false;
        default:
            snake.move(snake.m_dir);
    }
}

void GameManager::applyItemBlock(BlockType block) {
    if (block == BlockType::Growth)
    {
        score.addGrowthScore();
        snake.insert();
        board.setMapData(snake.head->x, snake.head->y, Empty);
    }
    else if (block == BlockType::Poison)
    {
        score.addPoisonScore();
        snake.remove();
        board.setMapData(snake.head->x, snake.head->y, Empty);
    }
    else if (block == BlockType::GateIn)
    {
        score.addGateScore();
        spawner.setGateActive(snake._size);


        int destX, destY;
        int i = 0;
        do {
            spawner.getGateDestination(destX, destY, static_cast<MoveDir>((snake.m_dir + i) % 4), i++ == 0);
        }while(i < 4 && board.getMapData(destX, destY) == BlockType::Wall);

        snake.m_dir = spawner.getGate().out_dir;
        snake.move(destX, destY);
    }
}

void GameManager::validate(BlockType bt)
{
    if(!condition)
        return;

    //check snake condition
    condition = snake.isAlive();

    //check collision with wall and snake
    switch (bt) {
        case Wall:
        case Conner:
        case GateOut:
            condition = false;
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

    board.update();
}

void GameManager::displayScore() {
    score.clear();
    score.update();
}
void GameManager::updateItemInfo()
{
    spawner.update();

    int rottenItemPos_x;
    int rottenItemPos_y;
    //한번에 두개 이상의 아이템이 사라질 수 없음. (respectively)
    if (spawner.getRottenGrowth(rottenItemPos_x, rottenItemPos_y))
        board.setMapData(rottenItemPos_x, rottenItemPos_y, Empty);

    if(spawner.getRottenPoison(rottenItemPos_x, rottenItemPos_y))
        board.setMapData(rottenItemPos_x, rottenItemPos_y, Empty);

    Gate tmp;
    if(spawner.getRottenGate(tmp))
    {
        board.setMapData(tmp.x, tmp.y, BlockType::Wall);
        board.setMapData(tmp.out_x, tmp.out_y, BlockType::Wall);
    }
}

void GameManager::updateScoreInfo() {
    score.updateTime();
    score.setSnakePos(snake.head->x, snake.head->y);
    score.setSnakeSize(snake._size);
    score.checkMissionCondition();
}

void GameManager::spawnItem() {
    int x, y;

    if(spawner.canSpawn(BlockType::Growth))
    {
        do {
            spawner.getRandomPosition(x, y);
        }while(board.getMapData(x,y) != BlockType::Empty || snake.isInSnake(x,y));

        spawner.spawnGrowthItem(x, y);
        board.setMapData(x, y, Growth);
    }

    if(spawner.canSpawn(BlockType::Poison))
    {
        do {
            spawner.getRandomPosition(x, y);
        }while(board.getMapData(x,y) != BlockType::Empty || snake.isInSnake(x,y));

        spawner.spawnPoisonItem(x, y);
        board.setMapData(x, y, Poison);
    }

    if(spawner.canSpawn(BlockType::GateIn))
    {
        int x2, y2;

        do {
            spawner.getRandomPosition(x, y);
        }while(board.getMapData(x,y) != BlockType::Wall);

        board.setMapData(x, y, GateIn);

        do {
            spawner.getRandomPosition(x2, y2);
        }while(board.getMapData(x2,y2) != BlockType::Wall);

        board.setMapData(x2, y2, GateOut);

        spawner.spawnGate(x, y, x2, y2);
    }
}

