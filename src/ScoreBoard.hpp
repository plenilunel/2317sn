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
    int time{};
    void updateScoreWin();
    void calcTotal_Score();
public:
    void awake(int h, int w, int starty, int startx);

    void update();

    void onDisable();

    void clear();
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

    wattron(score_win, A_BLINK);
    mvwprintw(score_win, 1, 3, "Snake Head Position <%d, %d>", snake_pos_x, snake_pos_y);
    wattroff(score_win, A_BLINK);

    mvwprintw(score_win,2, 3,"Score : %d", total_score);

    mvwprintw(score_win,3, 3,"Gate_Count : %d", gate_score);
    mvwprintw(score_win,4, 3,"Growth_Count : %d", growth_score);
    mvwprintw(score_win,5, 3,"Poison_Count : %d", poison_score);
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

#endif //SNAKE_SCOREHANDLER_H
