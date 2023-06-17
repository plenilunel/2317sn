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

    score_win = newwin(height/2, width, start_y, start_x);
    mission_win = newwin(height/2, width, start_y+(starty*2)/2, start_x);

    wbkgd(score_win, COLOR_PAIR(1) | A_BOLD);
    wbkgd(mission_win, COLOR_PAIR(2) | A_BOLD);
}

void ScoreBoard::update() {
    wrefresh(score_win);
    wrefresh(mission_win);
}

void ScoreBoard::onDisable() {

}

void ScoreBoard::clear() {
    werase(score_win);
    werase(mission_win);
}

#endif //SNAKE_SCOREHANDLER_H
