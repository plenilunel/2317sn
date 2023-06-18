#include <ncurses.h>
#include <csignal>
#include <deque>

using namespace std;

//#define DEBUG

#include "src/Misc.hpp"
#include "src/Stage.hpp"
#include "src/ScoreBoard.hpp"
#include "src/Board.hpp"
#include "src/snake.hpp"
#include "src/Spawner.hpp"
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
        {
            gm.onDisable();
            mvprintw((LINES-1)/2, (COLS/2)-8, "GAME END..");
            break;
        }
        else if (game_condition == 2)
        {
            gm.onDisable();
            mvprintw((LINES-1)/2, (COLS/2)-8, "WIN..");
            break;
        }

        usleep(100000);
    }



    refresh();
    getch();
    endwin(); // 게임종료

    return 0;
}
