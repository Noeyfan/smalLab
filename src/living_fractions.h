#ifndef LIVING_FRACTIONS_H
#define LIVING_FRACTIONS_H

#include "config_window_base.h"
#include "utility.h"

struct LevelElement {
    QString format1 = "", format2 = "", format3 = "",
    goal1rep = "", goal2rep = "", goal3rep = "";
    std::vector<double> goals;

    LevelElement() : goals(3,0) { }

    void print() const {
        qDebug() << "format1: " << format1
                 << " format2: " << format2
                 << " format3: " << format3 << "\n";
        qDebug() << "goal1rep: " << goal1rep
                 << " goal2rep: " << goal2rep
                 << " goal3rep: " << goal3rep << "\n";
    }
};

struct MTextField : public QLineEdit{
    Q_OBJECT
public:
    MTextField(QWidget* parent) : QLineEdit(parent) { }
public slots:
};

class LivingFractions : public ConfigWindowBase
{
    Q_OBJECT
public:
    explicit LivingFractions(QWidget *parent = 0);
    void ReadXmlFileImp(QString filename);
    void WriteXmlFileImp(QString filename);

signals:

public slots:

private slots:
    void add_levels() {
        strlist << QString::number(levels.size());
        levels.push_back(LevelElement());
        model->setStringList(strlist);
    }

    void remove_levels() {
        foreach (const QModelIndex &index, listview->selectionModel()->selectedIndexes()) {
            // TODO maybe add a member selected_idx;
            int idx = index.row();
            strlist.removeAt(idx);
            levels.erase(levels.begin() + idx);
            for (int i = idx; i < strlist.size(); i++) {
                strlist[i] = QString::number(i);
            }
        }
        model->setStringList(strlist);
        Reset();
    }

    void Update(QModelIndex idx) {
        Update(idx.row());
    }

    void Update(int idx) {
        for (int i = 0; i < 3; i++) {
            goals[i]->setText(QString::number(levels[idx].goals[i]));
        }
    }

    void SetValue() {
        // all value update should be here
        if (levels.empty() || listview->currentIndex().row() == -1) { return; }
        for (int i = 0; i < 3; i++) {
            levels[listview->currentIndex().row()].goals[i] = goals[i]->text().toDouble();
            qDebug() << goals[i]->text();
        }
    }

    void Reset() {
        for (int i = 0; i < 3; i++) {
            goals[i]->setText("");
        }
    }

    bool CheckEmpty() {
        if (levels.empty() || listview->currentIndex().row() == -1) {
            Reset();
            QMessageBox::warning(this, "Message", "Please add a level first",
                                 QMessageBox::Ok);
            return true;
        }
        return false;
    }

    void debug() {
        qDebug() << "triggered";
    }

private:
    int highest_denominator = 0;
    std::vector<LevelElement> levels;

    // ui
    QListView* listview;
    QStringList strlist;
    QPushButton* add;
    QPushButton* rid;
    QStringListModel* model;

    //QLineEdit
    std::vector<MTextField*> goals;
};

#endif // LIVING_FRACTIONS_H
