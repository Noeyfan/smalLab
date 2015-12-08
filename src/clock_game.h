#ifndef CLOCKGAME_H
#define CLOCKGAME_H

#include "config_window_base.h"
#include "mlist.h"

struct _CG_LevelElement{
    std::tuple<int, int, int> start_time;
    std::tuple<int, int, int> end_time;
    std::pair<int, int> duration;
};

class ClockGame : public ConfigWindowBase
{
    Q_OBJECT
public:
    ClockGame(QWidget *parent);
    ~ClockGame() = default;

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    QString HelpImp();

private:
    std::vector<_CG_LevelElement> levels;
    QStringList am_pm;

    MList* list_view;
    QLineEdit* start_hour, *start_minute, *end_hour, *end_minute, *duration_hour, *duration_minute;
    QComboBox* start_am_pm, *end_am_pm;

signals:

public slots:
    bool CheckEmpty();

    void add_level() {
        levels.push_back({std::make_tuple<int,int,int>(0,0,0),
                          std::make_tuple<int,int,int>(0,0,0),
                          std::make_pair(0,0)});
    }

    void delete_level(int idx) {
        if (levels.empty()) return;
        qDebug() << "deleted" << idx <<"\n";
        levels.erase(levels.begin() + idx);
    }

    void SetVal() {
        if (levels.empty()) return;
        int idx = list_view->currentIndex();
        levels[idx].start_time=std::make_tuple(start_hour->text().toInt(),
                                                 start_minute->text().toInt(),
                                                 start_am_pm->currentIndex());
        levels[idx].end_time = std::make_tuple(end_hour->text().toInt(),
                                               end_minute->text().toInt(),
                                               end_am_pm->currentIndex());
        levels[idx].duration = std::make_pair(duration_hour->text().toInt(),
                                              duration_minute->text().toInt());
    }

    void Update(QModelIndex qmi) {
        if (levels.empty()) return;
        int idx = qmi.row();
        int a = 0, b = 0, c = 0;
        std::tie(a, b, c) = levels[idx].start_time;
        start_hour->setText(QString::number(a));
        start_minute->setText(QString::number(b));
        start_am_pm->setCurrentIndex(c);
        a = 0, b = 0, c = 0;
        std::tie(a, b, c) = levels[idx].end_time;
        end_hour->setText(QString::number(a));
        end_minute->setText(QString::number(b));
        end_am_pm->setCurrentIndex(c);

        a = 0, b = 0;
        std::tie(a, b) = levels[idx].duration;
        duration_hour->setText(QString::number(a));
        duration_minute->setText(QString::number(b));
    }
};

#endif // CLOCKGAME_H
