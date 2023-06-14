#include <ncurses.h>
#include <csignal>
#include "src/GameManager.hpp"

int main()
{
    GameManager gm;

    gm.awake();
    int game_condition;
    while(true)
    {
        game_condition = gm.update();

        if(game_condition == 0)
            break;
        usleep(110000);
    }
    gm.onDisable();
//
//    for (auto i = 0; i < 30; i++) // draws top
//    {
//        mvaddch(0, i, 219);
//    }
//
//    for (auto i = 0; i < 30; i++) // draws bottom
//    {
//        mvaddch(30, i, 219);
//    }
//
//    for (auto i = 0; i < 30; i++) // draws left side
//    {
//        move(i, 0);
//        addch(219);
//    }
//
//    for (auto i = 0; i < 30; i++) // draws right side
//    {
//        move(i, 30);
//        addch(219);
//    }
//    refresh();
    mvprintw(10, 10, "GAME END..");
    refresh();
    getch();
    endwin(); // 게임종료

    return 0;
}