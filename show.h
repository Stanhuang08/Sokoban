#ifndef SHOW_H
#define SHOW_H

#include "game.h"
#include <QGraphicsPixmapItem>

class showw : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    showw(game *, int);
    //void move();
    int x, y;

public slots:


private:
    game *g;
    int type; //-1 = player, 0~n = boxes

public slots:
    void update();
};

#endif // SHOW_H
