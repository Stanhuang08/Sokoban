#include "ui.h"
#include "background.h"
#include "show.h"

#include <QMessageBox>

ui::ui(game *ptr) : g(ptr)
{
    //game
    gameScene = new QGraphicsScene();
    gameScene -> setSceneRect(0, 0, 1200, 800);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 800);

    bg = new background(g);
    gameScene -> addWidget(bg);

    restart = new QPushButton("Restart");
    gameScene -> addWidget(restart);
    restart -> connect(restart, SIGNAL(clicked()), this, SLOT(restart_clicked()));
    restart -> setGeometry(1000, 100, 100, 100);
    restart -> setFocusPolicy(Qt::NoFocus);

    back = new QPushButton("Back");
    gameScene -> addWidget(back);
    back -> connect(back, SIGNAL(clicked()), this, SLOT(back_clicked()));
    back -> setGeometry(1000, 250, 100, 100);
    back -> setFocusPolicy(Qt::NoFocus);

    toMenu = new QPushButton("Back to Menu");
    gameScene -> addWidget(toMenu);
    connect(toMenu, SIGNAL(clicked()), this, SLOT(toMenu_clicked()));
    toMenu -> setGeometry(1000, 600, 100, 50);
    toMenu -> setFocusPolicy(Qt::NoFocus);

    setFocus();
    setFocusPolicy(Qt::StrongFocus);

    step = new QGraphicsTextItem();
    step -> setPos(1000, 400);
    step -> setScale(2);
    step -> setDefaultTextColor(Qt::white);
    gameScene -> addItem(step);
    score = new QGraphicsTextItem();
    score -> setPos(1000, 500);
    score -> setScale(2);
    score -> setDefaultTextColor(Qt::white);
    gameScene -> addItem(score);

    level = new QGraphicsTextItem();
    level -> setPos(980, 670);
    level -> setScale(3);
    level -> setDefaultTextColor(QColor(219, 112, 147));
    gameScene -> addItem(level);

    connect(g, SIGNAL(move_signal()), this, SLOT(update()));
    update();

    connect(g, SIGNAL(next_level()), this, SLOT(ask_if_next()));

    //menu
    menu = new QGraphicsScene();
    menu -> setSceneRect(0, 0, 1200, 800);
    setStyleSheet("background-color:black");
    setScene(menu);

    level1 = new QPushButton("level1");
    level2 = new QPushButton("level2");
    level3 = new QPushButton("level3");
    level1 -> setGeometry(400, 400, 100, 50);
    level2 -> setGeometry(400, 500, 100, 50);
    level3 -> setGeometry(400, 600, 100, 50);
    connect(level1, SIGNAL(clicked()), this, SLOT(level1_clicked()));
    connect(level2, SIGNAL(clicked()), this, SLOT(level2_clicked()));
    connect(level3, SIGNAL(clicked()), this, SLOT(level3_clicked()));
    menu -> addWidget(level1);
    menu -> addWidget(level2);
    menu -> addWidget(level3);

    sokoban = new QGraphicsTextItem();
    sokoban -> setPos(350, 130);
    sokoban -> setScale(6);
    sokoban -> setDefaultTextColor(Qt::white);
    menu -> addItem(sokoban);
    sokoban -> setPlainText("SOKOBAN");

    name - new QGraphicsTextItem();
    name -> setPos(1000, 700);
    name -> setScale(1);
    name -> setDefaultTextColor(Qt::white);
    menu -> addItem(name);
    name -> setPlainText("H24061333");

    best_1 = new QGraphicsTextItem();
    best_2 = new QGraphicsTextItem();
    best_3 = new QGraphicsTextItem();
    best_1 -> setPos(500, 400);
    best_2 -> setPos(500, 500);
    best_3 -> setPos(500, 600);
    best_1 -> setScale(2);
    best_2 -> setScale(2);
    best_3 -> setScale(2);
    best_1 -> setDefaultTextColor(Qt::white);
    best_2 -> setDefaultTextColor(Qt::white);
    best_3 -> setDefaultTextColor(Qt::white);
    menu -> addItem(best_1);
    menu -> addItem(best_2);
    menu -> addItem(best_3);


    //prize
    prize = new QGraphicsScene();
    prize -> setSceneRect(0, 0, 1200, 800);
    /*
    prize_1 = new QGraphicsPixmapItem(QPixmap(":/images/prize.png").scaled(415, 615));
    prize_1 -> setPos(350, 50);
    prize -> addItem(prize_1);
*/
    setStyleSheet("background-color:black");

    prize_to_menu = new QPushButton("Back to Menu");
    prize -> addWidget(prize_to_menu);
    connect(prize_to_menu, SIGNAL(clicked()), this, SLOT(prize_to_menu_clicked()));
    prize_to_menu -> setGeometry(1000, 600, 100, 50);
    prize_to_menu -> setFocusPolicy(Qt::NoFocus);

    connect(g, SIGNAL(get_prize()), this, SLOT(change_to_prize()));
}

void ui::prize_to_menu_clicked() {
    toMenu_clicked();
}

void ui::level1_clicked() {
    g -> init(1);
    create_show();
    setScene(gameScene);
}
void ui::level2_clicked() {
    g -> init(2);
    create_show();
    setScene(gameScene);
}
void ui::level3_clicked() {
    g -> init(3);
    create_show();
    setScene(gameScene);
}

void ui::create_show() {
    for (auto& ptr : s) delete ptr;
    s.clear();
    for (int i = 0; i < g -> boxes.size(); ++i) {
        auto temp = new showw(g, i);
        connect(g, SIGNAL(move_signal()), temp, SLOT(update()));
        s.push_back(temp);
    }
    auto temp = new showw(g, -1);
    connect(g, SIGNAL(move_signal()), temp, SLOT(update()));
    s.push_back(temp);
    for (auto& a : s) {
        gameScene -> addItem(a);
    }
}

void ui::restart_clicked() {
    QMessageBox msg;
    msg.setText("Are You Sure???");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setGeometry(600, 400, 400, 300);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
        g -> init(g -> level);
}

void ui::ask_if_next() {
    QMessageBox msg;
    msg.setText("Next Level ???");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setGeometry(600, 400, 400, 300);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
        g -> init(g -> level + 1);
    else toMenu_clicked();
}

void ui::change_to_prize() {
    QMessageBox msg;
    msg.setText("Congrates! Press 'ok' to see your exlusive prize~~~~");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setGeometry(600, 400, 400, 300);

    if (msg.exec() == QMessageBox::Ok) {
        setScene(prize);
    }
}

void ui::back_clicked() {
    g -> player_back();
}

void ui::toMenu_clicked() {
    setScene(menu);
    best_1 -> setPlainText("Record: " + QString::number(g -> best_scores[0]));
    best_2 -> setPlainText("Record: " + QString::number(g -> best_scores[1]));
    best_3 -> setPlainText("Record: " + QString::number(g -> best_scores[2]));
}

void ui::keyPressEvent(QKeyEvent *event) {
    if (this -> scene() == gameScene) {
        if (event -> key() == Qt::Key_Right) g -> player_move(1);
        else if (event -> key() == Qt::Key_Down) g -> player_move(0);
        else if (event -> key() == Qt::Key_Left) g -> player_move(3);
        else if (event -> key() == Qt::Key_Up) g -> player_move(2);
    }
}

void ui::update() {
    step -> setPlainText("Steps:\n" + QString::number(g -> steps));
    score -> setPlainText("completed:\n" + QString::number(g -> score) + "/" + QString::number(g -> boxes.size()));
    level -> setPlainText("Level " + QString::number(g -> level));
}





