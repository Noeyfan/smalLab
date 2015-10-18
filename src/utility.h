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
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTextEdit>

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

    MTextField(QWidget* parent, QString name, std::function<void()>& f)
    : MTextField(parent, name, f, "^[0-9]*(.)*[0-9]+$")
    { }

    MTextField(QWidget* parent, QString name, std::function<void()>& f, QString regex)
    : validator(new QRegExpValidator(QRegExp(regex),parent)), label(new QLabel(name, this)) {
        this->setValidator(validator);
        connect(this, SIGNAL(textEdited(QString)), this, SLOT(check_empty()));
    }

    void move(int x, int y) {
        static_cast<QLineEdit*>(this)->move(x,y);
        label->move(x, y - 30);
    }

    //  regex = "^[0-9]*(.)*[0-9]+$"

private:
    std::function<void()> check_empty;
    QValidator* validator;
    QLabel *label;
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

