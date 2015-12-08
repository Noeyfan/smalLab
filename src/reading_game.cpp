#include "reading_game.h"
#include "ui_reading_game.h"

ReadingGame::ReadingGame(QWidget *parent) :
    ConfigWindowBase(parent),
    ui(new Ui::ReadingGame),
    level_list(QStringList(), new QStringListModel(this))
{
    this->setFixedSize(1000, 450);
    ui->setupUi(this);
    open_button->move(300, 10);
    save_button->move(600, 10);
    help_button->move(450, 410);
    ui->levels->setModel(level_list.second);
}

ReadingGame::~ReadingGame()
{
    delete ui;
}

void ReadingGame::ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "ReadingGame", this);
    levels.clear();
    level_list.first.clear();
    clear_inputs();

    rxml.readNextStartElement();
    ui->e1->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e2->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e3->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e4->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e5->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e6->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e7->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e8->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e9->setText(rxml.readElementText());
    rxml.readNextStartElement();
    ui->e10->setText(rxml.readElementText());
    rxml.readNextStartElement();

    while(!rxml.atEnd()) {
        rxml.readNext();
        if(rxml.name() == "level") {
            rxml.readNextStartElement();
            std::vector<std::pair<QString, QString>> tmp;
            for(int i = 0; i < 10; ++i) {
                QString ls = rxml.readElementText();
                rxml.readNextStartElement();
                QString ld = rxml.readElementText();
                rxml.readNextStartElement();
                tmp.emplace_back(ls, ld);
            }
            levels.push_back(tmp);
        }
    }
    if(rxml.hasError()) qDebug() << rxml.errorString();
    for(int i = 1; i <= levels.size(); ++i) {
        level_list.first << QString::number(i);
    }
    level_list.second->setStringList(level_list.first);
}

