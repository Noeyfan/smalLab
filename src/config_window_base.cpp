#include "config_window_base.h"

ConfigWindowBase::ConfigWindowBase(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(500, 500);
    open_button = new QPushButton("open file", this);

    // File Dialog
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(ReadXmlFile()));
}

void ConfigWindowBase::get_xml_file_name() {
    xml_file_name = QFileDialog::
            getOpenFileName(this,tr("Open xml File"),
                            QStandardPaths::locate(
                                QStandardPaths::DesktopLocation,
                                QString(),
                                QStandardPaths::LocateDirectory),
                            tr("xml Files (*.xml)"));
    qDebug("File opened: " + xml_file_name.toLatin1());
}

void ConfigWindowBase::ReadXmlFile() {
    ReadXmlFileImp(xml_file_name);
}
