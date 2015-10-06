#include "mlist.h"

MList::MList(QWidget *parent) : QListView(parent)
{
    QLabel *list_view_label = new QLabel("levels", parent);
    this->resize(100,200);
    this->move(50, 150);
    list_view_label->move(50, 120);

    add = new QPushButton("+", parent);
    add->resize(add->width()/2, add->height());
    add->move(50, 350);

    rid = new QPushButton("-", parent);
    rid->resize(rid->width()/2, rid->height());
    rid->move(100, 350);

    model = new QStringListModel(strlist, NULL);
    this->setModel(model);

    connect(add, SIGNAL(pressed()), this, SLOT(add_levels()));
    connect(rid, SIGNAL(pressed()), this, SLOT(remove_levels()));
}

