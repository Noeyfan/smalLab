#ifndef PREFIX_POGODA_H
#define PREFIX_POGODA_H

#include "config_window_base.h"
#include "utility.h"

namespace Ui {
class PrefixPogoda;
}

struct Words {
    int prefix_id, root_id, suffix_id;
    QString word, desc;

    Words(int p, int r, int s, QString w, QString d)
    : prefix_id(p), root_id(r), suffix_id(s), word(w), desc(d) { }
};

class PrefixPogoda : public ConfigWindowBase
{
    Q_OBJECT

public:
    explicit PrefixPogoda(QWidget *parent = 0);
    ~PrefixPogoda();

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();
    QString HelpImp();

private slots:
    void on_affix_add_pressed();

    void on_word_add_pressed();

    void on_word_update_pressed();

    void on_word_delete_pressed();

    void on_word_list_clicked(const QModelIndex &index);

    void on_prefix_list_clicked(const QModelIndex &index);

    void on_root_list_clicked(const QModelIndex &index);

    void on_suffix_list_clicked(const QModelIndex &index);

    void on_prefix_list_activated(const QModelIndex &index);

    void on_affix_delete_clicked();

private:
    void affix_add_helper(int, QString);
    QString removeSemi(QString);
    std::pair<int,int> get_pos(QString);
    bool checkDup(QString, std::vector<std::pair<QString, QString>>&);

    Ui::PrefixPogoda *ui;

    std::vector<std::pair<QString, QString>> prefixs;
    std::vector<std::pair<QString, QString>> roots;
    std::vector<std::pair<QString, QString>> suffixs;
    std::vector<Words> words;

    std::vector<std::pair<QStringList, QStringListModel*>> affix_lists;
    std::pair<QStringList, QStringListModel*> word_list;

    int delete_cur_type = -1, delete_cur_idx = -1;
};

#endif // PREFIX_POGODA_H
