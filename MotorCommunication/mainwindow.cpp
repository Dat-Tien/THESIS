#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QObject>
#include <QTableWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QTime>
#include "capture.h"
#include <QSerialPort>

using namespace cv;
using namespace std;
using namespace rs2;

std::vector<int32_t> Pos;
int32_t str[6];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Robot Communication");
    setWindowIcon(QIcon("C:/Users/TD/Desktop/Yaskawa/Qt_Controller/MotorCommunication/motomini.png"));
    connect(ui->btnQuit,SIGNAL(clicked()),this,SLOT(close()));

    table = ui->tableWidgetPoints;
    count = 0;

    Multi = new QTimer(this);
    Multi->setInterval(2000);
    connect(Multi,SIGNAL(timeout()),this,SLOT(MultiPoint()));

    TransPosX = new QTimer(this);
    TransPosX->setInterval(250);
    connect(TransPosX,SIGNAL(timeout()),this,SLOT(TransportPosX()));

    videoCapture = new capture(this);
    QObject::connect(videoCapture,SIGNAL(newPixmapCaptured_Color()), this, SLOT (handleButton()));
    QObject::connect(videoCapture,SIGNAL(rectangle()), this, SLOT (detect_rectangle()));
    QObject::connect(videoCapture,SIGNAL(circle()), this, SLOT (detect_circle()));
    QObject::connect(videoCapture,SIGNAL(defect()), this, SLOT (detect_defectshape()));
    QObject::connect(videoCapture,SIGNAL(noobject()), this, SLOT (detect_noobject()));
    QObject::connect(videoCapture,SIGNAL(hexagon()), this, SLOT (detect_hexagon()));
    QObject::connect(videoCapture,SIGNAL(pass()), this, SLOT (pass_height()));
    QObject::connect(videoCapture,SIGNAL(fail()), this, SLOT (fail_height()));

    videoCapture->StreamOption=0;

    testWrite = new QTimer(this);
    connect(testWrite,SIGNAL(timeout()),this,SLOT(Test_Continues()));

    serial = new QSerialPort;

    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    connect(serial,SIGNAL(readyRead()),this,SLOT(ReadSerial()));



    TimeWriteY = new QTimer(this);
    connect(TimeWriteY,SIGNAL(timeout()),this,SLOT(AddYrobot()));

}

MainWindow::~MainWindow()
{
    delete ui;
//    videoCapture->terminate();// dong thread
}

void MainWindow::handleButton()
{
    ui->cameraFrame->setPixmap(videoCapture->pixmap_Color().scaled(640,480));
}

void MainWindow::detect_rectangle()
{
    ui->label_shape->setText("Rectangle");
    shape = 3;
}

void MainWindow::detect_circle()
{
    ui->label_shape->setText("Circle");
    shape = 6;
}
void MainWindow::detect_hexagon()
{
    ui->label_shape->setText("Hexagon");
    shape = 7;
}

void MainWindow::detect_defectshape()
{
    ui->label_shape->setText("Defect");
}

void MainWindow::detect_noobject()
{
    ui->label_shape->setText("No Object");
    ui->label_height->setText("No Object");
}



void MainWindow::pass_height()
{
    ui->label_height->setText("Pass");
}

void MainWindow::fail_height()
{
    ui->label_height->setText("Fail");
}

void MainWindow::ReadSerial()
{

    ui->textEdit_Serial->setText(serial->readAll());
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
};\

