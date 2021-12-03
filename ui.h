#ifndef UI_H
#define UI_H

// #include "game.h"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <vector>

using namespace std;

class game;
class background;
class showw;

class ui : public QGraphicsView
{
    Q_OBJECT
public:
    ui(game *);

private:
    background* bg;
    vector<showw*> s;
    game* g;
    QGraphicsScene* gameScene;
    QPushButton* restart;
    QPushButton* back;
    QPushButton* toMenu;
    QGraphicsTextItem* step;
    QGraphicsTextItem* score;
    QGraphicsTextItem* level;
    void keyPressEvent(QKeyEvent *);

    QGraphicsScene* menu;
    QPushButton *level1, *level2, *level3;
    QGraphicsTextItem* sokoban;
    QGraphicsTextItem* name;
    QGraphicsTextItem* best_1;
    QGraphicsTextItem* best_2;
    QGraphicsTextItem* best_3;

    void create_show();

    QGraphicsScene* prize;
    QGraphicsPixmapItem* prize_1;
    QPushButton* prize_to_menu;

signals:

public slots:
    //when playing
    void restart_clicked();
    void back_clicked();
    void toMenu_clicked();
    void update();
    //menu
    void level1_clicked();
    void level2_clicked();
    void level3_clicked();
    //win a level
    void ask_if_next(); //for level 1, 2
    void change_to_prize(); //for level 3

    void prize_to_menu_clicked();
};

#endif // UI_H
