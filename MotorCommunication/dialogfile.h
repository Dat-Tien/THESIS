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
    uint32_t Check_blockNo_Send;




    void CheckBlockNoReceive();
    void CheckBlockNoSend();
    void Transmitted_File(uint32_t blockNo);

    void ReadLine();

    std::vector<char> s;

    bool CheckACK;


private slots:
    void realTimeDate();

    void on_btnSaveFile_clicked();

    void on_pushButtonOpenFile_clicked();

    void on_pushButtonGetFile_clicked();

    void ReadFile();
    void on_btnLoadFile_clicked();


    void on_pushButton_clicked();
    void on_pushButtonDeleteFile_clicked();
};

#endif // DIALOGFILE_H
