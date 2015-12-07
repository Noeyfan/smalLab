#include "config_window_base.h"

ConfigWindowBase::ConfigWindowBase(QWidget *parent) : QMainWindow(parent), validator(new QRegExpValidator(QRegExp("^[0-9]*(.)*[0-9]+$"),this))
{
    this->setFixedSize(700, 450);
    open_button = new QPushButton("open file", this);
    save_button = new QPushButton("save file", this);
    help_button = new QPushButton("help", this);
    open_button->move(200, 10);
    save_button->move(400, 10);
    help_button->move(300, 410);

    // Draw 2 Line, should really use Qt designer
    QFrame* line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(0, 50, 1000, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QFrame* line2 = new QFrame(this);
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(0, 400, 1000, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    // File Dialog
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(set_file_open_mode()));
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
    connect(open_button, SIGNAL(clicked(bool)), this, SLOT(ReadXmlFile()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(set_file_save_mode()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(get_xml_file_name()));
    connect(save_button, SIGNAL(clicked(bool)), this, SLOT(WriteXmlFile()));
    connect(help_button, SIGNAL(clicked(bool)), this, SLOT(GetHelp()));
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

void ConfigWindowBase::GetHelp() {
    QMessageBox msgBox;
    msgBox.setText(HelpImp());
    msgBox.setTextFormat(Qt::AutoText);
    msgBox.exec();
}

void ConfigWindowBase::set_file_open_mode() {
    mode = true;
}

void ConfigWindowBase::set_file_save_mode() {
    mode = false;
}

QString ConfigWindowBase::HelpImp() {
    return "Error: 404";
}
