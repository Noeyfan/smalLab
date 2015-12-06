#ifndef TEACHING_TOOL_H
#define TEACHING_TOOL_H

#include <QWidget>
#include "config_window_base.h"

namespace Ui {
class TeachingTool;
}

struct TT_Ele {
    TT_Ele(QString ip, QString in, const QString& tc, QString vn, QString vu, int a, int b, int c)
        : imagepath(ip), imagename(in), textcontent(tc), videoname(vn), videourl(vu),
          soi(a), sot(b), sov(c){ }
    QString imagepath, imagename, textcontent, videoname, videourl;
    int soi, sot, sov;
    // scene number of image/text/video
};

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

    void on_pushButton_2_clicked();

    void on_levels_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TeachingTool *ui;
    std::vector<TT_Ele> levels;
    std::pair<QStringList, QStringListModel*> level_list;
};

#endif // TEACHING_TOOL_H
