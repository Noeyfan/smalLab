#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include "utility.h"
#include "living_fractions.h"
#include "cupcake_war.h"

class InitWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit InitWindow(QWidget *parent = 0);

private slots:
    void set_selected_game(int idx);
    void EnterSelectedConfig();

private:
    QPushButton* open_button;
    QPushButton* close_button;
    QComboBox* game_list;
    int selected_game = 0;
};

#endif // INIT_WINDOW_H
