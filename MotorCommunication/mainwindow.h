#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udp.h"
#include "dialogfile.h"
#include <time.h>
#include <QObject>
#include <QThread>
#include <QTableWidget>
#include <vector>
using namespace std;

namespace Ui { class MainWindow; }


class DialogFile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void close();


    void DisplayPulse();
    void DisplayPosition();


private slots:
    void MultiPoint();

    void on_btnConnected_clicked();

    void on_btnServo_clicked();

    void Thread_Pos();

    void Read();

    void TransportPosX();

    void on_btnHome_clicked();

    void on_btnMoveJ_clicked();

    void on_chkCartesianPos_clicked();

    void on_btnTeaching_clicked();

    void on_chkcarPulPos_clicked();

    void on_btnClearData_clicked();

    void on_btnDelete_clicked();

    void on_btnPlayback_clicked();

    void on_btnLoadJob_clicked();

    void on_btnStartJob_clicked();

    void on_btnExport_clicked();

    void on_btnX1_pressed();

    void on_btnX1_released();

    void on_SliderSpeed_sliderMoved();

    void on_btnX2_pressed();

    void on_btnX2_released();

    void on_btnY1_pressed();

    void on_btnY1_released();

    void on_btnY2_pressed();

    void on_btnY2_released();

    void on_tbnZ1_pressed();

    void on_tbnZ1_released();

    void on_btnZ2_pressed();

    void on_btnZ2_released();

    void on_btnR1_pressed();

    void on_btnR1_released();

    void on_btnR2_pressed();

    void on_btnR2_released();

    void on_btnP1_pressed();

    void on_btnP1_released();

    void on_btnP2_pressed();

    void on_btnP2_released();

    void on_btnYaw1_pressed();

    void on_btnYaw1_released();

    void on_btnYaw2_pressed();

    void on_btnYaw2_released();

    void on_pushButton_clicked();

    void on_btnSaveJob_clicked();

    void on_btnJobExec_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::MainWindow *ui;
    udp *socket;




    time_t start;
    time_t stop;
    QTimer *startPos;
    QTimer *Multi;

    QTimer *TransPosX;

    QTableWidget *table;

    int count;

    int Move;

    void subtractX();
    void addX();
    void subtractY();
    void addY();
    void subtractZ();
    void addZ();
    void subtractRx();
    void addRx();
    void subtractRy();
    void addRy();
    void subtractRz();
    void addRz();




    void setValueAt( int ix, int jx, const QString &value);
    QString getValueAt(int ix, int jx);

    std::vector<QString> TableValue(int row);

    enum Position
    {
        PosX, PosY, PosZ, PosRx, PosRy, PosRz, Speeds
    };



};
#endif // MAINWINDOW_H
