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


    func =0;

    pre_blockNo = 0x80000000;

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

    }
    file.close();
}


void DialogFile::on_pushButtonGetFile_clicked()
{
    ui->plainTextEdit->clear();
    QString name = ui->textEditJOBNAME->toPlainText();
    char job[name.length()];
    strcpy(job,name.toStdString().c_str());
    socket->SAVEFILE(job,name.length());
    func =1;



}

void DialogFile::ReadFile()
{
    socket->ReceiveDataFile();
    ui->plainTextEdit->appendPlainText(socket->HEX2ASCII());

    switch (func)
    {
        case 1:
        QString s;
        s.append(socket->rx_dataFile.at(45));
        s.append(socket->rx_dataFile.at(46));
        s.append(socket->rx_dataFile.at(42));
        s.append(socket->rx_dataFile.at(43));
        s.append(socket->rx_dataFile.at(39));
        s.append(socket->rx_dataFile.at(40));
        s.append(socket->rx_dataFile.at(36));
        s.append(socket->rx_dataFile.at(37));
        uint32_t block = s.toUInt(nullptr,16);
        if(block - pre_blockNo != 1 )
        {
            socket->FILEACK(block);
            pre_blockNo += block;
        }
        else
        {
            socket->FILEACK(block);
            pre_blockNo = 0x80000000;

        }
        func = 0;
        break;
    }

}


void DialogFile::on_btnLoadFile_clicked()
{
        auto filename = QFileDialog::getOpenFileName(this,"open file",
                                           QDir::homePath(), "JBI File (*.JBI)");
//        QMessageBox::information(this,"..",filename);
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
        QString line =in.readAll();
        while (!in.atEnd())
        {
            QString line = in.readAll();

        }
        file.close();

        char strLine [line.size()];
        strcpy(strLine,line.toStdString().c_str());
        char strChar [line.size()];
        for(int i =0;i<line.size();i++)
        {
            strChar[i] = strLine[i];
        }
//        qDebug()<<line;
//        qDebug()<<strChar;
        char HexVal[line.size()*2 + 1];
        socket->convert_hexa(strChar,HexVal);
        qDebug()<<HexVal;
        qDebug()<<filename<<" "<<filename.size();

//        socket->SAVEFILE(filename,filename.size());
}
