//
// Created by Administrator on 6/17/2023.
//

#ifndef SNAKE_SCOREHANDLER_H
#define SNAKE_SCOREHANDLER_H

#include <chrono>

class ScoreBoard{
private:
    int width{}, height{};
    int start_y{}, start_x{};
    WINDOW* score_win{};
    WINDOW* mission_win{};
    int snake_pos_x{};
    int snake_pos_y{};
    int snake_size{};
    int gate_score{};
    int growth_score{};
    int poison_score{};
    int total_score{};
    int prev_score{};
    int stage{1};

    void printStage1();
    char stage1_mission1{'X'};
    char stage1_mission2{'X'};
    char stage1_mission3{'X'};

    void printStage2();
    char stage2_mission1{'X'};
    char stage2_mission2{'X'};
    char stage2_mission3{'X'};

    void printStage3();
    char stage3_mission1{'X'};
    char stage3_mission2{'X'};
    char stage3_mission3{'X'};

    void printStage4();
    char stage4_mission1{'X'};
    char stage4_mission2{'X'};
    char stage4_mission3{'X'};

    long time{};
    chrono::time_point<chrono::steady_clock> start_time{};
    chrono::time_point<chrono::steady_clock> curr_time{};
    void updateScoreWin();
    void calcTotal_Score();

    void updateMissionWin();

    static bool isMissionComplete(char& m1, char& m2, char& m3);
    void clearScore();
public:
    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    void clear();

    [[nodiscard]] int getCurrStage() const {return stage;}
    void checkMissionCondition();

    void setSnakePos(int x, int y);
    void setSnakeSize(int size);
    void addGateScore(int amount = 1);
    void addGrowthScore(int amount = 1);
    void addPoisonScore(int amount = 1);
    void updateTime();
};

void ScoreBoard::awake(int h, int w, int starty, int startx) {
    start_time = chrono::steady_clock::now();

    height = h;
    width = w;
    start_y = starty;
    start_x = startx;

    score_win = newwin(height/2 + height/3, width, start_y, start_x);
    mission_win = newwin(height/2 + height/4, width, start_y +height/2 + height/3, start_x);

    wbkgd(score_win, COLOR_PAIR(10) | A_BOLD);
    wbkgd(mission_win, COLOR_PAIR(10) | A_BOLD);
}

void ScoreBoard::update() {
    updateMissionWin();

    calcTotal_Score();
    updateScoreWin();
}

void ScoreBoard::onDisable() {
    delwin(score_win);
    delwin(mission_win);
}

void ScoreBoard::clear() {
    werase(score_win);
    werase(mission_win);
}

void ScoreBoard::updateScoreWin() {
    wborder(score_win, '|', '|', '-', '-', '+', '+', '+', '+');

    wattron(score_win, A_DIM);
    mvwprintw(score_win, 1, 3, "Current Stage : %d", stage);
    mvwprintw(score_win, 3, 3, "Snake Head Position <%d, %d>", snake_pos_x, snake_pos_y);
    mvwprintw(score_win, 4, 3, "Current Snake Size [%d]", snake_size);

    mvwprintw(score_win,5, 3,"Score : %d", total_score);
    mvwprintw(score_win,6, 3,"Gate_Count : %d", gate_score);
    mvwprintw(score_win,7, 3,"Growth_Count : %d", growth_score);
    mvwprintw(score_win,8, 3,"Poison_Count : %d", poison_score);
    mvwprintw(score_win,9, 3,"Time : %d min %d sec", (int)time/60, (int)time%60);
    wattroff(score_win, A_DIM);

    wrefresh(score_win);
}

void ScoreBoard::calcTotal_Score() {
    total_score =
            growth_score*100 +
            gate_score*200 -
            poison_score*100 +
            prev_score +
            (int)time;
}

void ScoreBoard::setSnakePos(int x, int y) {
    snake_pos_x = x;
    snake_pos_y = y;
}

void ScoreBoard::setSnakeSize(int size) {
    snake_size = size;
}

void ScoreBoard::addGateScore(int amount) {
    gate_score += amount;
}

void ScoreBoard::addGrowthScore(int amount) {
    growth_score += amount;
}

void ScoreBoard::addPoisonScore(int amount) {
    poison_score += amount;
}

void ScoreBoard::updateTime() {
    curr_time = chrono::steady_clock::now();
    time = chrono::duration_cast<chrono::seconds>(curr_time - start_time).count();
}

