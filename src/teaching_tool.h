#ifndef TEACHING_TOOL_H
#define TEACHING_TOOL_H

#include <QWidget>
#include "config_window_base.h"

namespace Ui {
class TeachingTool;
}

class TeachingTool : public ConfigWindowBase
{
    Q_OBJECT

public:
    explicit TeachingTool(QWidget *parent = 0);
    ~TeachingTool();

    void ReadXmlFileImp(QString);
    void WriteXmlFileImp(QString);
    bool CheckEmpty();
    QString HelpImp();

private slots:
    void on_load_button_clicked();

private:
    Ui::TeachingTool *ui;
};

#endif // TEACHING_TOOL_H
