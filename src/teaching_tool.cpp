#include "teaching_tool.h"
#include "ui_teaching_tool.h"

TeachingTool::TeachingTool(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::TeachingTool)
{
    ui->setupUi(this);
}

TeachingTool::~TeachingTool()
{
    delete ui;
}

void TeachingTool::ReadXmlFileImp(QString) {

}

void TeachingTool::WriteXmlFileImp(QString) {

}

bool TeachingTool::CheckEmpty() {

}

QString TeachingTool::HelpImp() {
}

void TeachingTool::on_load_button_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("Open image File"),
                                                     QStandardPaths::locate(
                                                         QStandardPaths::DesktopLocation,
                                                         QString(),
                                                         QStandardPaths::LocateDirectory),
                                                     tr("image Files (*.jpg *.png *.gif *.tiff *.jpeg)"));
    ui->img_path_input->setText(file_name);
    auto sep = file_name.split('/');
    ui->img_name_input->setText(sep[sep.size() - 1]);
}
