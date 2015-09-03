#include "living_fractions.h"
#include <QFileDialog>

LivingFractions::LivingFractions(QWidget *parent) : ConfigWindowBase(parent)
{
    // listview
    listview = new QListView(this);
    QLabel *list_view_label = new QLabel("levels", this);
    listview->resize(100,200);
    listview->move(50, 100);
    list_view_label->move(50, 70);

    add = new QPushButton("+", this);
    add->resize(add->width()/2, add->height());
    add->move(50, 300);

    rid = new QPushButton("-", this);
    rid->resize(rid->width()/2, rid->height());
    rid->move(100, 300);

    model = new QStringListModel(strlist, NULL);
    listview->setModel(model);

    //Qline
    goals.reserve(3);
    for (int i = 0; i < 3; i++) {
        goals[i] = new MTextField(this);
        goals[i]->move(300, 150 + i * 60);
        QLabel *goal_label = new QLabel("goal" + QString::number(i), this);
        goal_label->move(300, 120 + i * 60);
        connect(goals[i], SIGNAL(editingFinished()), this, SLOT(SetValue()));
        connect(goals[i], SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    }

    // connect
    connect(add, SIGNAL(pressed()), this, SLOT(add_levels()));
    connect(rid, SIGNAL(pressed()), this, SLOT(remove_levels()));
    connect(listview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(Update(QModelIndex)));
}

void LivingFractions:: ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "livingFractions", this);
    qDebug() << rxml.name().toString();
    rxml.readNextStartElement();
    highest_denominator = rxml.readElementText().toInt();
    while (!rxml.atEnd()) {
        if (rxml.isStartElement()) {
            if (rxml.name() == "levelList") {
                rxml.readNext();
            }
            if (rxml.name() == "level") {
                rxml.readNext();
                LevelElement level_element;
                while (rxml.name() != "level") {
                    if (rxml.name() == "format1") {
                        level_element.format1 = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "format2") {
                        level_element.format2 = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "format3") {
                        level_element.format3 = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "goal1") {
                        level_element.goals[0] = rxml.readElementText().toDouble();
                        rxml.readNext();
                    }else if (rxml.name() == "goal2") {
                        level_element.goals[1] = rxml.readElementText().toDouble();
                        rxml.readNext();
                    }else if (rxml.name() == "goal3") {
                        level_element.goals[2] = rxml.readElementText().toDouble();
                        rxml.readNext();
                    }else if (rxml.name() == "goal1rep") {
                        level_element.goal1rep = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "goal2rep") {
                        level_element.goal2rep = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "goal3rep") {
                        level_element.goal3rep = rxml.readElementText();
                        rxml.readNext();
                    }
                    rxml.readNext();
                }
                levels.push_back(level_element);
            }
        }else {
            rxml.readNext();
        }
    }

    // update qlistview
    int i = 0;
    for (const auto& ele : levels) {
        ele.print();
        strlist << QString::number(i++);
    }
    model->setStringList(strlist);

    if (rxml.hasError()) {
        qDebug(rxml.errorString().toLatin1());
    }
}

void LivingFractions::WriteXmlFileImp(QString filename) {
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);
    SetValue();

    // lambda for write CData
    auto WriteCDataNumb = [&wxml](QString tag, int numb) {
        wxml.writeStartElement(tag);
        wxml.writeCDATA(QString::number(numb));
        wxml.writeEndElement();
    };
    auto WriteCDataString = [&wxml](QString tag, QString s) {
        wxml.writeStartElement(tag);
        wxml.writeCDATA(s);
        wxml.writeEndElement();
    };

    wxml.writeStartElement("livingFractions");
    WriteCDataNumb("highestDenominator", highest_denominator);
    wxml.writeStartElement("levelList");

    for (const auto& ele : levels) {
        wxml.writeStartElement("level");
        WriteCDataString("format1", ele.format1);
        WriteCDataString("format2", ele.format2);
        WriteCDataString("format3", ele.format3);

        if (ele.goals[0] != 0)
        {
            WriteCDataNumb("goal1", ele.goals[0]);
            WriteCDataString("goal1rep", ele.goal1rep);
        }
        if (ele.goals[1] != 0)
        {
            WriteCDataNumb("goal2", ele.goals[1]);
            WriteCDataString("goal2rep", ele.goal2rep);
        }
        if (ele.goals[2] != 0)
        {
            WriteCDataNumb("goal3", ele.goals[2]);
            WriteCDataString("goal3rep", ele.goal3rep);
        }
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}
