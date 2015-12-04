#include "mlist.h"

MList::MList(QWidget *parent, QString name) : QListView(parent), list_view_label(new QLabel(name, parent))
{
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

QItemSelectionModel* MList::selectionModel() {
    return QListView::selectionModel();
}

int MList::currentIndex() {
    return QListView::currentIndex().row();
}

void MList::setLines(int lines) {
    strlist.clear();
    for (int i = 0; i < lines; ++i) {
        strlist << QString::number(i);
    }
    num_of_lines = lines;
    model->setStringList(strlist);
}

void MList::clear() {
    strlist.clear();
    model->setStringList(strlist);
    num_of_lines = 0;
}

void MList::add_levels() {
    strlist << QString::number(num_of_lines++);
    model->setStringList(strlist);
    emit level_added();
}

void MList::remove_levels() {
    int idx = currentIndex();
    strlist.removeAt(idx);
    this->setLines(--num_of_lines);
    emit level_deleted(idx);
}

