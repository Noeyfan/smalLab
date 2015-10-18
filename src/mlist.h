#ifndef MLIST_H
#define MLIST_H

#include "utility.h"

class MList : public QListView {
    QStringList strlist;
    QStringListModel* model;
    QPushButton* add;
    QPushButton* rid;
    QLabel* list_view_label;
    int num_of_lines = 0;

    Q_OBJECT
public:
    explicit MList(QWidget*, QString name = "levels");
    QItemSelectionModel* selectionModel();
    int currentIndex();
    void setLines(int lines);
    void clear();

signals:
    void level_added();
    void level_deleted(int);

public slots:
    void add_levels();
    void remove_levels();
};

#endif // MLIST_H



