#include "config_window_base.h"

ConfigWindowBase::ConfigWindowBase(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(500, 500);
    open_button = new QPushButton("open file", this);

    // File Dialog
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
}
