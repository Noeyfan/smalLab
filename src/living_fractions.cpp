#include "living_fractions.h"
#include <QFileDialog>

LivingFractions::LivingFractions(QWidget *parent) : ConfigWindowBase(parent)
{
}

void LivingFractions:: ReadXmlFileImp(QString filename) {
    XmlFile rxml(filename);
    rxml.readNext();
    while (!rxml.atEnd()) {
        rxml.readNext();
        if (rxml.isStartElement()) {
            const auto& tmp = rxml.name().toString();
            qDebug(tmp.toLatin1());
        }
    }

    if (rxml.hasError()) {
        qDebug(rxml.errorString().toLatin1());
    }
}
