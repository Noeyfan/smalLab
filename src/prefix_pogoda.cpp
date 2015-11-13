#include "prefix_pogoda.h"
#include "ui_prefix_pogoda.h"

PrefixPogoda::PrefixPogoda(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::PrefixPogoda)
{
    ui->setupUi(this);
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


