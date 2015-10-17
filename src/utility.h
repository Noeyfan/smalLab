#ifndef UTILITY
#define UTILITY
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QRegExpValidator>

#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QComboBox>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QLineEdit>
#include <QLabel>
#include <QList>
#include <QCheckBox>

// Main Game List
enum GameList {
    CLOCK_GAME = 0,
    LIVING_FRACTIONS,
    ORDER_OF_OPERATIONS,
    PREFIX_PAGODA,
    READING_GAME,
    TEACHING_TOOL,
    CUPCAKE_WAR
};

class MFile {
public:
    QFile file;

    MFile(QString filename) : file(filename) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug("File Not opened Correctly");
        }
    }

    MFile(QString filename, bool) : file(filename) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            qDebug("File Not opened Correctly");
        }
    }

    ~MFile() { file.close(); }
};

class MTextField : QLineEdit {
    Q_OBJECT

public:
    // ctor for class that don't need empty check
    explicit MTextField(QWidget* parent) : QLineEdit(parent) { }

    MTextField(QWidget* parent, std::function<void()>& f) : QLineEdit(parent), check_empty(f) {
        connect(this, SIGNAL(textEdited(QString)), this, SLOT(check_empty()));
    }

    MTextField(QWidget* parent, std::function<void()>& f, QString regex = "^[0-9]*(.)*[0-9]+$")
    : validator(new QRegExpValidator(QRegExp(regex),parent)) {
        this->setValidator(validator);
    }



private:
    std::function<void()> check_empty;
    QValidator* validator;
};

// xml file reader wrapper
class XmlFileReader : public QXmlStreamReader {
    MFile file;

public:
    XmlFileReader(QString filename, QString gamename, QWidget* cur_window) : file(filename) {
        this->setDevice(&file.file);
        if (this->readNextStartElement()) {
            if (this->name() != gamename) {
                QMessageBox::warning(cur_window, "Message", "Wrong config file",QMessageBox::Ok);
            }
        }
    }
};

class XmlFileWriter : public QXmlStreamWriter {
    MFile file;

public:
    XmlFileWriter(QString filename) : file(filename, true), QXmlStreamWriter(&file.file) { }
};

#endif // UTILITY

