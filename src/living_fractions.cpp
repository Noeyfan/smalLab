#include "living_fractions.h"
#include <QFileDialog>

LivingFractions::LivingFractions(QWidget *parent) : ConfigWindowBase(parent)
{
    // listview
    listview = new QListView(this);
    QLabel *list_view_label = new QLabel("levels", this);
    listview->resize(100,200);
    listview->move(50, 150);
    list_view_label->move(50, 120);

    add = new QPushButton("+", this);
    add->resize(add->width()/2, add->height());
    add->move(50, 350);

    rid = new QPushButton("-", this);
    rid->resize(rid->width()/2, rid->height());
    rid->move(100, 350);

    model = new QStringListModel(strlist, NULL);
    listview->setModel(model);

    //highest denominator
    QLabel *hd_label = new QLabel("highest\ndenominator", this);
    hd_label->resize(hd_label->width() + 40, hd_label->height() + 80);
    hd_label->move(50,10);
    highest_denominator_txt = new QLineEdit(this);
    highest_denominator_txt->move(50, 80);
    highest_denominator_txt->resize(80, 30);
    connect(highest_denominator_txt, SIGNAL(editingFinished()), this, SLOT(SetHD()));

    //goals
    goals.reserve(3);
    for (int i = 0; i < 3; i++) {
        goals[i] = new QLineEdit(this);
        goals[i]->move(350, 200 + i * 60);
        goals[i]->setValidator(validator);
        QLabel *goal_label = new QLabel("goal" + QString::number(i + 1), this);
        goal_label->move(380, 170 + i * 60);
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
        fractions[i]->move(200, 200 + i * 60);
        QLabel *goal_label = new QLabel("format" + QString::number(i + 1), this);
        goal_label->move(210, 170 + i * 60);
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
        goalreps[i]->move(500, 200 + i * 60);
        QLabel *goal_label = new QLabel("goal" + QString::number(i + 1) + "rep", this);
        goal_label->move(510, 170 + i * 60);
        connect(goalreps[i], SIGNAL(activated(int)), this, SLOT(SetValueRep()));
    }
    // connect
    connect(add, SIGNAL(pressed()), this, SLOT(add_levels()));
    connect(rid, SIGNAL(pressed()), this, SLOT(remove_levels()));
    connect(listview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(Update(QModelIndex)));
}

void LivingFractions:: ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "livingFractions", this);

    // Clear List before load from File
    levels.clear();
    strlist.clear();
    model->setStringList(strlist);

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
    highest_denominator_txt->setText(QString::number(highest_denominator));

    model->setStringList(strlist);
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

bool LivingFractions::CheckEmpty() {
    if (levels.empty() || listview->currentIndex().row() == -1) {
        Reset();
        QMessageBox::warning(this, "Message", "Please select or add a level first",
                             QMessageBox::Ok);
        return true;
    }
    return false;
}

QString LivingFractions::HelpImp() {
    return "1. Use the + / - button to add/delete an level,"
           "then edit the level by selecting the leve you created, after finish all the editing, you can go ahead and export the xml file\n"
           "2. Choose the highest denominator you want to divide the pie chart by.\n"
           "It is recommended that you choose this based on the common fractions you want students to be able to create\n"
           "1/8 * 1/3 = 1/24\n"
           "1/8 * 1/3 * 1/5 = 1/120)\n"
           "3. Every number on the pie chart can be represented through fractions, "
           "decimals, percentages, or left blank, and these representations change from one level to the next.\n"
           "4. Each Level needs at least one goal (in decimal), and a way to represent that goal\n"
           "5. If the sum value is over 1, then your goals are unattainable.\n";
}
