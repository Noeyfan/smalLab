#ifndef LIVING_FRACTIONS_H
#define LIVING_FRACTIONS_H

#include "config_window_base.h"
#include "utility.h"

struct LevelElement {
    QString format1 = "", format2 = "", format3 = "",
    goal1rep = "", goal2rep = "", goal3rep = "";
    double goal1 = 0, goal2 = 0, goal3 = 0;

    void print() const {
        qDebug() << "format1: " << format1
                 << " format2: " << format2
                 << " format3: " << format3 << "\n";
        qDebug() << "goal1: " << goal1
                 << " goal2: " << goal2
                 << " goal3: " << goal3 << "\n";
        qDebug() << "goal1rep: " << goal1rep
                 << " goal2rep: " << goal2rep
                 << " goal3rep: " << goal3rep << "\n";
    }
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

private:
    int highest_denominator = 0;
    std::vector<LevelElement> levels;
};

#endif // LIVING_FRACTIONS_H
