#pragma once

#include <ncurses.h>
#include "Board.hpp"
#include "Misc.hpp"
#include "snake.hpp"

#define DEFEAT 0

class GameManager
{
private:
    int ch{};
    int condition{1};
    Board board;

    static void initSnakeGame();
    static void initMisc();
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
    board.awake(Misc::MAP_SIZE,
              Misc::MAP_SIZE * 2,
              (Misc::WIN_HEIGHT - Misc::MAP_SIZE) / 2,
              (Misc::WIN_WIDTH - Misc::MAP_SIZE) / 2);
}

int GameManager::update()
{
    ch = getch();
    if(ch == 'q' || ch == KEY_DOWN)
        return DEFEAT;

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
}

void GameManager::initMisc()
{
    //set misc
    getmaxyx(stdscr, Misc::WIN_HEIGHT, Misc::WIN_WIDTH);
    Misc::MAP_SIZE = 21;
}