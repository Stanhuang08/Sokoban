#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "game.h"
#include <QWidget>
#include <QPainter>

class background : public QWidget
{
    Q_OBJECT
public:
    background(game *);

protected:
    void paintEvent(QPaintEvent *);

private:
    game *g;



};

#endif // BACKGROUND_H
