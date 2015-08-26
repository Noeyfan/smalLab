#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include "utility.h"
#include "living_fractions.h"

class InitWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit InitWindow(QWidget *parent = 0);

signals:

public slots:

private slots:
    void set_selected_game(int idx) {
        selected_game = idx;
        qDebug("selected: %d" , idx);
    }

    void EnterSelectedConfig() {
        switch (selected_game) {
            case LIVING_FRACTIONS: {
                ConfigWindowBase* living_fractions_config_window = new LivingFractions(this);
                living_fractions_config_window->show();
                break;
            }
            default: {
                QMessageBox::warning(this, "Message", game_list->itemText(selected_game),
                                     QMessageBox::Ok);
            }
        }
    }

private:
    QPushButton* open_button;
    QPushButton* close_button;
    QComboBox* game_list;
    int selected_game = 0;
};

#endif // INIT_WINDOW_H
