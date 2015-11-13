#ifndef PREFIX_POGODA_H
#define PREFIX_POGODA_H

#include "config_window_base.h"
#include "utility.h"

namespace Ui {
class PrefixPogoda;
}

class PrefixPogoda : public ConfigWindowBase
{
    Q_OBJECT

public:
    explicit PrefixPogoda(QWidget *parent = 0);
    ~PrefixPogoda();

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();

private:
    Ui::PrefixPogoda *ui;
};

#endif // PREFIX_POGODA_H