//--------------Thread Position-------------------------------
void MainWindow::ReadPosCartasian(){
        socket->GetCartasianPos();

}
void MainWindow::ReadPosPulse()
{
        socket->GetPulsePos();

}
void MainWindow::DisplayPosition()
{
    ui->tbxX->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),52,4)/1000) +" mm");
    ui->tbxY->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),56,4)/1000) +" mm");
    ui->tbxZ->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),60,4)/1000) +" mm");
    ui->tbxRoll->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),64,4)/10000) +" deg");
    ui->tbxPitch->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),68,4)/10000)+" deg");
    ui->tbxYaw->setText(QString::number((double)socket->ByteArray2Int32(socket->Get_rx_buffer(),72,4)/10000)  +" deg");


}
void MainWindow::DisplayPulse()
{
    ui->tbxX->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),52,4)));
    ui->tbxY->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),56,4)));
    ui->tbxZ->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),60,4)));
    ui->tbxRoll->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),64,4)));
    ui->tbxPitch->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),68,4)));
    ui->tbxYaw->setText(QString::number(socket->ByteArray2Int32(socket->Get_rx_buffer(),72,4)));
    std::vector<double> Joints;
    for (int i=0;i<6;i++){
        Joints.push_back(socket->Pulse2Joint(socket->ByteArray2Int32(socket->Get_rx_buffer(),52 + i*4,4),i));
    }
    ui->tbxX_2->setText(QString::number(Joints.at(0),'f',4)    + " deg");
    ui->tbxY_2->setText(QString::number(Joints.at(1),'f',4)    + " deg");
    ui->tbxZ_2->setText(QString::number(Joints.at(2),'f',4)    + " deg");
    ui->tbxRoll_2->setText(QString::number(Joints.at(3),'f',4) + " deg");
    ui->tbxPitch_2->setText(QString::number(Joints.at(4),'f',4)+ " deg");
    ui->tbxYaw_2->setText(QString::number(Joints.at(5),'f',4)  + " deg");


}
//------------------------------------------------------------
void MainWindow::Read()
{
    socket->ReceiveData();
    stop = clock();
    switch (socket->Get_rx_buffer()->at(11)) {
    case 02:
        DisplayPosition();
        for(int i = 0; i< 6;i++){
            Pos.push_back(socket->ByteArray2Int32(socket->Get_rx_buffer(),52 + 4*i,4));
        }
        for(uint i = 0; i<Pos.size();i++){
            str[i] = Pos.at(i);
        }
        Pos.clear();
        break;
    case 03:
        DisplayPulse();
        for(int i = 0; i< 6;i++){
            Pos.push_back(socket->ByteArray2Int32(socket->Get_rx_buffer(),52 + 4*i,4));
        }
        for(uint i = 0; i<Pos.size();i++){
            str[i] = Pos.at(i);
        }
        Pos.clear();
        break;
    default:
        ui->textBrowser111->setText(QString::number(double(stop-start)/CLOCKS_PER_SEC*1000));
        break;
    }
}

//---------Connected/Disconnected------------------------
void MainWindow::on_btnConnected_clicked()
{
    QHostAddress h;
    if(ui->btnConnected->text()=="Connected")
    {
        ui->btnConnected->setText("Disconnected");
        h.setAddress(ui->tbxIPAdress->toPlainText());
        quint16 p = ui->tbxPort->toPlainText().toUInt();
        socket = new udp(h,p);
        socket->ConnectMotoman();
        connect(socket->client,SIGNAL(readyRead()),this,SLOT(Read()));
        start = clock();

// Lay Signal tu Thread de doc vi tri cua Robot

        connect(socket,SIGNAL(SigReadCartasian()),this,SLOT(ReadPosCartasian()));
        connect(socket,SIGNAL(SigReadPulse()),this,SLOT(ReadPosPulse()));
        connect(socket,SIGNAL(SigWriteCartasian()),this,SLOT(Test_Continues()));

        while(1){
          //   qDebug()<< videoCapture->y_robot;
             delay(500);
        }

    }
    else
    {
        ui->btnConnected->setText("Connected");
        socket->DisconnectMotoman();
    }

}
//------------------------------------------------------------
//----------Servo---------------------------------------------
void MainWindow::on_btnServo_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first!");
    }
    else
    {
    if(ui->btnServo->text() == "ON Servo")
    {
        ui->btnServo->setText("OFF Servo");
        ui->lblStatusServo->setText("ON");
        start = clock();
        socket->OnServo();

    }
    else
    {
        ui->btnServo->setText("ON Servo");
        ui->lblStatusServo->setText("OFF");
        start = clock();
        socket->OffServo();
        socket->terminate();


    }
    }
}
//-------HomePos---------------------------------------------------
void MainWindow::on_btnHome_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    socket->HomePos();
    }

}
//-----------------------------------------------------------------

