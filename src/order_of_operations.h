#ifndef ORDEROFOPERATIONS_H
#define ORDEROFOPERATIONS_H

#include "config_window_base.h"
#include "mlist.h"
#include "utility.h"

class OrderOfOperations : public ConfigWindowBase
{
    Q_OBJECT
public:
    OrderOfOperations(QWidget* parent);

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();
    QString HelpImp();

signals:

public slots:
};

#endif // ORDEROFOPERATIONS_H
