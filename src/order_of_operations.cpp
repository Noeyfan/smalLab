#include "order_of_operations.h"
#include "ui_order_of_operations.h"

OrderOfOperations::OrderOfOperations(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderOfOperations)
{
    ui->setupUi(this);
}

OrderOfOperations::~OrderOfOperations()
{
    delete ui;
}
