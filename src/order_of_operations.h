#ifndef ORDER_OF_OPERATIONS_H
#define ORDER_OF_OPERATIONS_H

#include <QMainWindow>

namespace Ui {
class OrderOfOperations;
}

class OrderOfOperations : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderOfOperations(QWidget *parent = 0);
    ~OrderOfOperations();

private:
    Ui::OrderOfOperations *ui;
};

#endif // ORDER_OF_OPERATIONS_H
