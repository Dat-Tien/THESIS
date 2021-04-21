#include "dialogfile.h"
#include "ui_dialogfile.h"

#include <QDebug>
#include <iostream>
#include<QDateTime>
#include <QTime>
#include<QDate>
#include<QTimer>
#include <QFileDialog>
using namespace std;

DialogFile::DialogFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFile)
{
    ui->setupUi(this);
    time = new QTime;
    date = new QDate;
    QTimer *timer = new QTimer;
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(realTimeDate()));


    QHostAddress h;
    const QString u = "192.168.1.15";
    h.setAddress(u);
    socket = new udp(h,10041);
    socket->ConnectMotoman();
    connect(socket->client,SIGNAL(readyRead()),this,SLOT(ReadFile()));
}

DialogFile::~DialogFile()
{
    delete ui;
    socket->DisconnectMotoman();
}


void DialogFile::realTimeDate()
{
    ui->dateTimeEdit->setTime(time->currentTime());
    ui->dateTimeEdit->setDate(date->currentDate());

}

void DialogFile::getValueTable(std::vector<QString> s, int row)
{
    ui->plainTextEdit->appendPlainText("/JOB\n"
                                       "//NAME\n"
                                       "//POS\n"
                                       "///NPOS 0,0,0,2,0,0\n"
                                       "///TOOL 0\n"
                                       "///POSTYPE PULSE\n"
                                       "///PULSE");
    QString A[s.size()];
    for(uint i =0 ;i<s.size();i++ ){
        A[i] = s.at(i);
    }
    for(uint i = 0;i<sizeof(A)/sizeof(QString);i++){
        qDebug()<<A[i];
    }
    QString B;
    for(int j = 0; j<row;j++){
        for(int i = j*7;i<j*7+7;i++){
            B += A[i]+",";
        }
    ui->plainTextEdit->appendPlainText("P0000"+ QString::number(j)+"=" +B);
    B = "";
    }
    ui->plainTextEdit->appendPlainText("//INST\n"
                                       "///DATE\n"
                                       "///ATTR SC,RW\n"
                                       "///GROUP1 RB1\n"
                                       "NOP\n"

                                       "END");

}





void DialogFile::on_btnSaveFile_clicked()
{
    auto filename =  QFileDialog::getSaveFileName(this,"Choose an directory",QDir::homePath(), "JBI File (*.JBI)");
    if(filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream xout(&file);
    xout<<ui->plainTextEdit->toPlainText();
    file.flush();
    file.close();

}


void DialogFile::on_pushButtonOpenFile_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,"open file",
                                       QDir::homePath(), "JBI File (*.JBI)");
//    QMessageBox::information(this,"..",filename);
    if(filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QTextStream in(&file);


    while (!in.atEnd())
    {
        auto line = in.readLine();
        ui->plainTextEdit->appendPlainText(line);
        file.close();
    }
}

void DialogFile::on_pushButtonEXECUTE_clicked()
{

}

void DialogFile::on_pushButtonGetFile_clicked()
{
    QString name = ui->textEditJOBNAME->toPlainText();
    char job[name.length()];
    strcpy(job,name.toStdString().c_str());
    qDebug()<<name.length();
    qDebug()<<job;
    socket->SAVEFILE(job,name.length());
//    int blockNo =0 ;
//    ++blockNo;
//    socket->FILEACK(blockNo);

}

void DialogFile::ReadFile()
{
    socket->ReceiveDataFile();
    ui->plainTextEdit->appendPlainText(socket->HEX2ASCII());
//    QString s = socket->HEX2ASCII();
//    char strChar[s.length()];
//    if(strChar[s.length()]!="")
}
