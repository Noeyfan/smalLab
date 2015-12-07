#ifndef READING_GAME_H
#define READING_GAME_H

#include <QWidget>
#include "config_window_base.h"
#include "util.h"

namespace Ui {
class ReadingGame;
}

class ReadingGame : public ConfigWindowBase
{
    Q_OBJECT

public:
    explicit ReadingGame(QWidget *parent = 0);
    ~ReadingGame();

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();
    QString HelpImp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ReadingGame *ui;
    std::vector<std::vector<std::pair<QString, QString>>> levels;
};

#endif // READING_GAME_H
