#ifndef LIVING_FRACTIONS_H
#define LIVING_FRACTIONS_H

#include "config_window_base.h"
#include "utility.h"

enum Format {
    BLANK = 0,
    FRACTION,
    DECIMAL,
    PERCENT,
    ANGLE
};

struct LevelElement {
    Format fraction1 = BLANK, fraction2 = BLANK, fraction3 = BLANK;
    Format goal1rep = BLANK, goal2rep = BLANK, goal3rep = BLANK;
    int goal1 = 0, goal2 = 0, goal3 = 0;
};

class LivingFractions : public ConfigWindowBase
{
    Q_OBJECT
public:
    explicit LivingFractions(QWidget *parent = 0);
    void ReadXmlFileImp(QString filename);

signals:

public slots:

private:
    std::vector<LevelElement> levels;
};

#endif // LIVING_FRACTIONS_H
