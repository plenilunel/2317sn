//
// Created by Administrator on 6/17/2023.
//

#ifndef SNAKE_SCOREHANDLER_H
#define SNAKE_SCOREHANDLER_H

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
    double time{};
    void updateScoreWin();
    void calcTotal_Score();
public:
    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    void clear();

    void setSnakePos(int x, int y);
    void setSnakeSize(int size);
    void addGateScore(int amount = 1);
    void addGrowthScore(int amount = 1);
    void addPoisonScore(int amount = 1);
    void addTime();
};

void ScoreBoard::awake(int h, int w, int starty, int startx) {
    height = h;
    width = w;
    start_y = starty;
    start_x = startx;

    score_win = newwin(height/2 + height/3, width, start_y, start_x);
    mission_win = newwin(height/2, width, starty*4, start_x);

    wbkgd(score_win, COLOR_PAIR(10) | A_BOLD);
    wbkgd(mission_win, COLOR_PAIR(10) | A_BOLD);
}

void ScoreBoard::update() {
    calcTotal_Score();
    updateScoreWin();

    wrefresh(mission_win);
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

    mvwprintw(score_win, 1, 3, "Snake Head Position <%d, %d>", snake_pos_x, snake_pos_y);
    wattron(score_win, A_BLINK);
    mvwprintw(score_win, 2, 3, "Current Snake Size [%d]", snake_size);
    wattroff(score_win, A_BLINK);

    mvwprintw(score_win,3, 3,"Score : %d", total_score);

    mvwprintw(score_win,4, 3,"Gate_Count : %d", gate_score);
    mvwprintw(score_win,5, 3,"Growth_Count : %d", growth_score);
    mvwprintw(score_win,6, 3,"Poison_Count : %d", poison_score);
    mvwprintw(score_win,7, 3,"Time : %d min %d sec", (int)time/60, (int)time%60);
    wattroff(score_win, A_DIM);
    wrefresh(score_win);
}

void ScoreBoard::calcTotal_Score() {
    total_score =
            growth_score*100 +
            gate_score*200 -
            poison_score*100 +
            time;

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

void ScoreBoard::addTime() {
    time+=0.5;
}

#endif //SNAKE_SCOREHANDLER_H
