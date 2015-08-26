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

signals:

public slots:

private slots:
    void get_xml_file_name() {
        xml_file_name = QFileDialog::
                getOpenFileName(this,tr("Open xml File"),
                                QStandardPaths::locate(
                                    QStandardPaths::DesktopLocation,
                                    QString(),
                                    QStandardPaths::LocateDirectory),
                                tr("xml Files (*.xml)"));
        qDebug("File opened: " + xml_file_name.toLatin1());
    }

protected:
    QPushButton* open_button;
    QString xml_file_name;
};

#endif // CONFIGWINDOWBASE_H