//----------Move Joint---------------------------------------------
void MainWindow::on_btnMoveJ_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
        bool x,y,z,rx,ry,rz,v;
        x = ui->tbxMoveX->toPlainText().size()==0;
        y = ui->tbxMoveY->toPlainText().size()==0;
        z = ui->tbxMoveZ->toPlainText().size()==0;
        rx = ui->tbxMoveRoll->toPlainText().size()==0;
        ry = ui->tbxMovePitch->toPlainText().size()==0;
        rz = ui->tbxMoveYaw->toPlainText().size()==0;
        v = ui->tbxMovSpeed->toPlainText().size()==0;

        if(x||y||z||rx||ry||rz)
        {
            QMessageBox::critical(this,"Error","Please insert the position!");
        }
        else if (v) {
            QMessageBox::critical(this,"Error","Please insert the velocity!");
        }
        else
        {
            if(ui->chkCartesianPos->isChecked()==true)
            {
                int32_t speed = ui->tbxMovSpeed->toPlainText().toDouble(&v)*100;
                int32_t X = ui->tbxMoveX->toPlainText().toDouble(&x)*1000;
                int32_t Y = ui->tbxMoveY->toPlainText().toDouble(&y)*1000;
                int32_t Z = ui->tbxMoveZ->toPlainText().toDouble(&z)*1000;
                int32_t RX = ui->tbxMoveRoll->toPlainText().toDouble(&rx)*10000;
                int32_t RY = ui->tbxMovePitch->toPlainText().toDouble(&ry)*10000;
                int32_t RZ = ui->tbxMoveYaw->toPlainText().toDouble(&rz)*10000;
                 if(x&&y&&z&&rx&&ry&&rz&&v)
                 {
                     start = clock();
                     socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);

                 }
                 else
                 {
                      QMessageBox::critical(this,"Error","Please check the number format!");
                 }
            }
            else
            {
                int32_t speed = ui->tbxMovSpeed->toPlainText().toInt(&v)*100;
                int32_t R1 = ui->tbxMoveX->toPlainText().toInt(&x);
                int32_t R2 = ui->tbxMoveY->toPlainText().toInt(&y);
                int32_t R3 = ui->tbxMoveZ->toPlainText().toInt(&z);
                int32_t R4 = ui->tbxMoveRoll->toPlainText().toInt(&rx);
                int32_t R5 = ui->tbxMovePitch->toPlainText().toInt(&ry);
                int32_t R6 = ui->tbxMoveYaw->toPlainText().toInt(&rz);
                if(x&&y&&z&&rx&&ry&&rz&&v)
                {
                    start = clock();
                    socket->WritePosPulse(speed,R1,R2,R3,R4,R5,R6);
                }
            }
        }
    }
}
void MainWindow::on_chkcarPulPos_clicked()
{
    if(ui->chkCartesianPos->isChecked()){
         QMessageBox::information(this,"Error","Both Cordinate are checked!");
    }
    else{
        if(ui->chkcarPulPos->isChecked())
        {
            socket->StopReadPos = true;
      //      qDebug()<<"StopReadPos: "<<socket->StopReadPos;

            ui->btnX1->setText("S-");
            ui->btnX2->setText("S+");
            ui->btnY1->setText("L-");
            ui->btnY2->setText("L+");
            ui->tbnZ1->setText("U-");
            ui->btnZ2->setText("U+");
            ui->btnR1->setText("R-");
            ui->btnR2->setText("R+");
            ui->btnP1->setText("B-");
            ui->btnP2->setText("B+");
            ui->btnYaw1->setText("T-");
            ui->btnYaw2->setText("T+");

        }
        else
        {
            socket->StopReadPos = false;
            //qDebug()<<"StopReadPos: "<<socket->StopReadPos;
            ui->btnX1->setText("X-");
            ui->btnX2->setText("X+");
            ui->btnY1->setText("Y-");
            ui->btnY2->setText("Y+");
            ui->tbnZ1->setText("Z-");
            ui->btnZ2->setText("Z+");
            ui->btnR1->setText("RX-");
            ui->btnR2->setText("RX+");
            ui->btnP1->setText("RY-");
            ui->btnP2->setText("RY+");
            ui->btnYaw1->setText("RZ-");
            ui->btnYaw2->setText("RZ+");
        }
    }

}
//-----------------------------------------------------------------
//-----------Teaching Multi Points---------------------------------
void MainWindow::on_chkCartesianPos_clicked()
{
    if(ui->chkcarPulPos->isChecked() == true)
    {
        QMessageBox::information(this,"Error","Both Cordinate are checked!");
    }
    else
    {
        if(ui->chkCartesianPos->isChecked()==true)
        {
            ui->lblMovX->setText("X");
            ui->lblMovY->setText("Y");
            ui->lblMovZ->setText("Z");
            ui->lblMovRx->setText("Roll");
            ui->lblMovRy->setText("Pitch");
            ui->lblMovRz->setText("Yaw");
            ui->lblUnitCar1->setText("mm");
            ui->lblUnitCar2->setText("mm");
            ui->lblUnitCar3->setText("mm");
            ui->lblUnitCar4->setText("deg");
            ui->lblUnitCar5->setText("deg");
            ui->lblUnitCar6->setText("deg");
        }
        else
        {
            ui->lblMovX->setText("S");
            ui->lblMovY->setText("L");
            ui->lblMovZ->setText("U");
            ui->lblMovRx->setText("R");
            ui->lblMovRy->setText("B");
            ui->lblMovRz->setText("T");
            ui->lblUnitCar1->setText("deg");
            ui->lblUnitCar2->setText("deg");
            ui->lblUnitCar3->setText("deg");
            ui->lblUnitCar4->setText("deg");
            ui->lblUnitCar5->setText("deg");
            ui->lblUnitCar6->setText("deg");
        }
    }


}
void MainWindow::on_btnTeaching_clicked()
{
    if(ui->chkcarPulPos->isChecked() == true)
    {
        int Num = ui->tableWidgetPoints->rowCount() ;
        table->setRowCount(Num);
        table->setColumnCount(6);
      //  qDebug()<<Num;

        ui->tableWidgetPoints->insertRow(ui->tableWidgetPoints->rowCount());
        ui->tableWidgetPoints->setItem(Num,PosX,new QTableWidgetItem(QString::number(ui->tbxX->toPlainText().toDouble())));
        ui->tableWidgetPoints->setItem(Num,PosY,new QTableWidgetItem(QString::number(ui->tbxY->toPlainText().toDouble())));
        ui->tableWidgetPoints->setItem(Num,PosZ,new QTableWidgetItem(QString::number(ui->tbxZ->toPlainText().toDouble())));
        ui->tableWidgetPoints->setItem(Num,PosRx,new QTableWidgetItem(QString::number(ui->tbxRoll->toPlainText().toDouble())));
        ui->tableWidgetPoints->setItem(Num,PosRy,new QTableWidgetItem(QString::number(ui->tbxPitch->toPlainText().toDouble())));
        ui->tableWidgetPoints->setItem(Num,PosRz,new QTableWidgetItem(QString::number(ui->tbxYaw->toPlainText().toDouble())));
    }
    else
    {
        QMessageBox::information(this,"Error","Teaching Type Pulse only");
    }


}
//------------------------------------------------------------------
//---------Clear Data-----------------------------------------------
void MainWindow::on_btnClearData_clicked()
{
    int Row = table->rowCount();
    ui->tableWidgetPoints->removeRow(Row-1);
}
//------------------------------------------------------------------
//---------Import Data----------------------------------------------
void MainWindow::on_btnExport_clicked()
{
    auto filename =  QFileDialog::getSaveFileName(this,"Choose an directory",QDir::homePath(), "Txt File (*.txt)");
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
    const int Row = table->rowCount();
    const int Col = table->columnCount();
    for (int ix =0; ix < Row; ++ix)
    {
        xout<<getValueAt(ix,0);
        for (int jx = 1 ;jx < Col; ++jx)
        {
           xout<<','<<getValueAt(ix,jx);
        }
        xout<<"\n";
    }
    file.flush();
    file.close();
}
QString MainWindow::getValueAt(int ix, int jx)
{
    if(!table->item(ix,jx))
    {
        return "";
    }
    return table->item(ix,jx)->text();
}
//------------------------------------------------------------------
//--------Delete Table----------------------------------------------
void MainWindow::on_btnDelete_clicked()
{
   table->clearContents();
}
//------------------------------------------------------------------
//--------Play back-------------------------------------------------
void MainWindow::Waiting(){
    while(1){
        if(table->item(count,PosX)->text().toUInt()- str[0] >1 ||table->item(count,PosY)->text().toUInt()- str[1] >1 ||table->item(count,PosZ)->text().toUInt()- str[2] >1 ||table->item(count,PosRx)->text().toUInt()- str[3] >1 || table->item(count,PosRy)->text().toUInt()- str[4] >1 || table->item(count,PosRz)->text().toUInt()- str[5] >1)
           {
           delay(400);
        }
        else break;
    }
}
void MainWindow::on_btnPlayback_clicked()
{

    //Multi->start();
    int row = table->rowCount();
    while(count != row){
        uint32_t speed = 10*100;
               uint32_t X = table->item(count,PosX)->text().toUInt();
               uint32_t Y = table->item(count,PosY)->text().toUInt();
               uint32_t Z = table->item(count,PosZ)->text().toUInt();
               uint32_t Rx = table->item(count,PosRx)->text().toUInt();
               uint32_t Ry = table->item(count,PosRy)->text().toUInt();
               uint32_t Rz = table->item(count,PosRz)->text().toUInt();
               socket->WritePosPulse(speed,X,Y,Z,Rx,Ry,Rz);
               qDebug()<<count;
               Waiting();
               count+=1;
                if(count == row){
                    count =0;
                    break;
                }
    }
}
void MainWindow::MultiPoint()
{

    int row = table->rowCount();
    uint32_t speed = 20*100;
    uint32_t X = table->item(count,PosX)->text().toUInt();
    uint32_t Y = table->item(count,PosY)->text().toUInt();
    uint32_t Z = table->item(count,PosZ)->text().toUInt();
    uint32_t Rx = table->item(count,PosRx)->text().toUInt();
    uint32_t Ry = table->item(count,PosRy)->text().toUInt();
    uint32_t Rz = table->item(count,PosRz)->text().toUInt();
    socket->WritePosPulse(speed,X,Y,Z,Rx,Ry,Rz);
    count+=1;
  //  qDebug()<<count;

    if(count == row)
    {
         Multi->stop();
         count = 0;
    }
}
//------------------------------------------------------------------
//-------Start Job--------------------------------------------------
void MainWindow::on_btnLoadJob_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
        QString Job = ui->tbxLoadJob->toPlainText();

        char jobname[Job.length()] ;
        strcpy(jobname,Job.toStdString().c_str());
      //  qDebug()<<jobname;
        socket->SelectJob(jobname);
    }
}
void MainWindow::on_btnStartJob_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
        socket->StartJob();
    }
}
//------------------------------------------------------------------
//---------Di chuyen------------------------------------------------
void MainWindow::on_btnX1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
   TransPosX->start();
   Move = 1;
    }
}
void MainWindow::on_btnX1_released()
{

    TransPosX->stop();
    Move = 0;

}
void MainWindow::on_btnX2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 2;
    }
}
void MainWindow::on_btnX2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnY1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 3;
    }
}
void MainWindow::on_btnY1_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnY2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 4;
    }
}
void MainWindow::on_btnY2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_tbnZ1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 5;
    }
}
void MainWindow::on_tbnZ1_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnZ2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 6;
    }
}
void MainWindow::on_btnZ2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnR1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 7;
    }
}
void MainWindow::on_btnR1_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnR2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 8;
    }
}
void MainWindow::on_btnR2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnP1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 9;
    }
}
void MainWindow::on_btnP1_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnP2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 10;
    }
}
void MainWindow::on_btnP2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnYaw1_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 11;
    }
}
void MainWindow::on_btnYaw1_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::on_btnYaw2_pressed()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
    TransPosX->start();
    Move = 12;
    }
}
void MainWindow::on_btnYaw2_released()
{
    TransPosX->stop();
    Move = 0;
}
void MainWindow::TransportPosX()
{
    switch(Move)
    {
    case 1:
        subtractX();
        break;
    case 2:
        addX();
        break;
    case 3:
        subtractY();
        break;
    case 4:
        addY();
        break;
    case 5:
        subtractZ();
        break;
    case 6:
        addZ();
        break;
    case 7:
        subtractRx();
        break;
    case 8:
        addRx();
        break;
    case 9:
        subtractRy();
        break;
    case 10:
        addRy();
        break;
    case 11:
        subtractRz();
        break;
    case 12:
        addRz();
        break;
    default:
        break;
    }
}
void MainWindow::subtractX()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t X1 = 100*speed/100;
        int32_t X = ui->tbxX->toPlainText().toInt() - X1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t X1 = 5*speed/100;
        int32_t X = str[0] - X1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addX()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t X1 = 100*speed/100;
        int32_t X = ui->tbxX->toPlainText().toInt() + X1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t X1 = 5*speed/100;
        int32_t X = str[0] + X1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::subtractY()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Y1 = 100*speed/100;
        int32_t Y = ui->tbxY->toPlainText().toInt() - Y1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t Y1 = 5*speed/100;
        int32_t Y = str[1] - Y1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addY()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Y1 = 100*speed/100;
        int32_t Y = ui->tbxY->toPlainText().toInt() + Y1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t Y1 = 5*speed/100;
        int32_t Y = str[1] + Y1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::subtractZ()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Z1 = 100*speed/100;
        int32_t Z = ui->tbxZ->toPlainText().toInt() - Z1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t Z1 = 5*speed/100;
        int32_t Z = str[2] - Z1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addZ()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Z1 = 100*speed/100;
        int32_t Z = ui->tbxZ->toPlainText().toInt() + Z1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t Z1 = 5*speed/100;
        int32_t Z = str[2] + Z1*1000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::subtractRx()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RX = ui->tbxRoll->toPlainText().toInt() - Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t RX1 = 0.2*speed/100;
        int32_t RX = str[3] - RX1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addRx()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RX = ui->tbxRoll->toPlainText().toInt() + Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RY = str[4];
        int32_t RZ = str[5];
        int32_t RX1 = 0.2*speed/100;
        int32_t RX = str[3] + RX1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::subtractRy()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RY = ui->tbxPitch->toPlainText().toInt() - Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RZ = str[5];
        int32_t RY1 = 0.2*speed/100;
        int32_t RY = str[4] - RY1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addRy()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RZ = ui->tbxYaw->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RY = ui->tbxPitch->toPlainText().toInt() + Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RZ = str[5];
        int32_t RY1 = 0.2*speed/100;
        int32_t RY = str[4] + RY1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::subtractRz()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RZ = ui->tbxYaw->toPlainText().toInt() - Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ1 = 0.2*speed/100;
        int32_t RZ = str[5] - RZ1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::addRz()
{
    if(ui->chkcarPulPos->isChecked())
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = ui->tbxX->toPlainText().toInt();
        int32_t Y = ui->tbxY->toPlainText().toInt();
        int32_t Z = ui->tbxZ->toPlainText().toInt();
        int32_t RX = ui->tbxRoll->toPlainText().toInt();
        int32_t RY = ui->tbxPitch->toPlainText().toInt();
        int32_t Rx1 = 100*speed/100;
        int32_t RZ = ui->tbxYaw->toPlainText().toInt() + Rx1;
        socket->WritePosPulse(speed,X,Y,Z,RX,RY,RZ);
    }
    else
    {
        int32_t speed = ui->progressBarSpeed->value()*100;
        int32_t X = str[0];
        int32_t Y = str[1];
        int32_t Z = str[2];
        int32_t RX = str[3];
        int32_t RY = str[4];
        int32_t RZ1 = 0.2*speed/100;
        int32_t RZ = str[5] + RZ1*10000;
        socket->WritePosCar(speed,X,Y,Z,RX,RY,RZ);
    }
}
void MainWindow::on_SliderSpeed_sliderMoved()
{
    ui->progressBarSpeed->setValue(ui->SliderSpeed->value());
    //qDebug()<<ui->SliderSpeed->value();
}
//------------------------------------------------------------
//------Button JobExecuse----------------------------
void MainWindow::on_btnJobExec_clicked()
{
    DialogFile file;
    file.setModal(true);
    file.getValueTable(TableValue(table->rowCount()),table->rowCount());
    file.exec();
//    startPos->stop();

}
std::vector<QString> MainWindow::TableValue(int row)
{

   std::vector<QString> s;
   for(int i =0;i<row;i++){
       for(int j=0;j<6;j++){
      s.push_back(table->item(i,j)->text());
       }
   }

   return s;
}
//------------------------------------------------------------


