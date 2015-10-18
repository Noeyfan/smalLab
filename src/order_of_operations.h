#ifndef ORDER_OF_OPERATIONS_H
#define ORDER_OF_OPERATIONS_H

#include "config_window_base.h"
#include "mlist.h"
#include "utility.h"

namespace Ui {
class OrderOfOperations;
}

struct _OO_Element {
    int stg1_difficulty = 1;
    int stg1_num_of_op = 1;

    std::vector<QString> stg2_ops;

    _OO_Element() = default;
};

class OrderOfOperations : public ConfigWindowBase
{
    Q_OBJECT

public:
    explicit OrderOfOperations(QWidget *parent = 0);
    ~OrderOfOperations();
    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();
    QString HelpImp();

private:
    Ui::OrderOfOperations *ui;

    //data
    _OO_Element data;
    QStringList strlist;
    QStringListModel* model;


private slots:
    void on_add_clicked();
    void on_remove_clicked();
    void on_difficulty_activated(int index);
    void on_opnum_editingFinished();
};

#endif // ORDER_OF_OPERATIONS_H
