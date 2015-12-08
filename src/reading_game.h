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

    void on_levels_activated(const QModelIndex &index);

    void on_levels_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void clear_inputs();

    Ui::ReadingGame *ui;
    std::pair<QStringList, QStringListModel*> level_list;
    std::vector<std::vector<std::pair<QString, QString>>> levels;
};

#endif // READING_GAME_H
