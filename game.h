#ifndef GAME_H
#define GAME_H

#include "ui.h"
#include <QObject>
#include <QTimer>
#include <vector>
#include <stack>

using namespace std;

class twoD {
public:
    vector<vector<int>> matrix;
    int& operator[] (pair<int, int> p) {return matrix[p.first][p.second];}
    vector<int>& operator[](int first) {return matrix[first];}
};

class game : public QObject
{
    Q_OBJECT
    friend ui;
    friend background;
    friend showw;
public:
    game();
    void init(int); //choose level
    const pair<int, int>& get_player_pos() {return player;}
private:
    twoD map; //wall=0, road=1
    vector<pair<int, int>> boxes;
    vector<bool> boxes_pos; //whether boxes on the targets
    vector<pair<int, int>> targets;
    pair<int, int> player;
    stack<pair<int, int>> player_path;
    stack<vector<pair<int, int>>> boxes_path;
    stack<vector<bool>> boxes_pos_path;

    unsigned int score;
    int steps;
    int level=1;
    vector<int> best_scores;

    void update(); //update score
    void reset();
    void set_Level1();
    void set_Level2();
    void set_Level3();
    void win();
    void player_move(int); //right = 0, down = 1, left = 2, up = 3
    void player_back();


signals :
    void move_signal();
    void next_level();
    void get_prize();
};

#endif // GAME_H