void ScoreBoard::updateMissionWin() {
    wborder(mission_win, '|', '|', '-', '-', '+', '+', '+', '+');

    wattron(mission_win, A_DIM);

    wattron(mission_win, A_ITALIC);
    mvwprintw(mission_win, 1, 3, "               <Mission list>");
    wattroff(mission_win, A_ITALIC);

    switch (stage) {
        case 1:
            printStage1();
            break;
        case 2:
            printStage2();
            break;
        case 3:
            printStage3();
            break;
        case 4:
            printStage4();
            break;
        default:
            break;
    }

    wattroff(mission_win, A_DIM);

    wrefresh(mission_win);
}

void ScoreBoard::printStage1() {
    mvwprintw(mission_win, 2, 3, "1. Obtain 3 Growth item            ( %c )", stage1_mission1);
    mvwprintw(mission_win, 3, 3, "2. Avoid collision 30 seconds      ( %c )", stage1_mission2);
    mvwprintw(mission_win, 4, 3, "3. Use Gate more than Once         ( %c )", stage1_mission3);
}

void ScoreBoard::printStage2() {
    mvwprintw(mission_win, 2, 3, "1. Obtain 7 Growth item            ( %c )", stage2_mission1);
    mvwprintw(mission_win, 3, 3, "2. Obtain 5 Poison item            ( %c )", stage2_mission2);
    mvwprintw(mission_win, 4, 3, "3. Use Gates more than Twice       ( %c )", stage2_mission3);
}

void ScoreBoard::printStage3() {
    mvwprintw(mission_win, 3, 3, "2. Avoid collision 50 seconds      ( %c )", stage1_mission2);
    mvwprintw(mission_win, 3, 3, "2. Obtain 5 Poison item            ( %c )", stage3_mission2);
    mvwprintw(mission_win, 4, 3, "3. Use Gates more than Twice       ( %c )", stage3_mission3);
}

void ScoreBoard::printStage4() {
    mvwprintw(mission_win, 2, 3, "1. Obtain 7 Growth item            ( %c )", stage3_mission1);
    mvwprintw(mission_win, 3, 3, "2. Obtain 5 Poison item            ( %c )", stage3_mission2);
    mvwprintw(mission_win, 4, 3, "3. Use Gates more than Twice       ( %c )", stage3_mission3);
}

void ScoreBoard::checkMissionCondition() {
    switch (stage) {
        case 1:
            if (growth_score >= 3)
                stage1_mission1 = 'O';
            if (time >= 30)
                stage1_mission2 = 'O';
            if (gate_score >= 1)
                stage1_mission3 = 'O';

            if(isMissionComplete(stage1_mission1, stage1_mission2, stage1_mission3))
            {
                stage = 2;
                clearScore();
            }
            break;
        case 2:
            if (growth_score >= 7)
                stage2_mission1 = 'O';
            if (poison_score >= 30)
                stage2_mission2 = 'O';
            if (gate_score >= 2)
                stage2_mission3 = 'O';

            if(isMissionComplete(stage2_mission1, stage2_mission2, stage2_mission3))
            {
                stage = 3;
                clearScore();
            }
            break;
        case 3:
            if (growth_score >= 7)
                stage2_mission1 = 'O';
            if (poison_score >= 30)
                stage2_mission2 = 'O';
            if (gate_score >= 2)
                stage2_mission3 = 'O';

            if(isMissionComplete(stage3_mission1, stage3_mission2, stage3_mission3))
            {
                stage = 4;
                clearScore();
            }
            break;
        case 4:
            if (growth_score >= 7)
                stage2_mission1 = 'O';
            if (poison_score >= 30)
                stage2_mission2 = 'O';
            if (gate_score >= 2)
                stage2_mission3 = 'O';

            if(isMissionComplete(stage4_mission1, stage4_mission2, stage4_mission3))
            {
                stage = 0;
                clearScore();
            }
            break;
    }
}
bool ScoreBoard::isMissionComplete(char& m1, char& m2, char& m3)
{
    return (m1 == 'O') && (m2 == 'O') && (m3 == 'O');
}

void ScoreBoard::clearScore() {
    gate_score = 0;
    growth_score = 0;
    poison_score = 0;
    start_time = chrono::steady_clock::now();
    time = 0;
    prev_score += total_score;
}

#endif //SNAKE_SCOREHANDLER_H
