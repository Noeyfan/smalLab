#ifndef CONFIGWINDOWBASE_H
#define CONFIGWINDOWBASE_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>

class ConfigWindowBase : public QMainWindow
{
    Q_OBJECT
public:
    explicit ConfigWindowBase(QWidget *parent = 0);
    virtual ~ConfigWindowBase() = default;

    // base class should implement how Xml is readed
    virtual void ReadXmlFileImp(QString) = 0;

signals:

public slots:

private slots:
    void get_xml_file_name();

    void ReadXmlFile();

protected:
    QPushButton* open_button;
    QString xml_file_name;
};

#endif // CONFIGWINDOWBASE_H
