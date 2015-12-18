#include "teaching_tool.h"
#include "ui_teaching_tool.h"

TeachingTool::TeachingTool(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::TeachingTool),
    level_list(QStringList(), new QStringListModel(this))
{
    ui->setupUi(this);
    ui->levels->setModel(level_list.second);
}

TeachingTool::~TeachingTool()
{
    delete ui;
}

void TeachingTool::ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "ToolCustomization", this);
    levels.clear();
    level_list.first.clear();
    clean_inputs();

    rxml.readNextStartElement();
    while(!rxml.atEnd()) {
        rxml.readNext();
        if(rxml.isStartElement() && rxml.name() == "level") {
            rxml.readNextStartElement();
            TT_Ele te;
            te.imagepath = rxml.readElementText();
            rxml.readNextStartElement();
            te.imagename = rxml.readElementText();
            rxml.readNextStartElement();
            te.soi = rxml.readElementText().toInt();
            rxml.readNextStartElement();
            te.textcontent = rxml.readElementText();
            rxml.readNextStartElement();
            te.sot = rxml.readElementText().toInt();
            rxml.readNextStartElement();
            te.videoname = rxml.readElementText();
            rxml.readNextStartElement();
            te.videourl = rxml.readElementText();
            rxml.readNextStartElement();
            te.sov = rxml.readElementText().toInt();
            rxml.readNextStartElement();
            levels.push_back(te);
            level_list.first << te.imagename;
        }
    }
    level_list.second->setStringList(level_list.first);
}

void TeachingTool::WriteXmlFileImp(QString filename) {
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("ToolCustomization");
    wxml.writeStartElement("LevelList");

    // lambda for write CData
    auto WriteCDataNumb = [&wxml](QString tag, double numb) {
        wxml.writeStartElement(tag);
        wxml.writeCDATA(QString::number(numb));
        wxml.writeEndElement();
    };
    auto WriteCDataString = [&wxml](QString tag, QString s) {
        wxml.writeStartElement(tag);
        wxml.writeCDATA(s);
        wxml.writeEndElement();
    };

    for(const auto& ele : levels) {
        wxml.writeStartElement("level");
        WriteCDataString("imagepath", ele.imagename);
        WriteCDataString("imagename", ele.imagepath);
        WriteCDataNumb("scenenumberofimage", ele.soi);
        WriteCDataString("textcontent", ele.textcontent);
        WriteCDataNumb("scenenumberoftext", ele.sot);
        WriteCDataString("nameofvideo", ele.videoname);
        WriteCDataString("videourl", ele.videourl);
        WriteCDataNumb("scenenumberofvideo", ele.sov);
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndDocument();
}

bool TeachingTool::CheckEmpty() {
    return true;
}

QString TeachingTool::HelpImp() {
    return "1) Download the images you want for your scene and save them in a folder on the small Lab computer.\n"
            "2) Copy the location of the folder and paste it in the column named “Image Location on Smalllab System\n"
            "3) Enter the name of the image under the column “Image Name ” and enter which scene you want it in , in the column “Scene Number of Image” , besides it.\n\n"
           "1) For Text and Video you do not have to worry about entering any Folder location\n"
            "2) For text, all you need to do is enter the text you want to display and enter the scene number besides it. There can be multiple texts in the scene but try to use small words. These text will then appear on the right hand side of the small Lab floor. You can pick them up  , and drag them using the wands.\n"
            "3) For Video, once you have found the video you want to show on the internet, copy the address of the video and enter it under the column “Video URL” , enter the name of the video you want to display on the small lab floor in the corresponding row under the column “Name of the Video”. You can then show this video by click on the “Video Name” on the small lab floor. All the video names occur on the left hand side of the floor. Again, try to give small names, and you can enter as many videos in any scene you want.\n\n"
           "Notes:\n1) The first image in each scene becomes the default background image that shows on the floor in that scene. For example, there will be a list of images showing in scene 1, but the first image you put at the column with scene number as 1 will show on the floor as default image. The others will hide at top until you use the wand click it.\n"
           "2) A new scene will be created only if you have an image in that scene, and you cannot enter a video or a text content for a scene which does not have any images in it.";
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

void TeachingTool::on_pushButton_2_clicked()
{
    // add level
    if(ui->img_name_input->text() == "") return;
    levels.emplace_back(ui->img_path_input->text(), ui->img_name_input->text(),
                        ui->text_content_input->text(), ui->video_name_input->text(), ui->video_url_input->text(),
                        ui->soi->text().toInt(), ui->sot->text().toInt(), ui->sov->text().toInt());
    level_list.first << ui->img_name_input->text();
    level_list.second->setStringList(level_list.first);
    clean_inputs();
}

void TeachingTool::on_levels_clicked(const QModelIndex &index)
{
    auto ele = levels[index.row()];
    ui->img_path_input->setText(ele.imagepath); ui->img_name_input->setText(ele.imagename);
    ui->text_content_input->setText(ele.textcontent);
    ui->video_name_input->setText(ele.videoname);
    ui->video_url_input->setText(ele.videourl);
    ui->soi->setText(QString::number(ele.soi));
    ui->sot->setText(QString::number(ele.sot));
    ui->sov->setText(QString::number(ele.sov));
}

void TeachingTool::on_pushButton_clicked()
{
    // update
    int idx = ui->levels->currentIndex().row();
    if(idx < 0) return;
    levels[idx] = TT_Ele(ui->img_path_input->text(), ui->img_name_input->text(),
                         ui->text_content_input->text(), ui->video_name_input->text(), ui->video_url_input->text(),
                         ui->soi->text().toInt(), ui->sot->text().toInt(), ui->sov->text().toInt());
    clean_inputs();
}

void TeachingTool::on_pushButton_3_clicked()
{
    int idx = ui->levels->currentIndex().row();
    if(idx < 0) return;
    levels.erase(levels.begin() + idx);
    level_list.first.erase(level_list.first.begin() + idx);
    level_list.second->setStringList(level_list.first);
    clean_inputs();
}

void TeachingTool::clean_inputs()
{
    ui->img_path_input->clear(); ui->img_name_input->clear();
    ui->text_content_input->clear(); ui->video_url_input->clear();
    ui->video_name_input->clear();
    ui->soi->clear();
    ui->sot->clear();
    ui->sov->clear();
}
