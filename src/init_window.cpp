#include "init_window.h"

Init_Window::Init_Window(QWidget *parent) : QMainWindow(parent)
{
    // init
    this->setFixedSize(400, 300);

    // buttons
    open = new QPushButton("open", this);
    open->move(300, 220);
    close = new QPushButton("close", this);
    close->move(300, 250);

    // menu
    game_list = new QComboBox(this);
    game_list->move(100, 100);
    game_list->resize(200, 25);

    game_list->addItem("Clock Game");
    game_list->addItem("Living Fractions");
    game_list->addItem("Order Of Operations");
    game_list->addItem("Prefix Pagoda");
    game_list->addItem("Reading Game");
    game_list->addItem("Teaching Tool");

    // connect
    connect(game_list, SIGNAL (currentIndexChanged(int)), this, SLOT (setSelectedGame(int)));
    connect(close, SIGNAL(clicked()), QApplication::instance(), SLOT (quit()));
    connect(open, SIGNAL(clicked()), this, SLOT (enterSelectedConfig()));
}
