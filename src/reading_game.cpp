#include "reading_game.h"
#include "ui_reading_game.h"

ReadingGame::ReadingGame(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::ReadingGame)
{
    this->setFixedSize(1000, 450);
    ui->setupUi(this);
    open_button->move(300, 10);
    save_button->move(600, 10);
    help_button->move(450, 410);
}

ReadingGame::~ReadingGame()
{
    delete ui;
}

void ReadingGame::ReadXmlFileImp(QString) {

}

void ReadingGame::WriteXmlFileImp(QString) {

}

bool ReadingGame::CheckEmpty() {

}

QString ReadingGame::HelpImp() {

}

void ReadingGame::on_pushButton_clicked()
{
    // add level

}
