#include "living_fractions.h"
#include <QFileDialog>

LivingFractions::LivingFractions(QWidget *parent) : ConfigWindowBase(parent)
{
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
                        level_element.goal1 = rxml.readElementText().toDouble();
                        rxml.readNext();
                    }else if (rxml.name() == "goal2") {
                        level_element.goal2 = rxml.readElementText().toDouble();
                        rxml.readNext();
                    }else if (rxml.name() == "goal3") {
                        level_element.goal3 = rxml.readElementText().toDouble();
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

    for (const auto& ele : levels) {
        ele.print();
    }

    if (rxml.hasError()) {
        qDebug(rxml.errorString().toLatin1());
    }
}

void LivingFractions::WriteXmlFileImp(QString filename) {
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

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

        if (ele.goal1 != 0)
        {
            WriteCDataNumb("goal1", ele.goal1);
            WriteCDataString("goal1rep", ele.goal1rep);
        }
        if (ele.goal2 != 0)
        {
            WriteCDataNumb("goal2", ele.goal2);
            WriteCDataString("goal2rep", ele.goal2rep);
        }
        if (ele.goal3 != 0)
        {
            WriteCDataNumb("goal3", ele.goal3);
            WriteCDataString("goal3rep", ele.goal3rep);
        }
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}
