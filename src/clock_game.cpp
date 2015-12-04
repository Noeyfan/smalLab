#include "clock_game.h"

ClockGame::ClockGame(QWidget *parent) : ConfigWindowBase(parent), list_view(new MList(this)), am_pm({"blank", "am", "pm"}) {
    QLabel *label1 = new QLabel("start hour", this);
    QLabel *label2 = new QLabel("start minute", this);
    QLabel *label3 = new QLabel("start am/pm", this);
    QLabel *label4 = new QLabel("end hour", this);
    QLabel *label5 = new QLabel("end minute", this);
    QLabel *label6 = new QLabel("duration hour", this);
    QLabel *label7 = new QLabel("duration minute", this);
    QLabel *label8 = new QLabel("end am/pm", this);

    start_hour = new QLineEdit("0", this);
    start_hour->move(200, 100 + 60);
    label1->move(200, 130);
    start_minute = new QLineEdit("0", this);
    start_minute->move(320, 100 + 60);
    label2->move(320, 130);
    start_am_pm = new QComboBox(this);
    start_am_pm->move(440, 100 + 60);
    label3->move(440, 130);
    start_am_pm->addItems(am_pm);

    connect(start_hour, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    connect(start_minute, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    connect(start_am_pm, SIGNAL(activated(int)), this, SLOT(SetVal()));

    duration_hour = new QLineEdit("0", this);
    duration_minute = new QLineEdit("0", this);
    duration_hour->move(200, 175 + 60);
    label6->move(200, 205);
    duration_minute->move(320, 175 + 60);
    label7->move(320, 205);

    end_hour = new QLineEdit("0", this);
    end_hour->move(200, 250 + 60);
    label4->move(200, 280);
    end_minute = new QLineEdit("0", this);
    end_minute->move(320, 250 + 60);
    label5->move(320, 280);
    end_am_pm = new QComboBox(this);
    end_am_pm->move(440, 250 + 60);
    end_am_pm->addItems(am_pm);
    label8->move(440, 280);

    connect(end_hour, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    connect(end_minute, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    connect(end_am_pm, SIGNAL(activated(int)), this, SLOT(SetVal()));
    connect(duration_hour, SIGNAL(editingFinished()), this, SLOT(SetVal()));
    connect(duration_minute, SIGNAL(editingFinished()), this, SLOT(SetVal()));

    // check empty TODO, add a base class for QLineEdit to check empty and add regex detection
    connect(start_hour, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    connect(start_minute, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    connect(start_am_pm, SIGNAL(activated(int)), this, SLOT(CheckEmpty()));
    connect(end_hour, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    connect(end_minute, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    connect(end_am_pm, SIGNAL(activated(int)), this, SLOT(CheckEmpty()));
    connect(duration_hour, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    connect(duration_minute, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));

    connect(list_view, SIGNAL(level_added()), this, SLOT(add_level()));
    connect(list_view, SIGNAL(level_deleted(int)), this, SLOT(delete_level(int)));
    connect(list_view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(Update(QModelIndex)));
}

void ClockGame::ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "ElapseTime", this);

    // Clear List before load from File
    levels.clear();
    list_view->clear();
    rxml.readNextStartElement();

    while (!rxml.atEnd()) {
        rxml.readNext();
        if (rxml.name() == "level") {
            rxml.readNext();
            std::tuple<int,int,int> t1;
            std::tuple<int,int,int> t2;
            std::pair<int, int> p;
            while (rxml.name() != "level") {
                if (rxml.name() == "starthour") {
                    int h = 0, m = 0, mer = 0;
                    h = rxml.readElementText().toInt();
                    rxml.readNextStartElement();
                    if (rxml.name() == "startminute") {
                        m = rxml.readElementText().toInt();
                        rxml.readNextStartElement();
                        if (rxml.name() == "startmeridian") {
                            QString txt = rxml.readElementText();
                            mer = (txt == "blank") ? 0 : txt == "am" ? 1 : 2;
                            rxml.readNextStartElement();
                        }
                    }
                    t1 = std::make_tuple(h, m, mer);
                }

                if (rxml.name() == "durationhour") {
                    int h = 0, m = 0;
                    h = rxml.readElementText().toInt();
                    rxml.readNextStartElement();
                    if (rxml.name() == "durationminute") {
                        m = rxml.readElementText().toInt();
                        rxml.readNextStartElement();
                    }
                    p = std::make_pair(h, m);
                }

                if (rxml.name() == "endhour") {
                    int h = 0, m = 0, mer = 0;
                    h = rxml.readElementText().toInt();
                    rxml.readNextStartElement();
                    if (rxml.name() == "endminute") {
                        m = rxml.readElementText().toInt();
                        rxml.readNextStartElement();
                        if (rxml.name() == "endmeridian") {
                            QString txt = rxml.readElementText();
                            mer = txt == "blank" ? 0 : txt == "am" ? 1 : 2;
                            rxml.readNext();
                        }
                    }
                    t2 = std::make_tuple(h, m, mer);
                }
                rxml.readNext();
            }
            levels.push_back({t1, t2, p});
        }
    }

    list_view->setLines(levels.size());

    if(rxml.hasError()) qDebug() << "has error\n";
}

void ClockGame::WriteXmlFileImp(QString filename) {
    SetVal();
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("ElapseTime");
    wxml.writeStartElement("levelList");

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

    for (int i = 0; i < levels.size(); ++i) {
        wxml.writeStartElement("level");
        WriteCDataNumb("starthour", std::get<0>(levels[i].start_time));
        WriteCDataNumb("startminute", std::get<1>(levels[i].start_time));
        WriteCDataString("startmeridian", am_pm[std::get<2>(levels[i].start_time)]);
        WriteCDataNumb("durationhour", levels[i].duration.first);
        WriteCDataNumb("durationminute", levels[i].duration.second);
        WriteCDataNumb("endhour", std::get<0>(levels[i].end_time));
        WriteCDataNumb("endminute", std::get<1>(levels[i].end_time));
        WriteCDataString("endmeridian", am_pm[std::get<2>(levels[i].end_time)]);
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}

bool ClockGame::CheckEmpty() {
    if (levels.empty() || list_view->currentIndex() == -1) {
        QMessageBox::warning(this, "Message", "Please select or add a level first",
                             QMessageBox::Ok);
        return true;
    }
    return false;
}
