#include "cupcake_war.h"

CupcakeWar::CupcakeWar(QWidget* parent) : ConfigWindowBase(parent), list_view(new MList(this))
{
    for (int i = 0; i < nutritions.size(); ++i) {
        QCheckBox* qcb = new QCheckBox(nutritions[i], this);
        QLineEdit* txt = new QLineEdit(this);
        qcb->move(300, 150 + i * 40);
        txt->move(400, 150 + i * 40);
        selection.push_back(std::make_pair(qcb, txt));
        txt->setValidator(validator);
        connect(qcb, SIGNAL(clicked()), this, SLOT(SetVal()));
        connect(qcb, SIGNAL(clicked()), this, SLOT(CheckEmpty()));
        connect(txt, SIGNAL(editingFinished()), this, SLOT(SetVal()));
        connect(txt, SIGNAL(textEdited(QString)), this, SLOT(CheckEmpty()));
    }
    connect(list_view, SIGNAL(level_added()), this, SLOT(add_level()));
    connect(list_view->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(Update(QModelIndex)));
}

void CupcakeWar::ReadXmlFileImp(QString filename) {
    XmlFileReader rxml(filename, "CupcakeWar", this);

    // Clear List before load from File
    levels.clear();
    selection.clear();
    list_view->clear();
    rxml.readNextStartElement();

    while (!rxml.atEnd()) {
        rxml.readNext();
        if (rxml.name() == "level") {
            rxml.readNext();
            std::vector<std::pair<bool, int>> item(nutritions.size(), {false, 0});
            while (rxml.name() != "level") {
                if (rxml.name() == "item") {
                    qDebug() << rxml.attributes().value("index") << rxml.attributes().value("value");
                    item[rxml.attributes().value("index").toInt()] =
                            std::make_pair(true, rxml.attributes().value("value").toInt());
                    rxml.readNext();
                }
                rxml.readNext();
            }
            levels.push_back(item);
        }
    }

    list_view->setLines(levels.size());

    if(rxml.hasError()) qDebug() << "has error\n";
}

void CupcakeWar::WriteXmlFileImp(QString filename) {
    SetVal();
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("CupcakeWar");
    wxml.writeStartElement("levelList");
    //for (const auto& ele : levels) {
    for (int i = 0; i < levels.size(); ++i) {
        wxml.writeStartElement("level");
        for (int j = 0; j < levels[i].size(); ++j) {
            if (!levels[i][j].first) continue;
            wxml.writeStartElement("item");
            wxml.writeAttribute("index", QString::number(j));
            wxml.writeAttribute("value", QString::number(levels[i][j].second));
            wxml.writeEndElement();
        }
        wxml.writeEndElement();
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}

bool CupcakeWar::CheckEmpty() {
    if (levels.empty() || list_view->currentIndex() == -1) {
        for (int i = 0; i < nutritions.size(); i++) {
            selection[i].second->setText("");
        }
        QMessageBox::warning(this, "Message", "Please select or add a level first",
                             QMessageBox::Ok);
        return true;
    }
    return false;
}
