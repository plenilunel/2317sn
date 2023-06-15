#include <ncurses.h>
#include <csignal>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

#include "src/Stage.hpp"
#include "src/Misc.hpp"
#include "src/Board.hpp"
#include "src/snake.hpp"
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
    mvprintw(10, 10, "GAME END..");
    refresh();
    getch();
    endwin(); // 게임종료

    return 0;
}
