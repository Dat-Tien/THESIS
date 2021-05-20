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




    pre_blockNo = 0x80000000;
//    qDebug()<<pre_blockNo+0x0B;
    QString s1  = "0x01";
    Check_blockNo_Send = 0x80000000;

      std::vector<char> s;



}

DialogFile::~DialogFile()
{
    delete ui;
    socket->DisconnectMotoman();
}

void delay2(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
        for(int i = j*6;i<j*6+6;i++){
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

    CheckACK = true;
    if(CheckACK == true){
        ui->plainTextEdit->clear();
        QString name = ui->textEditJOBNAME->toPlainText();
        char job[name.length()];
        strcpy(job,name.toStdString().c_str());
        socket->SAVEFILE(job,name.length());

    }
}

void DialogFile::ReadFile()
{
    socket->ReceiveDataFile();

    qDebug()<<"--------------------------------------------";
    qDebug()<<socket->rx_dataFile;
    QString checkBlock;
    checkBlock.push_back(socket->rx_dataFile.at(72));
    checkBlock.push_back(socket->rx_dataFile.at(73));

    switch(checkBlock.toInt()){
    case 96:
        ui->plainTextEdit->appendPlainText(socket->HEX2ASCII(socket->rx_dataFile));
        CheckBlockNoReceive();
        break;
    case 95:
        delay2(3000);
        CheckBlockNoSend();
        break;
    }


}


void DialogFile::on_btnLoadFile_clicked()
{
    QString name = ui->textEditJOBNAME->toPlainText();
    char job[name.length()];
    strcpy(job,name.toStdString().c_str());
    socket->LOADFILE_REQUEST(job,name.length());


}





void DialogFile::CheckBlockNoReceive()
{
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

    if(block - pre_blockNo != 1)
    {

        socket->FileBlockNoReceive(block);
        block++;
        pre_blockNo += block;
        qDebug()<<"---------------------------------------";

    }
    else
    {
        socket->FileBlockNoReceive(block);
        pre_blockNo = 0x80000000;
        CheckACK = false;
    }

}

void DialogFile::CheckBlockNoSend()
{
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
    qDebug()<<block;
    if(block != Check_blockNo_Send){
        Transmitted_File(block+1);
        qDebug()<<Check_blockNo_Send;

    }
    else{
        Check_blockNo_Send =0x80000000;

        qDebug()<<"Done!!!"<<" "<<Check_blockNo_Send;
        s.resize(0);
    }

}


void DialogFile::Transmitted_File(uint32_t blockNo){

    Check_blockNo_Send+=0x01;
    uint32_t solancat;
    uint32_t chuoicuoi;
    uint32_t length = s.size();
    if(length%100 == 0){
        solancat = length/32;
        chuoicuoi = 0;
    }
    else{
        solancat = length/32;
        chuoicuoi = length%32;
    }

    if(blockNo < solancat+1){// truyen chuoi tu dau den truoc chuoi cuoi cung
        int i = 0;
        char arr[32];
        for(uint32_t ix = (blockNo-1)*32; ix<blockNo*32;ix++){
            if(blockNo == 1){
                arr[ix]= s.at(ix);
                i++;
            }
            else{
                arr[ix - (blockNo-1)*32] = s.at(ix);
                i++;
            }

        }
        qDebug()<<"chuoi truyen vao la: "<<arr;
        qDebug()<<"block ke tiep: "<<blockNo;
        qDebug()<<"data part size "<<i;
        qDebug()<<"chuoi truyen di: ";
        socket->TransmitData(arr,blockNo,32);

    }
    if(blockNo == solancat+1){// truyen chuoi cuoi cung
        int i = 0;
        char arr[chuoicuoi];
        for(uint32_t ix = (blockNo-1)*32;ix < (blockNo-1)*32+chuoicuoi;ix++){
            arr[ix - (blockNo-1)*32] = s.at(ix);
            i++;
        }
        qDebug()<<"chuoi truyen vao la: "<<arr;
        qDebug()<<"blockNo cuoi cung: "<<Check_blockNo_Send;
        qDebug()<<"Data part size: "<<i;
        socket->TransmitData(arr,blockNo+0x80000000,chuoicuoi);

    }

}

void DialogFile::on_pushButton_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,"open file",
                                       QDir::homePath(), "JBI File (*.JBI)");

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
    file.close();
    char strLine [line.size()];
    strcpy(strLine,line.toStdString().c_str());
    char strChar [line.size()];
    for(int i =0;i<line.size();i++)
    {
        strChar[i] = strLine[i];
    }

    s.resize(0);
    for(uint i = 0; i < sizeof (strChar)/sizeof(char);i++){
//            if(strChar[i] != '\n'){
//                s.push_back(strChar[i]);
//           }
        s.push_back(strChar[i]);
    }
    qDebug()<<s;
    ReadLine();


}

void DialogFile::ReadLine()
{
    int dong = 0;
    for(uint i = 0;i<s.size();i++){
        if(s.at(i)=='\n'){
            dong++;
        }
    }
    qDebug()<<dong;


     char a[dong][s.size()];
     for(int i = 0;i<dong;i++){
         for(uint j = 0;j<s.size();j++){
             if(s.at(j)!='\n'){
                 a[i][j] = s.at(j);


             }
             else{
                 break;
             }
         }
     }


}



void DialogFile::on_pushButtonDeleteFile_clicked()
{
    QString a1 = ui->textEditJOBNAME->toPlainText();
    char job[a1.length()];
    strcpy(job,a1.toStdString().c_str());
    socket->DELETEFILE(job,a1.length());
    qDebug()<<a1.length();
    qDebug()<<a1;

}