void ReadingGame::WriteXmlFileImp(QString filename) {
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("ReadingGame");

    // lambda for write CData
    auto WriteCDataString = [&wxml](QString tag, QString s) {
        wxml.writeStartElement(tag);
        wxml.writeCDATA(s);
        wxml.writeEndElement();
    };

    WriteCDataString("exampleWord1", ui->e1->text());
    WriteCDataString("exampleWord2", ui->e2->text());
    WriteCDataString("exampleWord3", ui->e3->text());
    WriteCDataString("exampleWord4", ui->e4->text());
    WriteCDataString("exampleWord5", ui->e5->text());
    WriteCDataString("exampleWord6", ui->e6->text());
    WriteCDataString("exampleWord7", ui->e7->text());
    WriteCDataString("exampleWord8", ui->e8->text());
    WriteCDataString("exampleWord9", ui->e9->text());
    WriteCDataString("exampleWord10", ui->e10->text());

    wxml.writeStartElement("LevelList");
    for(const auto& ele : levels) {
        wxml.writeStartElement("level");
        for(int i = 0; i < ele.size(); ++i) {
            WriteCDataString("similarword" + QString::number(i+1), ele[i].first);
            WriteCDataString("differentword" + QString::number(i+1), ele[i].second);
        }
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndDocument();
}

bool ReadingGame::CheckEmpty() {

}

QString ReadingGame::HelpImp() {
    return "1. The example word is the word that shows in the thinking cloud. It is used for kids to sort words based on the it.\n"
           "2. Put the words you want the kids to pick in the Similar Word column, put the words they should not choose at the "
           "Different Word column, based on the number matching with the Example word at the top\n"
           "3. You can put any amount lists less than 10, the only thing you need to keep in mind "
           "is to match the amount the example words with number of the lists you use.\n";
}

void ReadingGame::on_pushButton_clicked()
{
    // add level

    auto ls1 = std::make_pair(ui->ls1->text(), ui->ld1->text());
    auto ls2 = std::make_pair(ui->ls2->text(), ui->ld2->text());
    auto ls3 = std::make_pair(ui->ls3->text(), ui->ld3->text());
    auto ls4 = std::make_pair(ui->ls4->text(), ui->ld4->text());
    auto ls5 = std::make_pair(ui->ls5->text(), ui->ld5->text());
    auto ls6 = std::make_pair(ui->ls6->text(), ui->ld6->text());
    auto ls7 = std::make_pair(ui->ls7->text(), ui->ld7->text());
    auto ls8 = std::make_pair(ui->ls8->text(), ui->ld8->text());
    auto ls9 = std::make_pair(ui->ls9->text(), ui->ld9->text());
    auto ls10 = std::make_pair(ui->ls10->text(), ui->ld10->text());

    levels.push_back(std::vector<std::pair<QString, QString>>({ ls1,ls2,ls3,ls4,ls5,ls6,ls7,ls8,ls9,ls10 }));

    level_list.first << QString::number(levels.size());
    level_list.second->setStringList(level_list.first);
    clear_inputs();
}

void ReadingGame::clear_inputs()
{
    ui->ls1->clear(); ui->ld1->clear();
    ui->ls2->clear(); ui->ld2->clear();
    ui->ls3->clear(); ui->ld3->clear();
    ui->ls4->clear(); ui->ld4->clear();
    ui->ls5->clear(); ui->ld5->clear();
    ui->ls6->clear(); ui->ld6->clear();
    ui->ls7->clear(); ui->ld7->clear();
    ui->ls8->clear(); ui->ld8->clear();
    ui->ls9->clear(); ui->ld9->clear();
    ui->ls10->clear(); ui->ld10->clear();
}

void ReadingGame::on_levels_activated(const QModelIndex &index)
{

}

void ReadingGame::on_levels_clicked(const QModelIndex &index)
{
    clear_inputs();
    int idx = index.row();
    ui->ls1->setText(levels[idx][0].first); ui->ld1->setText(levels[idx][0].second);
    ui->ls2->setText(levels[idx][1].first); ui->ld2->setText(levels[idx][1].second);
    ui->ls3->setText(levels[idx][2].first); ui->ld3->setText(levels[idx][2].second);
    ui->ls4->setText(levels[idx][3].first); ui->ld4->setText(levels[idx][3].second);
    ui->ls5->setText(levels[idx][4].first); ui->ld5->setText(levels[idx][4].second);
    ui->ls6->setText(levels[idx][5].first); ui->ld6->setText(levels[idx][5].second);
    ui->ls7->setText(levels[idx][6].first); ui->ld7->setText(levels[idx][6].second);
    ui->ls8->setText(levels[idx][7].first); ui->ld8->setText(levels[idx][7].second);
    ui->ls9->setText(levels[idx][8].first); ui->ld9->setText(levels[idx][8].second);
    ui->ls10->setText(levels[idx][9].first); ui->ld10->setText(levels[idx][9].second);
}

void ReadingGame::on_pushButton_2_clicked()
{
    // update
    int idx = ui->levels->currentIndex().row();
    if(idx < 0) return;
    auto ls1 = std::make_pair(ui->ls1->text(), ui->ld1->text());
    auto ls2 = std::make_pair(ui->ls2->text(), ui->ld2->text());
    auto ls3 = std::make_pair(ui->ls3->text(), ui->ld3->text());
    auto ls4 = std::make_pair(ui->ls4->text(), ui->ld4->text());
    auto ls5 = std::make_pair(ui->ls5->text(), ui->ld5->text());
    auto ls6 = std::make_pair(ui->ls6->text(), ui->ld6->text());
    auto ls7 = std::make_pair(ui->ls7->text(), ui->ld7->text());
    auto ls8 = std::make_pair(ui->ls8->text(), ui->ld8->text());
    auto ls9 = std::make_pair(ui->ls9->text(), ui->ld9->text());
    auto ls10 = std::make_pair(ui->ls10->text(), ui->ld10->text());

    levels[idx] = std::vector<std::pair<QString, QString>>({ ls1,ls2,ls3,ls4,ls5,ls6,ls7,ls8,ls9,ls10 });
    clear_inputs();
}

void ReadingGame::on_pushButton_3_clicked()
{
    // delete
    int idx = ui->levels->currentIndex().row();
    if(idx < 0) return;
    levels.erase(levels.begin() + idx);
    level_list.first.clear();
    for(int i = 1; i <= levels.size(); ++i) {
        level_list.first << QString::number(i);
    }
    level_list.second->setStringList(level_list.first);
    clear_inputs();
}