QPixmap MainWindow:: cvMatToQPixmap( const cv::Mat &inMat )
   {
      return QPixmap::fromImage( cvMatToQImage( inMat ) );
   }

QImage MainWindow:: cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_ARGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Grayscale8 );
#else
            static QVector<QRgb>  sColorTable;

            // only create our color table the first time
            if ( sColorTable.isEmpty() )
            {
               sColorTable.resize( 256 );

               for ( int i = 0; i < 256; ++i )
               {
                  sColorTable[i] = qRgb( i, i, i );
               }
            }

            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );
#endif

            return image;
         }

         default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }
cv::Mat MainWindow::QImageToMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    /*case QImage::Format_Grayscale8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;*/
    }
    return mat;
}


void MainWindow::on_camera_clicked()
{
    if(ui->camera->text() == "Camera ON"){
        ui->camera->setText("Camera OFF");
        if(videoCapture->camera_running == false)
        {
            videoCapture->camera_running = true;
        }
        videoCapture->start(QThread::HighPriority);
    }
    else if(ui->camera->text() == "Camera OFF")
    {
        ui->camera->setText("Camera ON");
        videoCapture->stop();
    }



}

Resize_RubberBand::Resize_RubberBand(QWidget *parent) : QWidget(parent) {
    //tell QSizeGrip to resize this widget instead of top-level window
    setWindowFlags(Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
    rubberband = new QRubberBand(QRubberBand::Rectangle, this);
    rubberband->move(0, 0);
    rubberband->show();
    show();
}

void Resize_RubberBand::resizeEvent(QResizeEvent *) {
    rubberband->resize(size());
}
void Resize_RubberBand::mousePressEvent(QMouseEvent *event)
{
    if(rubberband->geometry().contains(event->pos()))
    {
        rubberband_offset = event->pos() - rubberband->pos();
        move_rubberband = true;
    }
}

void Resize_RubberBand::mouseMoveEvent(QMouseEvent *event)
{
    if(move_rubberband)
    {
        rubberband->move(event->pos() - rubberband_offset);
    }
}

void Resize_RubberBand::mouseReleaseEvent(QMouseEvent *event)
{
    move_rubberband = false;
}

void MainWindow::on_Get_Background_clicked()
{
    videoCapture->MaskSignal = 0;
    QPixmap OriginalPix(*ui->cameraFrame->pixmap());

    videoCapture->BackgroundImage = OriginalPix.toImage();

    if(Find_Mask_Ready)
    {
        band = new Resize_RubberBand(ui->cameraFrame);
        band->move(100, 100);
        band->resize(50, 50);
        band->setMinimumSize(30, 30);
        Find_Mask_Ready = 0;
    }
}

void MainWindow::on_Mask_clicked()
{
    QImage Background = videoCapture->BackgroundImage;

    QPoint center;
    center = band->pos();
    if (!Find_Mask_Ready)
    {
        videoCapture->MaskTLPoint = cv::Point((center.x() ),(center.y() ));
        videoCapture->MaskBRPoint = cv::Point((center.x() + band->width()),(center.y() + band->height()));
        videoCapture->MaskSignal = 1;
        band->close();
        Find_Mask_Ready = 1;
    }

    videoCapture->findcontour_ready =1;

    while(true)
    {
        ui->tbxObjectX->setText(QString::number(videoCapture->x_robot,'f',4) + " mm");
        ui->tbxObjectY->setText(QString::number(videoCapture->y_robot,'f',4)+ " mm");
        ui->tbxObjectZ->setText(QString::number(videoCapture->z_robot,'f',4)+ " mm");
        ui->tbxObjectTheta->setText(QString::number(videoCapture->theta,'f',4) + " deg");

        delay(100);
    }

}






void MainWindow::Test_Continues()
{

    //double velog = ui->SerialPort->text().toDouble();
    //yrobot = yrobot + velog*t2*1000;
    int32_t index = 3;
     std::vector<int32_t> pos;
        pos.push_back(xrobot);
        pos.push_back(yrobot);
        pos.push_back(zrobot - 4000);
        pos.push_back(str[3]);
        pos.push_back(str[4]);
        pos.push_back(str[5]);
       socket->WriteVarPosition(index,pos);

//       qDebug()<<"y = "<<yrobot;
      double distance = sqrt(pow(xrobot-str[0],2)+pow(yrobot - str[1],2) + pow(zrobot - str[2],2));
      //qDebug()<<distance;
       //qDebug()<<shape;

       ui->textEdiddis->setText(QString::number(shape));

       if( distance <=5*1000) {
           socket->WriteByte(shape,1);
           }
}






void MainWindow::on_pushButtonAuto_clicked()
{

   while(1){
       double velog = ui->textEdit_Serial->toPlainText().toDouble();
       if(videoCapture->blobs.size() == 1){
           if(videoCapture->y_robot > -220 && videoCapture->y_robot<-190){
               xrobot = videoCapture->x_robot*1000;
               yrobot = videoCapture->y_robot*1000 + velog*t1*1000;
               zrobot = videoCapture->z_robot*1000;
               std::vector<int32_t> pos;
               pos.push_back(videoCapture->x_robot*1000);
               pos.push_back(videoCapture->y_robot*1000 + velog*t1*1000);
               pos.push_back(videoCapture->z_robot*1000 );
               pos.push_back(1800000);
               pos.push_back(0);
               pos.push_back(videoCapture->theta);
               uint16_t index = 4;
               socket->WriteVarPosition(index,pos);
               uint16_t B02 = 2;
               socket->WriteByte(B02,1);
               delay(t1*1000);
               uint16_t B04 = 4;
               socket->WriteByte(B04,1);
           }
       }
       else {
           qDebug()<<"khong co vat";
           delay(1000);
       }
   }
}





void MainWindow::on_pushButtonTracking_clicked()
{
    if(ui->btnConnected->text() == "Connected")
    {
       QMessageBox::information(this,"Warning!!!","Pleased Connect UDP first then Turn on Servo");
    }
    else if(ui->btnServo->text() == "ON Servo")
    {
        QMessageBox::information(this,"Warning!!!","Pleased turn on Servo");
    }
    else{
        socket->start();
    }
}


void MainWindow::AddYrobot()
{
    coutY += 1;
  //  qDebug()<<coutY;
}

void MainWindow::on_ConveySpeed_currentIndexChanged(int index)
{
    switch(index){
    case 1:
        t1 = 1.5185;
        t2 = 0.04;
        break;
    case 2:
        t1 = 1.5756;
        t2 = 0.04;
        break;
    case 3:
        t1 = 1.6387;
        t2 = 0.03;
        break;
    case 4:
        t1 = 1.704;
        t2 = 0.03;

        break;
    case 5:
        t1 = 1.7868;
        t2 = 0.04;
    default:
        break;
    }
}





void MainWindow::on_pushButton_PLC_Conveyor_clicked()
{
    if(ui->pushButton_PLC_Conveyor->text()=="ON"){
        ui->pushButton_PLC_Conveyor->setText("OFF");
        std::vector<uint16_t> data;
        data.push_back(1);
        ui->label_Conveyor->setText("START");
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),3,1,data);
        data.at(0) = 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),3,1,data);
    }
    else if(ui->pushButton_PLC_Conveyor->text()=="OFF"){
        ui->pushButton_PLC_Conveyor->setText("ON");
        std::vector<uint16_t> data;
        data.push_back(1);
        ui->label_Conveyor->setText("STOP");
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),5,1,data);
        data.at(0)= 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),5,1,data);
    }
}

