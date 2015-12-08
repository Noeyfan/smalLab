#include "cupcake_war.h"

CupcakeWar::CupcakeWar(QWidget* parent)
    : ConfigWindowBase(parent),
      nutritions({"Grape", "Kiwi", "Orange", "Pineapple", "Raspberry", "Straberry"}),
      other_attr_val(4, 0)
{
    add_level();
    for (int i = 0; i < (int)nutritions.size(); ++i) {
        QCheckBox* qcb = new QCheckBox(nutritions[i], this);
        QLineEdit* txt = new QLineEdit(this);
        qcb->move(400, 100 + i * 40);
        txt->move(500, 100 + i * 40);
        selection.push_back(std::make_pair(qcb, txt));
        txt->setValidator(validator);
        connect(qcb, SIGNAL(clicked()), this, SLOT(SetVal()));
        connect(qcb, SIGNAL(clicked()), this, SLOT(CheckEmpty()));
        connect(txt, SIGNAL(editingFinished()), this, SLOT(SetVal()));
        connect(txt, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    }

    for(int i = 0; i < 4; ++i) {
        QLineEdit* txt = new QLineEdit(this);
        txt->move(200, 100 + i * 40);
        QLabel *name = new QLabel(i == 0 ? "flour amount"
                                         : i == 1 ? "milk amount"
                                                  : i == 2 ? "max"
                                                           : "min", this);
        name->move(100, 100 + i * 40);
        other_attr.push_back(txt);
        connect(txt, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    }

    grade = new QComboBox(this);
    QLabel *name = new QLabel("grade", this);
    name->move(100, 100 + 4 * 40);
    grade->move(200, 100 + 4 * 40);
    grade->addItems({"3", "4", "5", "6", "7", "8"});

    // connect(list_view, SIGNAL(level_added()), this, SLOT(add_level()));
    // connect(list_view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(Update(QModelIndex)));
}

void CupcakeWar::ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "CupcakeWar", this);

    // Clear List before load from File
    levels.clear();
    rxml.readNextStartElement();

    while (!rxml.atEnd()) {
        rxml.readNext();
        if (rxml.name() == "level") {
            rxml.readNext();
            std::vector<std::pair<bool, float>> item(nutritions.size(), {false, 0});
            while (rxml.name() != "level") {
                if (rxml.name() == "grade") {
                    this->grade->setCurrentIndex(rxml.attributes().value("grade").toInt() - 3);
                    rxml.readNext();
                }

                if (rxml.name() == "item") {
                    // qDebug() << rxml.attributes().value("index") << rxml.attributes().value("value");
                    item[rxml.attributes().value("index").toInt()] =
                            std::make_pair(true, rxml.attributes().value("value").toFloat());
                    rxml.readNext();
                }

                if (rxml.name() == "singleTermRange") {
                    other_attr_val[2] = rxml.attributes().value("max").toInt();
                    other_attr_val[3] = rxml.attributes().value("min").toInt();
                    other_attr[2]->setText(rxml.attributes().value("max").toString());
                    other_attr[3]->setText(rxml.attributes().value("min").toString());
                    rxml.readNext();
                }

                if (rxml.name() == "level1") {
                    other_attr_val[0] = rxml.attributes().value("flour").toInt();
                    other_attr_val[1] = rxml.attributes().value("milk").toInt();
                    other_attr[0]->setText(rxml.attributes().value("flour").toString());
                    other_attr[1]->setText(rxml.attributes().value("mkil").toString());
                    rxml.readNext();
                }

                rxml.readNext();
            }
            levels.push_back(item);
        }
    }

    Update(0);
    if(rxml.hasError()) qDebug() << "has error\n";
}

void CupcakeWar::WriteXmlFileImp(QString filename) {
    // check non Zero
    bool other = true;
    for(const auto& ele : other_attr_val) {
        other = ele && other;
    }

    qDebug() << other;

    for(const auto& ele : levels[0]) {
        if(ele.first && !ele.second || !other) {
            QMessageBox::warning(this, "Error", "Please make sure you filled in the correct number,"
                                                "none of the number should be 0",
                                 QMessageBox::Ok);
            return;
        }
    }


    SetVal();
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("CupcakeWar");
    wxml.writeStartElement("levelList");
    //for (const auto& ele : levels) {
    qDebug() << levels.size();
    for (int i = 0; i < (int)levels.size(); ++i) {
        wxml.writeStartElement("level");
        wxml.writeStartElement("grade");
        wxml.writeAttribute("grade", QString::number(grade->currentIndex() + 3));
        wxml.writeEndElement();
        for (int j = 0; j < (int)levels[i].size(); ++j) {
            if (!levels[i][j].first) continue;
            wxml.writeStartElement("item");
            wxml.writeAttribute("value", QString::number(levels[i][j].second));
            wxml.writeAttribute("index", QString::number(j));
            wxml.writeEndElement();
        }
        wxml.writeStartElement("singleTermRange");
        wxml.writeAttribute("max", QString::number(other_attr_val[2]));
        wxml.writeAttribute("min", QString::number(other_attr_val[3]));
        wxml.writeEndElement();

        wxml.writeStartElement("level1");
        wxml.writeAttribute("flour", QString::number(other_attr_val[0]));
        wxml.writeAttribute("milk", QString::number(other_attr_val[1]));
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
    wxml.writeEndElement();
}

bool CupcakeWar::CheckEmpty() {
    return false;
}

QString CupcakeWar::HelpImp() {
    return "1. flour amount is the total amount of flour, which should be dividable by 6\n"
           "2. milk amount is the total amount of milk, which should be dividable by 5\n"
           "3. the max/min represent { min <= Fruit * Number <= max } for any multiplication of Fruit and Number."
           "4. max and min should not be 0, the ideal value should be min = 5 ~ 10, max = 30 ~ 50"
           "5. grade is only need for recording the result of the game"
           "6. On the right side, select the fruit you need and fill in the number of each fruit(should not be 0).";
}
