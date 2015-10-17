#include "config_window_base.h"

ConfigWindowBase::ConfigWindowBase(QWidget *parent) : QMainWindow(parent), validator(new QRegExpValidator(QRegExp("^[0-9]*(.)*[0-9]+$"),this))
{
    this->setFixedSize(700, 500);
    open_button = new QPushButton("open file", this);
    save_button = new QPushButton("save file", this);
    open_button->move(200, 0);
    save_button->move(400, 0);

    // File Dialog
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(set_file_open_mode()));
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(ReadXmlFile()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(set_file_save_mode()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(WriteXmlFile()));
}

void ConfigWindowBase::get_xml_file_name() {
    xml_file_name = mode ?
                QFileDialog::getOpenFileName(this,tr("Open xml File"),
                                             QStandardPaths::locate(
                                                 QStandardPaths::DesktopLocation,
                                                 QString(),
                                                 QStandardPaths::LocateDirectory),
                                             tr("xml Files (*.xml)"))
              :QFileDialog::getSaveFileName(this, tr("Save xml File"),
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

void ConfigWindowBase::WriteXmlFile() {
    WriteXmlFileImp(xml_file_name);
}

void ConfigWindowBase::set_file_open_mode() {
    mode = true;
}

void ConfigWindowBase::set_file_save_mode() {
    mode = false;
}
