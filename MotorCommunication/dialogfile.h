#ifndef DIALOGFILE_H
#define DIALOGFILE_H

#include <QDialog>
#include "udp.h"

namespace Ui {
class DialogFile;
}

class DialogFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFile(QWidget *parent = nullptr);
    ~DialogFile();

    void getValueTable(std::vector<QString> s, int row);


private:
    Ui::DialogFile *ui;
    udp *socket;
    QString value;

    std::vector<QString> Para(std::vector<QString> s);
    QTime *time;
    QDate *date;

    QString getValueAt(int ix, int jx);

    uint32_t pre_blockNo;
    int func;
private slots:
    void realTimeDate();

    void on_btnSaveFile_clicked();

    void on_pushButtonOpenFile_clicked();

    void on_pushButtonGetFile_clicked();

    void ReadFile();
    void on_btnLoadFile_clicked();
};

#endif // DIALOGFILE_H
