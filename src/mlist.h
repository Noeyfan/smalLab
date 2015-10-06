#ifndef MLIST_H
#define MLIST_H

#include "utility.h"

class MList : public QListView{
    QStringList strlist;
    QStringListModel* model;
    QPushButton* add;
    QPushButton* rid;
    int i = 0;

    Q_OBJECT
public:
    explicit MList(QWidget *parent);

    auto selectionModel() -> decltype(QListView::selectionModel()){
        return QListView::selectionModel();
    }

    int currentIndex() {
        return QListView::currentIndex().row();
    }

    void setLines(int lines) {
        for (int i = 0; i < lines; ++i) {
            strlist << QString::number(i);
        }
        model->setStringList(strlist);
    }

    void clear() {
        strlist.clear();
        model->setStringList(strlist);
        i = 0;
    }

signals:
    void level_added();

public slots:
    void add_levels() {
        strlist << QString::number(i++);
        model->setStringList(strlist);
        emit level_added();
    }

    void remove_levels() {
    }

};

#endif // MLIST_H



