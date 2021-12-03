#include "background.h"
#include <QDebug>

#define width 100
#define length 100

int real_x(int x) {return 30 + x * width;}
int real_y(int y) {return 30 + y * length;}

background::background(game *g) : g(g) {
    setGeometry(0, 0, 1200, 800);
    setStyleSheet("background-color:black");


}

void background::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    for (int i = 0; i < g -> map.matrix.size(); ++i)
        for (int j = 0; j < g -> map[i].size(); ++j)
            if (g -> map[i][j] == 0) {
                //draw wall;
                painter.drawPixmap(real_x(j), real_y(i), QPixmap(":/images/wall.jpg").scaled(width, length));
            } else if (g -> map[i][j] == 1) {
                //draw road
                painter.drawPixmap(real_x(j), real_y(i), QPixmap(":/images/road.jpg").scaled(width, length));
            }
    for (const auto& t : (g -> targets)) {
        painter.drawPixmap(real_x(t.second) + width/2 - width/8, real_y(t.first) + length/2 - length/8, QPixmap(":/images/target_white.jpg").scaled(width/4, length/4));
    }

}
