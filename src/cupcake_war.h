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
    QString HelpImp();

private:
    // data
    std::vector<QString> nutritions;
    std::vector<std::vector<std::pair<bool, float>>> levels;
    std::vector<int> other_attr_val;

    //ui
    std::vector<std::pair<QCheckBox*, QLineEdit*>> selection;
    std::vector<QLineEdit*> other_attr;
    QComboBox* grade;

signals:

public slots:
    bool CheckEmpty();

    void add_level() {
        levels.push_back(std::vector<std::pair<bool, float>>(nutritions.size(), {false, 0}));
    }

private slots:
    void Update(int idx) {
        for (int i = 0; i < nutritions.size(); ++i) {
            //qDebug() << "idx is: " << idx;
            selection[i].first->setChecked(levels[idx][i].first);
            float val = levels[idx][i].second;
            qDebug() << "value is: " << val;
            selection[i].second->setText(QString::number(val));
        }

        for(int i = 0; i < 4; ++i) {
            other_attr[i]->setText(QString::number(other_attr_val[i]));
        }
    }

    void SetVal() {
        if (levels.empty()) return;
        for (int i = 0; i < nutritions.size(); ++i) {
            float num =  selection[i].second->text().toFloat();
            bool checked = selection[i].first->isChecked();
            levels[0][i] = std::make_pair(checked, num);
        }

        for(int i = 0; i < 4; ++i) {
            other_attr_val[i] = other_attr[i]->text().toInt();
        }
    }
};

#endif // CUPCAKE_WAR_H
