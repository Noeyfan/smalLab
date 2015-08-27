#ifndef UTILITY
#define UTILITY

#include <QFile>
#include <QXmlStreamReader>

// Main Game List
enum GameList {
    CLOCK_GAME = 0,
    LIVING_FRACTIONS,
    ORDER_OF_OPERATIONS,
    PREFIX_PAGODA,
    READING_GAME,
    TEACHING_TOOL,
};

// xml file wrapper
class XmlFile : public QXmlStreamReader {
    QFile file;

public:
    XmlFile(QString filename) : file(filename) {
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug("File Not opened Correctly");
        }
        this->setDevice(&file);
    }

    ~XmlFile() {
        file.close();
    }
};

#endif // UTILITY

