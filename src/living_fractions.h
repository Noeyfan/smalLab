#ifndef LIVING_FRACTIONS_H
#define LIVING_FRACTIONS_H

#include "config_window_base.h"
#include "utility.h"

struct LevelElement {
    //QString format1 = "", format2 = "", format3 = "",
    //goal1rep = "", goal2rep = "", goal3rep = "";
    std::vector<double> goals;
    std::vector<QString> formats;
    std::vector<QString> goalreps;

    LevelElement() : goals(3,0), formats(3, "blank"), goalreps(3, "blank") { }

    void print() const {
        qDebug() << "format1: " << formats[0]
                 << " format2: " << formats[1]
                 << " format3: " << formats[2] << "\n";
        qDebug() << "goal1rep: " << goalreps[0]
                 << " goal2rep: " << goalreps[1]
                 << " goal3rep: " << goalreps[2] << "\n";
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
            fractions[i]->setCurrentIndex(fractions[i]->findText(levels[idx].formats[i]));
            goalreps[i]->setCurrentIndex(levels[idx].goals[i] != 0 ?
                        goalreps[i]->findText(levels[idx].goalreps[i]) : 0 );
        }
    }

    void SetValue() {
        SetValueGoal();
        // SetValueFormat(); BUG HERE TODO
        // SetValueRep();
    }

    void SetValueGoal() {
        if (levels.empty() || listview->currentIndex().row() == -1) { return; }
        int row = listview->currentIndex().row();
        for (int i = 0; i < 3; i++) {
            levels[row].goals[i] = goals[i]->text().toDouble();
        }
    }

    void SetValueFormat() {
        if (levels.empty() || listview->currentIndex().row() == -1) { return; }
        int row = listview->currentIndex().row();
        for (int i = 0; i < 3; i++) {
            levels[row].formats[i] = fractions[i]->currentText();
        }
    }

    void SetValueRep() {
        if (levels.empty() || listview->currentIndex().row() == -1) { return; }
        int row = listview->currentIndex().row();
        for (int i = 0; i < 3; i++) {
            if (levels[row].goals[i] == 0) {
                continue; // omit empty elements
            }
            levels[row].goalreps[i] = goalreps[i]->currentText();
        }
    }

    void SetHD() {
        highest_denominator = highest_denominator_txt->text().toInt();
    }

    void Reset() {
        for (int i = 0; i < 3; i++) {
            goals[i]->setText("");
        }
    }

    bool CheckEmpty() {
        if (levels.empty() || listview->currentIndex().row() == -1) {
            Reset();
            QMessageBox::warning(this, "Message", "Please select or add a level first",
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
    std::vector<QComboBox*> fractions;
    std::vector<QComboBox*> goalreps;
    MTextField* highest_denominator_txt;
};

#endif // LIVING_FRACTIONS_H
