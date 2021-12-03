#include "game.h"
#include <QDebug>

pair<int, int> operator+(const pair<int, int>& a, const pair<int, int>& b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

game::game() {
    best_scores = vector<int>(3, 0);
}

void game::init(int i) {
    level = i;
    if (i == 1) set_Level1();
    else if (i == 2) set_Level2();
    else if (i == 3) set_Level3();
}

void game::update(){
    score = 0;
    for(int i = 0; i < boxes.size(); ++i) {
        bool flag = false;
        for (const auto& t : targets) {
            if (boxes[i] == t) {
                score += 1;
                flag = true;
            }
        }
        boxes_pos[i] = flag;
    }
    if (score == boxes.size()) {
        emit move_signal();
        win();
    }
}

void game::win() {
    if (best_scores[level-1] == 0 || best_scores[level-1] > steps) best_scores[level-1] = steps;
    if (level < 3) {
        emit next_level();
    } else {
        emit get_prize();
    }
}

void game::reset() {
    steps = 0;
    while(!player_path.empty()) player_path.pop();
    while(!boxes_path.empty()) boxes_path.pop();
    while(!boxes_pos_path.empty()) boxes_pos_path.pop();
    boxes.clear();
    targets.clear();
}

void game::set_Level1() {
    reset();
    boxes.push_back(make_pair(2, 2));
    boxes.push_back(make_pair(2, 3));
    boxes.push_back(make_pair(2, 4));
    boxes_pos = vector<bool> (boxes.size(), false);

    targets.push_back(make_pair(1, 3));
    targets.push_back(make_pair(1, 4));
    targets.push_back(make_pair(2, 3));

    map.matrix = {{9, 0, 0, 0, 0, 0},
                  {9, 0, 1, 1, 1, 0},
                  {0, 0, 1, 1, 1, 0},
                  {0, 1, 1, 1, 1, 0},
                  {0, 1, 1, 1, 1, 0},
                  {0, 0, 0, 0, 0, 0}};
    player = make_pair(1, 2);

    update();
    //qDebug("set lwvel1");
    emit move_signal();
}

void game::set_Level2() {
    reset();
    boxes.push_back(make_pair(3, 3));
    boxes.push_back(make_pair(4, 2));
    boxes.push_back(make_pair(4, 3));
    boxes_pos = vector<bool> (boxes.size(), false);

    targets.push_back(make_pair(2, 2));
    targets.push_back(make_pair(3, 1));
    targets.push_back(make_pair(3, 2));

    map.matrix = {{0, 0, 0, 0, 9, 9},
                  {0, 1, 1, 0, 0, 9},
                  {0, 1, 1, 1, 0, 9},
                  {0, 1, 1, 1, 0, 0},
                  {0, 1, 1, 1, 1, 0},
                  {0, 1, 1, 1, 1, 0},
                  {0, 0, 0, 0, 0, 0}};
    player = make_pair(2, 1);

    update();

    emit move_signal();
}

void game::set_Level3() {
    reset();
    boxes.push_back(make_pair(3, 2));
    boxes.push_back(make_pair(3, 3));
    boxes.push_back(make_pair(3, 4));

    boxes_pos = vector<bool> (boxes.size(), false);

    targets.push_back(make_pair(2, 4));
    targets.push_back(make_pair(4, 5));
    targets.push_back(make_pair(5, 3));

    map.matrix = {{9, 9, 0, 0, 0, 0, 9, 9},
                  {9, 9, 0, 1, 1, 0, 0, 0},
                  {0, 0, 0, 1, 1, 1, 1, 0},
                  {0, 1, 1, 1, 1, 1, 1, 0},
                  {0, 1, 1, 1, 0, 1, 1, 0},
                  {0, 0, 0, 1, 1, 1, 0, 0},
                  {9, 9, 0, 0, 0, 0, 0, 9}};
    player = make_pair(3, 1);

    update();

    emit move_signal();
}

void game::player_move(int d) {
    vector<pair<int, int>> four_dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    auto next = player + four_dirs[d];
    bool is_next_box = false;
    pair<int, int>* next_box = nullptr;
    for(auto& b : boxes)
        if (b == next) {
            is_next_box = true;
            next_box = &b;
            break;
        }
    if (is_next_box) {
        auto next_two = next + four_dirs[d];
        is_next_box = false;
        for(const auto& b : boxes) if (b == next_two) is_next_box = true;
        if (!is_next_box && map[next_two] == 1) { //determine whether next_two is road
            player_path.push(player);//record
            boxes_path.push(boxes);
            boxes_pos_path.push(boxes_pos);
            ++steps;

            *next_box = next_two;
            player = next;
            update();

            emit move_signal();
        }
    } else {
        if(map[next] == 1) {
            player_path.push(player);//record
            boxes_path.push(boxes);
            boxes_pos_path.push(boxes_pos);
            ++steps;

            player = next;
            emit move_signal();
        }
    }
}

void game::player_back() {
    if (steps) {
        --steps;
        player = player_path.top();
        player_path.pop();
        boxes = boxes_path.top();
        boxes_path.pop();
        boxes_pos = boxes_pos_path.top();
        boxes_pos_path.pop();
        emit move_signal();
    }
}

