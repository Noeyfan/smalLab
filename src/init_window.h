#ifndef INIT_WINDOW_H
#define INIT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include "utility"

class Init_Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Init_Window(QWidget *parent = 0);

signals:

public slots:

private slots:
    void setSelectedGame(int idx) {
        selected_game = idx;
        qDebug("selected: %d" , idx);
    }

    void enterSelectedConfig() {
        QMessageBox::warning(this, "Message", game_list->itemText(selected_game), QMessageBox::Ok);
    }

private:
    QPushButton* open;
    QPushButton* close;
    QComboBox* game_list;
    int selected_game = 0;
};

#endif // INIT_WINDOW_H
