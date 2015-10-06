#ifndef CUPCAKE_WAR_H
#define CUPCAKE_WAR_H

#include "config_window_base.h"
#include "utility.h"
#include "mlist.h"

class CupcakeWar : public ConfigWindowBase
{
    Q_OBJECT
public:
    explicit CupcakeWar(QWidget *parent = 0);

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);

private:
    // data
    std::vector<QString> nutritions = {"Vitamin A", "Vitamin B", "Vitamin C", "Vitamin D", "Vitamin E"};
    std::vector<std::vector<std::pair<bool, int>>> levels;

    //ui
    std::vector<std::pair<QCheckBox*, QLineEdit*>> selection;
    MList* list_view;

signals:

public slots:
    bool CheckEmpty();

    void add_level() {
        levels.push_back(std::vector<std::pair<bool, int>>(nutritions.size(), {false, 0}));
    }

private slots:
    void Update(QModelIndex qmi) {
        int idx = qmi.row();
        for (int i = 0; i < nutritions.size(); ++i) {
            //qDebug() << "idx is: " << idx;
            selection[i].first->setChecked(levels[idx][i].first);
            int val = levels[idx][i].second;
            qDebug() << "value is: " << val;
            selection[i].second->setText(QString::number(val));
        }
    }

    void SetVal() {
        if (levels.empty()) return;
        int idx = list_view->currentIndex();
        qDebug() << "SetVal() for idx:" << idx;
        for (int i = 0; i < nutritions.size(); ++i) {
            int num =  selection[i].second->text().toInt();
            bool checked = selection[i].first->isChecked();
            levels[idx][i] = std::make_pair(checked, num);
        }
    }
};

#endif // CUPCAKE_WAR_H
