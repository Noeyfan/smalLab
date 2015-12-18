#include "order_of_operations.h"
#include "ui_order_of_operations.h"

OrderOfOperations::OrderOfOperations(QWidget *parent)
    : ConfigWindowBase(parent),
    ui(new Ui::OrderOfOperations)
{
    ui->setupUi(this);
    model = new QStringListModel(strlist, NULL);
    this->ui->oplist->setModel(model);
}

OrderOfOperations::~OrderOfOperations()
{
    delete ui;
}

void OrderOfOperations::ReadXmlFileImp(QString filename) {
     XmlFileReader rxml(filename, "OrderOfOperations", this);
     strlist.clear();
     model->setStringList(strlist);
     data.stg2_ops.clear();

     rxml.readNextStartElement();
     while(!rxml.atEnd()) {
         if(rxml.name() == "stage1") {
             rxml.readNextStartElement();
             if (rxml.name() == "numOperators") this->data.stg1_num_of_op = rxml.readElementText().toInt();
             rxml.readNextStartElement();
             if (rxml.name() == "difficulty") this->data.stg1_difficulty = rxml.readElementText().toInt();
             rxml.readNextStartElement();
         }
         if(rxml.name() == "stage2") {
             rxml.readNextStartElement();
             while(rxml.name() != "stage2") {
                 QString s = rxml.readElementText();
                 qDebug() << s;
                 this->data.stg2_ops.push_back(s);
                 rxml.readNextStartElement();
             }
         }
         rxml.readNext();
     }
     if(rxml.hasError()) qDebug() << "has error\n";

     for (int i = 0; i < data.stg2_ops.size(); ++i) {
        strlist << data.stg2_ops[i];
        model->setStringList(strlist);
     }

     ui->difficulty->setCurrentIndex(data.stg1_difficulty - 1);
     ui->opnum->setText(QString::number(data.stg1_num_of_op));
}

void OrderOfOperations::WriteXmlFileImp(QString filename) {
    XmlFileWriter wxml(filename);
    wxml.setAutoFormatting(true);

    wxml.writeStartElement("OrderOfOperations");
    wxml.writeStartElement("stage1");

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

    WriteCDataNumb("numOperators", this->data.stg1_num_of_op);
    WriteCDataNumb("difficulty", this->data.stg1_difficulty);
    wxml.writeEndElement();

    wxml.writeStartElement("stage2");

    for (int i = 0; i < data.stg2_ops.size(); ++i) {
        qDebug() << data.stg2_ops[i];
        WriteCDataString("equation", data.stg2_ops[i]);
    }
    wxml.writeEndElement();
    wxml.writeEndElement();
}

QString OrderOfOperations::HelpImp() {
    QString str = "Stage 1\n"
                  "Set the number of operators and difficulty level for stage 1.\n"
                  "Difficulty level must be a number between 1 - 3.\n"
                  "Difficulty level 1 --- Equations generated only has + and * operators\n"
                  "Difficulty level 2 --- Equations generated has +, -, * and / operators\n"
                  "Difficulty level 3 --- Equations generated has +, -, *"
                  "and / operators as well as parentheses (2 parentheses at most)\n\n"
                  "Stage 2\n"
                  "Input equations that you would like to appear in stage2. \n"
                  "Add a space between each number and operator, as shown in the sample equation.\n"
                  "All operators will be substituted with blanks when they appear in stage 2.\n\n"
                  "Notes: \n1. Equations are randomly chosen for each team from the pool of equations given.\n"
                  "2. Equations that are too long may appear cramped.\n"
                  "3. No negative numbers.";

    return str;
}

void OrderOfOperations::on_add_clicked()
{
    if (this->ui->opinputs->text() == "") return;
    strlist << QString(this->ui->opinputs->text());
    model->setStringList(strlist);
    this->data.stg2_ops.push_back(this->ui->opinputs->text());
    this->ui->opinputs->setText("");
}

void OrderOfOperations::on_remove_clicked()
{
    if (!CheckEmpty()) return;
    int idx = this->ui->oplist->currentIndex().row();
    this->data.stg2_ops.erase(this->data.stg2_ops.begin() + idx);
    strlist.removeAt(idx);
    model->setStringList(strlist);
}

void OrderOfOperations::on_difficulty_activated(int index)
{
    this->data.stg1_difficulty = index + 1;
}

void OrderOfOperations::on_opnum_editingFinished()
{
    this->data.stg1_num_of_op = this->ui->opnum->text().toInt();
}

bool OrderOfOperations::CheckEmpty() {
    if (this->data.stg2_ops.empty() || this->ui->oplist->currentIndex().row() == -1) {
        QMessageBox::warning(this, "Message", "Please select or add a level first",
                             QMessageBox::Ok);
        return false;
    }
    return true;
}
