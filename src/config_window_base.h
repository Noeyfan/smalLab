#ifndef CONFIGWINDOWBASE_H
#define CONFIGWINDOWBASE_H

#include "utility.h"

class ConfigWindowBase : public QMainWindow
{
    Q_OBJECT
public:
    explicit ConfigWindowBase(QWidget *parent = 0);
    virtual ~ConfigWindowBase() = default;

    // base class should implement how Xml is readed
    virtual void ReadXmlFileImp(QString) = 0;
    virtual void WriteXmlFileImp(QString) = 0;

public:
    virtual bool CheckEmpty() = 0;

private slots:
    void get_xml_file_name();
    void set_file_open_mode();
    void set_file_save_mode();
    void ReadXmlFile();
    void WriteXmlFile();

protected:
    QPushButton* open_button;
    QPushButton* save_button;
    QString xml_file_name;
    bool mode = true;
    QValidator* validator;
};

#endif // CONFIGWINDOWBASE_H
