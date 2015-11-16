#include "prefix_pogoda.h"
#include "ui_prefix_pogoda.h"

PrefixPogoda::PrefixPogoda(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::PrefixPogoda),
    word_list(QStringList(), new QStringListModel(this))
{
    ui->setupUi(this);
    for(int i = 0; i < 3; ++i) {
        QStringList str;
        QStringListModel* model = new QStringListModel(this);
        affix_lists.emplace_back(str, model);
    }
    ui->prefix_list->setModel(affix_lists[0].second);
    ui->root_list->setModel(affix_lists[1].second);
    ui->suffix_list->setModel(affix_lists[2].second);
}

PrefixPogoda::~PrefixPogoda()
{
    delete ui;
}

void PrefixPogoda::ReadXmlFileImp(QString qs) {

}

void PrefixPogoda::WriteXmlFileImp(QString qs) {

}

bool PrefixPogoda::CheckEmpty() {

}

void PrefixPogoda::on_affix_add_pressed()
{
    auto ele = std::make_pair(ui->affix_input->text(), ui->affix_des->text());
    if(ele.first == "" || ele.second =="") return;
    switch (ui->affix_type->currentIndex()) {
    case 0:
        prefixs.push_back(ele);
        affix_add_helper(0, ele.first);
        break;
    case 1:
        roots.push_back(ele);
        affix_add_helper(1, ele.first);
        break;
    case 2:
        suffixs.push_back(ele);
        affix_add_helper(2, ele.first);
        break;
    default:
        break;
    }
}

void PrefixPogoda::on_affix_update_clicked()
{
}

void PrefixPogoda::affix_add_helper(int idx, QString s) {
    affix_lists[idx].first << s;
    affix_lists[idx].second->setStringList(affix_lists[idx].first);
}
