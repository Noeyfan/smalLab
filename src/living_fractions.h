#ifndef LIVING_FRACTIONS_H
#define LIVING_FRACTIONS_H

#include "config_window_base.h"
#include "utility.h"

class LivingFractions : public ConfigWindowBase
{
    Q_OBJECT
public:
    explicit LivingFractions(QWidget *parent = 0);
    void ReadXmlFileImp(QString filename);

signals:

public slots:
};

#endif // LIVING_FRACTIONS_H