void MainWindow::on_pushButtonServoONOFF_clicked()
{
    if(ui->pushButtonServoONOFF->text()=="ON"){
        ui->pushButtonServoONOFF->setText("OFF");
        ui->label_MPE->setText("ON");
        std::vector<uint16_t> data;
        data.push_back(1);
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),2,1,data);
        data.at(0) = 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),4,1,data);
    }
    else if(ui->pushButtonServoONOFF->text()=="OFF"){
        ui->pushButtonServoONOFF->setText("ON");
        ui->label_MPE->setText("OFF");
        std::vector<uint16_t> data;
        data.push_back(1);
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),4,1,data);
        data.at(0)= 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),2,1,data);
    }
}


void MainWindow::on_pushButtonServoHOMING_clicked()
{
    std::vector<uint16_t> data;
    data.push_back(1);
    socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),6,1,data);
}

void MainWindow::on_pushButtonServoSTARTSTOP_clicked()
{
    if(ui->pushButtonServoSTARTSTOP->text() == "START"){
        ui->pushButtonServoSTARTSTOP->setText("STOP");
        std::vector<uint16_t> data;
        data.push_back(1);
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),7,1,data);
        data.at(0)= 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),8,1,data);
    }
    else if(ui->pushButtonServoSTARTSTOP->text() == "STOP"){
        ui->pushButtonServoSTARTSTOP->setText("START");
        std::vector<uint16_t> data;
        data.push_back(1);
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),8,1,data);
        data.at(0)= 0;
        socket->PLC(QHostAddress(ui->tbxIPMPE->toPlainText()),ui->tbxPortMPE->toPlainText().toInt(),7,1,data);
    }
}

void MainWindow::on_btnSerial_clicked()
{
    if(ui->btnSerial->text()== "CONNECTED"){
        ui->btnSerial->setText("DISCONNECTED");
        ui->label_StatusSerial->setText("Connected");
        serial->setPortName(ui->textEdit_SerialPort->toPlainText());
        serial->open(QIODevice::ReadOnly);
    }
    else  if(ui->btnSerial->text()== "DISCONNECTED"){
        ui->btnSerial->setText("CONNECTED");
        ui->label_StatusSerial->setText("Not Connected");
        serial->setPortName(ui->textEdit_SerialPort->toPlainText());
        serial->close();
    }

}




void MainWindow::on_comboBoxImages_currentIndexChanged(int index)
{
    switch(index){
    case 1:
         videoCapture->StreamOption = 0;
        break;
    case 2:
        videoCapture->StreamOption = 1;
        break;
    default:
        break;
    }
}
