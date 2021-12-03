#include "show.h"

#define width 100
#define length 100

showw::showw(game *g, int type) : g(g), type(type) {
    if (type == -1) setPixmap(QPixmap(":/images/fatpig.jpg").scaled(width, length));
    update();
}

void showw::update() {
    if (type == -1) {
        x = g -> player.second;
        y = g -> player.first;
        setPos(30 + x*width, 30 + y*length);
    } else {
        x = g -> boxes[type].second;
        y = g -> boxes[type].first;
        setPos(30 + x*width, 30 + y*length);
        if (g -> boxes_pos[type] == true) {  //boxes on the tagets
            setPixmap(QPixmap(":/images/box2.jpg").scaled(width, length));
        } else setPixmap(QPixmap(":/images/box1.jpg").scaled(width, length));
    }
}




