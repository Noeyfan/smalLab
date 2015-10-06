#include "init_window.h"

InitWindow::InitWindow(QWidget *parent) : QMainWindow(parent)
{
    // init
    this->setFixedSize(400, 300);

    // buttons
    open_button = new QPushButton("open", this);
    open_button->move(300, 220);
    close_button = new QPushButton("close", this);
    close_button->move(300, 250);

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
    game_list->addItem("Cupcake War");

    // connect
    connect(game_list, SIGNAL (currentIndexChanged(int)), this, SLOT (set_selected_game(int)));
    connect(close_button, SIGNAL(clicked()), QApplication::instance(), SLOT (quit()));
    connect(open_button, SIGNAL(clicked()), this, SLOT (EnterSelectedConfig()));
}

void InitWindow::EnterSelectedConfig() {
    switch (selected_game) {
        case LIVING_FRACTIONS: {
            ConfigWindowBase* living_fractions_config_window = new LivingFractions(this);
            living_fractions_config_window->show();
            break;
        }
        case CUPCAKE_WAR: {
            ConfigWindowBase* cupcake_war = new CupcakeWar(this);
            cupcake_war->show();
            break;
        }
        default: {
            QMessageBox::warning(this, "Message", game_list->itemText(selected_game),
                                 QMessageBox::Ok);
        }
    }
}

void InitWindow::set_selected_game(int idx) {
    selected_game = idx;
    qDebug("selected: %d" , idx);
}
