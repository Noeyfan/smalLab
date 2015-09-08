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

    //goals
    goals.reserve(3);
    for (int i = 0; i < 3; i++) {
        goals[i] = new MTextField(this);
        goals[i]->move(350, 150 + i * 60);
        QLabel *goal_label = new QLabel("goal" + QString::number(i + 1), this);
        goal_label->move(380, 120 + i * 60);
        connect(goals[i], SIGNAL(editingFinished()), this, SLOT(SetValue()));
        connect(goals[i], SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    }

    // fractions
    fractions.reserve(3);
    for (int i = 0; i < 3; i++) {
        fractions[i] = new QComboBox(this);
        fractions[i]->addItems(QStringList(QList<QString> {
                                    "blank", "fraction", "decimal",
                                    "percent", "angle"}));
        fractions[i]->resize(100, 25);
        fractions[i]->move(200, 150 + i * 60);
        QLabel *goal_label = new QLabel("format" + QString::number(i + 1), this);
        goal_label->move(210, 120 + i * 60);
        connect(fractions[i], SIGNAL(activated(int)), this, SLOT(SetValueFormat()));
    }

    //goalrep
    goalreps.reserve(3);
    for (int i = 0; i < 3; i++) {
        goalreps[i] = new QComboBox(this);
        goalreps[i]->addItems(QStringList(QList<QString> {
                                    "blank", "fraction", "decimal",
                                    "percent", "angle"}));
        goalreps[i]->resize(100, 25);
        goalreps[i]->move(500, 150 + i * 60);
        QLabel *goal_label = new QLabel("goal" + QString::number(i + 1) + "rep", this);
        goal_label->move(510, 120 + i * 60);
        connect(goalreps[i], SIGNAL(activated(int)), this, SLOT(SetValueRep()));
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
                        level_element.formats[0] = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "format2") {
                        level_element.formats[1] = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "format3") {
                        level_element.formats[2] = rxml.readElementText();
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
                        level_element.goalreps[0] = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "goal2rep") {
                        level_element.goalreps[1] = rxml.readElementText();
                        rxml.readNext();
                    }else if (rxml.name() == "goal3rep") {
                        level_element.goalreps[2] = rxml.readElementText();
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

    wxml.writeStartElement("livingFractions");
    WriteCDataNumb("highestDenominator", highest_denominator);
    wxml.writeStartElement("levelList");

    for (const auto& ele : levels) {
        wxml.writeStartElement("level");
        WriteCDataString("format1", ele.formats[0]);
        WriteCDataString("format2", ele.formats[1]);
        WriteCDataString("format3", ele.formats[2]);

        if (ele.goals[0] != 0)
        {
            WriteCDataNumb("goal1", ele.goals[0]);
            WriteCDataString("goal1rep", ele.goalreps[0]);
        }
        if (ele.goals[1] != 0)
        {
            WriteCDataNumb("goal2", ele.goals[1]);
            WriteCDataString("goal2rep", ele.goalreps[1]);
        }
        if (ele.goals[2] != 0)
        {
            WriteCDataNumb("goal3", ele.goals[2]);
            WriteCDataString("goal3rep", ele.goalreps[2]);
        }
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}
