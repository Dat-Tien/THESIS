/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_4;
    QLabel *lblStatusServo;
    QPushButton *btnHome;
    QPushButton *btnServo;
    QLabel *label_9;
    QTextEdit *tbxLoadJob;
    QPushButton *btnLoadJob;
    QPushButton *btnStartJob;
    QLabel *label_10;
    QGroupBox *groupBoxCarPulPos;
    QTextBrowser *tbxPitch;
    QLabel *lblCurrentRy;
    QLabel *lblCurrentRz;
    QLabel *lblCurrentUnitX;
    QLabel *lblCurrentY;
    QLabel *lblCurrentRx;
    QTextBrowser *tbxYaw;
    QTextBrowser *tbxZ;
    QLabel *label_74;
    QLabel *label_75;
    QLabel *lblCurrentZ;
    QTextBrowser *tbxX;
    QLabel *lblCurrentUnitZ;
    QLabel *lblCurrentX;
    QTextBrowser *tbxY;
    QLabel *label_79;
    QLabel *lblCurrentUnitY;
    QTextBrowser *tbxRoll;
    QCheckBox *chkcarPulPos;
    QFrame *line;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnTeaching;
    QPushButton *btnPlayback;
    QPushButton *btnClearData;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetPoints;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnDelete;
    QPushButton *btnJobExec;
    QPushButton *btnExport;
    QHBoxLayout *horizontalLayout;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnX1;
    QPushButton *btnX2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnY1;
    QPushButton *btnY2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *tbnZ1;
    QPushButton *btnZ2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnR1;
    QPushButton *btnR2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btnP1;
    QPushButton *btnP2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnYaw1;
    QPushButton *btnYaw2;
    QVBoxLayout *verticalLayout_5;
    QProgressBar *progressBarSpeed;
    QSlider *SliderSpeed;
    QGroupBox *groupBox_4;
    QLabel *lblUnitCar1;
    QLabel *lblUnitCar4;
    QCheckBox *chkCartesianPos;
    QLabel *lblUnitCar5;
    QTextEdit *tbxMoveY;
    QTextEdit *tbxMovSpeed;
    QLabel *lblMovRy;
    QTextEdit *tbxMoveYaw;
    QPushButton *btnMoveJ;
    QLabel *lblUnitCar3;
    QLabel *lblMovRz;
    QTextEdit *tbxMovePitch;
    QLabel *lblMovY;
    QTextEdit *tbxMoveX;
    QTextEdit *tbxMoveRoll;
    QLabel *lblUnitCar6;
    QLabel *lblMovRx;
    QLabel *lblMovX;
    QLabel *lblMovZ;
    QLabel *lblUnitCar2;
    QTextEdit *tbxMoveZ;
    QLabel *lblMovRz_2;
    QWidget *tab_2;
    QFrame *line_2;
    QTextBrowser *textBrowserSendData;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *textBrowserReceiveData;
    QTableView *tableView;
    QPushButton *pushButtonSave;
    QTextBrowser *textBrowserRecFile;
    QPushButton *pushButton;
    QPushButton *btnACK;
    QWidget *tab_5;
    QGroupBox *groupBox;
    QTextEdit *tbxPort;
    QLabel *label;
    QTextEdit *tbxIPAdress;
    QLabel *label_2;
    QPushButton *btnConnected;
    QLabel *label_3;
    QPushButton *btnQuit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1293, 959);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 991, 721));
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(true);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 80, 47, 13));
        QFont font;
        font.setPointSize(11);
        label_4->setFont(font);
        lblStatusServo = new QLabel(tab);
        lblStatusServo->setObjectName(QString::fromUtf8("lblStatusServo"));
        lblStatusServo->setGeometry(QRect(100, 80, 47, 13));
        lblStatusServo->setFont(font);
        btnHome = new QPushButton(tab);
        btnHome->setObjectName(QString::fromUtf8("btnHome"));
        btnHome->setGeometry(QRect(20, 110, 151, 31));
        QFont font1;
        font1.setPointSize(13);
        btnHome->setFont(font1);
        btnServo = new QPushButton(tab);
        btnServo->setObjectName(QString::fromUtf8("btnServo"));
        btnServo->setGeometry(QRect(20, 40, 151, 31));
        QFont font2;
        font2.setPointSize(12);
        btnServo->setFont(font2);
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 10, 131, 21));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        label_9->setFont(font3);
        tbxLoadJob = new QTextEdit(tab);
        tbxLoadJob->setObjectName(QString::fromUtf8("tbxLoadJob"));
        tbxLoadJob->setGeometry(QRect(180, 200, 111, 71));
        btnLoadJob = new QPushButton(tab);
        btnLoadJob->setObjectName(QString::fromUtf8("btnLoadJob"));
        btnLoadJob->setGeometry(QRect(20, 200, 151, 31));
        btnLoadJob->setFont(font2);
        btnStartJob = new QPushButton(tab);
        btnStartJob->setObjectName(QString::fromUtf8("btnStartJob"));
        btnStartJob->setGeometry(QRect(20, 240, 151, 31));
        btnStartJob->setFont(font1);
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 160, 131, 21));
        label_10->setFont(font3);
        groupBoxCarPulPos = new QGroupBox(tab);
        groupBoxCarPulPos->setObjectName(QString::fromUtf8("groupBoxCarPulPos"));
        groupBoxCarPulPos->setGeometry(QRect(320, 10, 261, 321));
        groupBoxCarPulPos->setFont(font3);
        tbxPitch = new QTextBrowser(groupBoxCarPulPos);
        tbxPitch->setObjectName(QString::fromUtf8("tbxPitch"));
        tbxPitch->setGeometry(QRect(80, 190, 131, 31));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setWeight(75);
        tbxPitch->setFont(font4);
        lblCurrentRy = new QLabel(groupBoxCarPulPos);
        lblCurrentRy->setObjectName(QString::fromUtf8("lblCurrentRy"));
        lblCurrentRy->setGeometry(QRect(20, 200, 51, 16));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(false);
        font5.setItalic(true);
        font5.setWeight(50);
        lblCurrentRy->setFont(font5);
        lblCurrentRz = new QLabel(groupBoxCarPulPos);
        lblCurrentRz->setObjectName(QString::fromUtf8("lblCurrentRz"));
        lblCurrentRz->setGeometry(QRect(20, 241, 51, 16));
        lblCurrentRz->setFont(font5);
        lblCurrentUnitX = new QLabel(groupBoxCarPulPos);
        lblCurrentUnitX->setObjectName(QString::fromUtf8("lblCurrentUnitX"));
        lblCurrentUnitX->setGeometry(QRect(220, 40, 41, 16));
        lblCurrentUnitX->setFont(font5);
        lblCurrentY = new QLabel(groupBoxCarPulPos);
        lblCurrentY->setObjectName(QString::fromUtf8("lblCurrentY"));
        lblCurrentY->setGeometry(QRect(20, 80, 21, 16));
        lblCurrentY->setFont(font5);
        lblCurrentRx = new QLabel(groupBoxCarPulPos);
        lblCurrentRx->setObjectName(QString::fromUtf8("lblCurrentRx"));
        lblCurrentRx->setGeometry(QRect(20, 160, 41, 16));
        lblCurrentRx->setFont(font5);
        tbxYaw = new QTextBrowser(groupBoxCarPulPos);
        tbxYaw->setObjectName(QString::fromUtf8("tbxYaw"));
        tbxYaw->setGeometry(QRect(80, 231, 131, 31));
        tbxYaw->setFont(font4);
        tbxZ = new QTextBrowser(groupBoxCarPulPos);
        tbxZ->setObjectName(QString::fromUtf8("tbxZ"));
        tbxZ->setGeometry(QRect(80, 110, 131, 31));
        tbxZ->setFont(font4);
        label_74 = new QLabel(groupBoxCarPulPos);
        label_74->setObjectName(QString::fromUtf8("label_74"));
        label_74->setGeometry(QRect(220, 150, 41, 31));
        label_74->setFont(font5);
        label_75 = new QLabel(groupBoxCarPulPos);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setGeometry(QRect(220, 231, 51, 31));
        label_75->setFont(font5);
        lblCurrentZ = new QLabel(groupBoxCarPulPos);
        lblCurrentZ->setObjectName(QString::fromUtf8("lblCurrentZ"));
        lblCurrentZ->setGeometry(QRect(20, 120, 21, 16));
        lblCurrentZ->setFont(font5);
        tbxX = new QTextBrowser(groupBoxCarPulPos);
        tbxX->setObjectName(QString::fromUtf8("tbxX"));
        tbxX->setGeometry(QRect(80, 30, 131, 31));
        tbxX->setFont(font4);
        lblCurrentUnitZ = new QLabel(groupBoxCarPulPos);
        lblCurrentUnitZ->setObjectName(QString::fromUtf8("lblCurrentUnitZ"));
        lblCurrentUnitZ->setGeometry(QRect(220, 120, 41, 16));
        lblCurrentUnitZ->setFont(font5);
        lblCurrentX = new QLabel(groupBoxCarPulPos);
        lblCurrentX->setObjectName(QString::fromUtf8("lblCurrentX"));
        lblCurrentX->setGeometry(QRect(20, 40, 21, 16));
        lblCurrentX->setFont(font5);
        tbxY = new QTextBrowser(groupBoxCarPulPos);
        tbxY->setObjectName(QString::fromUtf8("tbxY"));
        tbxY->setGeometry(QRect(80, 70, 131, 31));
        tbxY->setFont(font4);
        label_79 = new QLabel(groupBoxCarPulPos);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setGeometry(QRect(220, 190, 51, 31));
        label_79->setFont(font5);
        lblCurrentUnitY = new QLabel(groupBoxCarPulPos);
        lblCurrentUnitY->setObjectName(QString::fromUtf8("lblCurrentUnitY"));
        lblCurrentUnitY->setGeometry(QRect(220, 80, 41, 16));
        lblCurrentUnitY->setFont(font5);
        tbxRoll = new QTextBrowser(groupBoxCarPulPos);
        tbxRoll->setObjectName(QString::fromUtf8("tbxRoll"));
        tbxRoll->setGeometry(QRect(80, 150, 131, 31));
        tbxRoll->setFont(font4);
        chkcarPulPos = new QCheckBox(groupBoxCarPulPos);
        chkcarPulPos->setObjectName(QString::fromUtf8("chkcarPulPos"));
        chkcarPulPos->setGeometry(QRect(20, 290, 71, 23));
        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(970, 0, 41, 731));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(5);
        line->setFrameShape(QFrame::VLine);
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 330, 931, 421));
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(420, 30, 491, 291));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnTeaching = new QPushButton(layoutWidget);
        btnTeaching->setObjectName(QString::fromUtf8("btnTeaching"));

        horizontalLayout_2->addWidget(btnTeaching);

        btnPlayback = new QPushButton(layoutWidget);
        btnPlayback->setObjectName(QString::fromUtf8("btnPlayback"));

        horizontalLayout_2->addWidget(btnPlayback);

        btnClearData = new QPushButton(layoutWidget);
        btnClearData->setObjectName(QString::fromUtf8("btnClearData"));

        horizontalLayout_2->addWidget(btnClearData);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidgetPoints = new QTableWidget(layoutWidget);
        if (tableWidgetPoints->columnCount() < 6)
            tableWidgetPoints->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetPoints->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetPoints->setObjectName(QString::fromUtf8("tableWidgetPoints"));
        tableWidgetPoints->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"background-color: #C0C0C0;\n"
"altermate-backgroud-color: #606060;\n"
"selection-backgound-color: #282828;\n"
"}\n"
""));
        tableWidgetPoints->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetPoints->setAlternatingRowColors(true);
        tableWidgetPoints->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPoints->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetPoints->setGridStyle(Qt::DashLine);

        verticalLayout->addWidget(tableWidgetPoints);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnDelete = new QPushButton(layoutWidget);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_4->addWidget(btnDelete);

        btnJobExec = new QPushButton(layoutWidget);
        btnJobExec->setObjectName(QString::fromUtf8("btnJobExec"));

        horizontalLayout_4->addWidget(btnJobExec);

        btnExport = new QPushButton(layoutWidget);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));

        horizontalLayout_4->addWidget(btnExport);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        layoutWidget1 = new QWidget(groupBox_5);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 40, 201, 251));
        verticalLayout_6 = new QVBoxLayout(layoutWidget1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnX1 = new QPushButton(layoutWidget1);
        btnX1->setObjectName(QString::fromUtf8("btnX1"));

        horizontalLayout_3->addWidget(btnX1);

        btnX2 = new QPushButton(layoutWidget1);
        btnX2->setObjectName(QString::fromUtf8("btnX2"));

        horizontalLayout_3->addWidget(btnX2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnY1 = new QPushButton(layoutWidget1);
        btnY1->setObjectName(QString::fromUtf8("btnY1"));

        horizontalLayout_5->addWidget(btnY1);

        btnY2 = new QPushButton(layoutWidget1);
        btnY2->setObjectName(QString::fromUtf8("btnY2"));

        horizontalLayout_5->addWidget(btnY2);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tbnZ1 = new QPushButton(layoutWidget1);
        tbnZ1->setObjectName(QString::fromUtf8("tbnZ1"));

        horizontalLayout_6->addWidget(tbnZ1);

        btnZ2 = new QPushButton(layoutWidget1);
        btnZ2->setObjectName(QString::fromUtf8("btnZ2"));

        horizontalLayout_6->addWidget(btnZ2);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        btnR1 = new QPushButton(layoutWidget1);
        btnR1->setObjectName(QString::fromUtf8("btnR1"));

        horizontalLayout_7->addWidget(btnR1);

        btnR2 = new QPushButton(layoutWidget1);
        btnR2->setObjectName(QString::fromUtf8("btnR2"));

        horizontalLayout_7->addWidget(btnR2);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        btnP1 = new QPushButton(layoutWidget1);
        btnP1->setObjectName(QString::fromUtf8("btnP1"));

        horizontalLayout_8->addWidget(btnP1);

        btnP2 = new QPushButton(layoutWidget1);
        btnP2->setObjectName(QString::fromUtf8("btnP2"));

        horizontalLayout_8->addWidget(btnP2);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        btnYaw1 = new QPushButton(layoutWidget1);
        btnYaw1->setObjectName(QString::fromUtf8("btnYaw1"));

        horizontalLayout_9->addWidget(btnYaw1);

        btnYaw2 = new QPushButton(layoutWidget1);
        btnYaw2->setObjectName(QString::fromUtf8("btnYaw2"));

        horizontalLayout_9->addWidget(btnYaw2);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        progressBarSpeed = new QProgressBar(layoutWidget1);
        progressBarSpeed->setObjectName(QString::fromUtf8("progressBarSpeed"));
        progressBarSpeed->setMaximum(100);
        progressBarSpeed->setValue(0);

        verticalLayout_5->addWidget(progressBarSpeed);

        SliderSpeed = new QSlider(layoutWidget1);
        SliderSpeed->setObjectName(QString::fromUtf8("SliderSpeed"));
        SliderSpeed->setMinimum(0);
        SliderSpeed->setMaximum(100);
        SliderSpeed->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(SliderSpeed);


        verticalLayout_6->addLayout(verticalLayout_5);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(600, 10, 301, 321));
        lblUnitCar1 = new QLabel(groupBox_4);
        lblUnitCar1->setObjectName(QString::fromUtf8("lblUnitCar1"));
        lblUnitCar1->setGeometry(QRect(230, 60, 41, 16));
        lblUnitCar1->setFont(font5);
        lblUnitCar4 = new QLabel(groupBox_4);
        lblUnitCar4->setObjectName(QString::fromUtf8("lblUnitCar4"));
        lblUnitCar4->setGeometry(QRect(230, 170, 41, 31));
        lblUnitCar4->setFont(font5);
        chkCartesianPos = new QCheckBox(groupBox_4);
        chkCartesianPos->setObjectName(QString::fromUtf8("chkCartesianPos"));
        chkCartesianPos->setGeometry(QRect(30, 20, 111, 21));
        chkCartesianPos->setFont(font2);
        lblUnitCar5 = new QLabel(groupBox_4);
        lblUnitCar5->setObjectName(QString::fromUtf8("lblUnitCar5"));
        lblUnitCar5->setGeometry(QRect(230, 210, 51, 31));
        lblUnitCar5->setFont(font5);
        tbxMoveY = new QTextEdit(groupBox_4);
        tbxMoveY->setObjectName(QString::fromUtf8("tbxMoveY"));
        tbxMoveY->setGeometry(QRect(80, 90, 131, 31));
        tbxMovSpeed = new QTextEdit(groupBox_4);
        tbxMovSpeed->setObjectName(QString::fromUtf8("tbxMovSpeed"));
        tbxMovSpeed->setGeometry(QRect(80, 290, 81, 31));
        QFont font6;
        font6.setPointSize(7);
        tbxMovSpeed->setFont(font6);
        lblMovRy = new QLabel(groupBox_4);
        lblMovRy->setObjectName(QString::fromUtf8("lblMovRy"));
        lblMovRy->setGeometry(QRect(30, 220, 51, 16));
        lblMovRy->setFont(font5);
        tbxMoveYaw = new QTextEdit(groupBox_4);
        tbxMoveYaw->setObjectName(QString::fromUtf8("tbxMoveYaw"));
        tbxMoveYaw->setGeometry(QRect(80, 250, 131, 31));
        btnMoveJ = new QPushButton(groupBox_4);
        btnMoveJ->setObjectName(QString::fromUtf8("btnMoveJ"));
        btnMoveJ->setGeometry(QRect(170, 290, 121, 31));
        lblUnitCar3 = new QLabel(groupBox_4);
        lblUnitCar3->setObjectName(QString::fromUtf8("lblUnitCar3"));
        lblUnitCar3->setGeometry(QRect(230, 140, 41, 16));
        lblUnitCar3->setFont(font5);
        lblMovRz = new QLabel(groupBox_4);
        lblMovRz->setObjectName(QString::fromUtf8("lblMovRz"));
        lblMovRz->setGeometry(QRect(30, 260, 51, 16));
        lblMovRz->setFont(font5);
        tbxMovePitch = new QTextEdit(groupBox_4);
        tbxMovePitch->setObjectName(QString::fromUtf8("tbxMovePitch"));
        tbxMovePitch->setGeometry(QRect(80, 210, 131, 31));
        lblMovY = new QLabel(groupBox_4);
        lblMovY->setObjectName(QString::fromUtf8("lblMovY"));
        lblMovY->setGeometry(QRect(30, 100, 21, 16));
        lblMovY->setFont(font5);
        tbxMoveX = new QTextEdit(groupBox_4);
        tbxMoveX->setObjectName(QString::fromUtf8("tbxMoveX"));
        tbxMoveX->setGeometry(QRect(80, 50, 131, 31));
        tbxMoveRoll = new QTextEdit(groupBox_4);
        tbxMoveRoll->setObjectName(QString::fromUtf8("tbxMoveRoll"));
        tbxMoveRoll->setGeometry(QRect(80, 170, 131, 31));
        lblUnitCar6 = new QLabel(groupBox_4);
        lblUnitCar6->setObjectName(QString::fromUtf8("lblUnitCar6"));
        lblUnitCar6->setGeometry(QRect(230, 250, 51, 31));
        lblUnitCar6->setFont(font5);
        lblMovRx = new QLabel(groupBox_4);
        lblMovRx->setObjectName(QString::fromUtf8("lblMovRx"));
        lblMovRx->setGeometry(QRect(30, 180, 41, 16));
        lblMovRx->setFont(font5);
        lblMovX = new QLabel(groupBox_4);
        lblMovX->setObjectName(QString::fromUtf8("lblMovX"));
        lblMovX->setGeometry(QRect(30, 60, 21, 16));
        lblMovX->setFont(font5);
        lblMovZ = new QLabel(groupBox_4);
        lblMovZ->setObjectName(QString::fromUtf8("lblMovZ"));
        lblMovZ->setGeometry(QRect(30, 140, 21, 16));
        lblMovZ->setFont(font5);
        lblUnitCar2 = new QLabel(groupBox_4);
        lblUnitCar2->setObjectName(QString::fromUtf8("lblUnitCar2"));
        lblUnitCar2->setGeometry(QRect(230, 100, 41, 16));
        lblUnitCar2->setFont(font5);
        tbxMoveZ = new QTextEdit(groupBox_4);
        tbxMoveZ->setObjectName(QString::fromUtf8("tbxMoveZ"));
        tbxMoveZ->setGeometry(QRect(80, 130, 131, 31));
        lblMovRz_2 = new QLabel(groupBox_4);
        lblMovRz_2->setObjectName(QString::fromUtf8("lblMovRz_2"));
        lblMovRz_2->setGeometry(QRect(10, 300, 71, 16));
        lblMovRz_2->setFont(font5);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        line_2 = new QFrame(tab_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(970, 0, 41, 731));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(5);
        line_2->setFrameShape(QFrame::VLine);
        textBrowserSendData = new QTextBrowser(tab_2);
        textBrowserSendData->setObjectName(QString::fromUtf8("textBrowserSendData"));
        textBrowserSendData->setGeometry(QRect(110, 20, 521, 111));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 40, 61, 21));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 210, 71, 21));
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(110, 160, 371, 392));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        textBrowserReceiveData = new QTextBrowser(layoutWidget2);
        textBrowserReceiveData->setObjectName(QString::fromUtf8("textBrowserReceiveData"));

        verticalLayout_3->addWidget(textBrowserReceiveData);

        tableView = new QTableView(layoutWidget2);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_3->addWidget(tableView);

        pushButtonSave = new QPushButton(tab_2);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(670, 50, 75, 23));
        textBrowserRecFile = new QTextBrowser(tab_2);
        textBrowserRecFile->setObjectName(QString::fromUtf8("textBrowserRecFile"));
        textBrowserRecFile->setGeometry(QRect(570, 170, 256, 161));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(850, 200, 75, 23));
        btnACK = new QPushButton(tab_2);
        btnACK->setObjectName(QString::fromUtf8("btnACK"));
        btnACK->setGeometry(QRect(850, 240, 75, 23));
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1000, 10, 281, 671));
        groupBox->setFont(font2);
        tbxPort = new QTextEdit(groupBox);
        tbxPort->setObjectName(QString::fromUtf8("tbxPort"));
        tbxPort->setGeometry(QRect(20, 190, 251, 41));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 80, 161, 21));
        tbxIPAdress = new QTextEdit(groupBox);
        tbxIPAdress->setObjectName(QString::fromUtf8("tbxIPAdress"));
        tbxIPAdress->setGeometry(QRect(20, 110, 251, 41));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 160, 161, 21));
        btnConnected = new QPushButton(groupBox);
        btnConnected->setObjectName(QString::fromUtf8("btnConnected"));
        btnConnected->setGeometry(QRect(20, 240, 251, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 40, 161, 31));
        label_3->setFont(font3);
        btnQuit = new QPushButton(centralwidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));
        btnQuit->setGeometry(QRect(1000, 690, 281, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1293, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        lblStatusServo->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        btnHome->setText(QCoreApplication::translate("MainWindow", "Home Position", nullptr));
        btnServo->setText(QCoreApplication::translate("MainWindow", "ON Servo", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Motor Control", nullptr));
        btnLoadJob->setText(QCoreApplication::translate("MainWindow", "LOAD JOB", nullptr));
        btnStartJob->setText(QCoreApplication::translate("MainWindow", "START JOB", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Data transfer", nullptr));
        groupBoxCarPulPos->setTitle(QCoreApplication::translate("MainWindow", " Current Position", nullptr));
        lblCurrentRy->setText(QCoreApplication::translate("MainWindow", "Ry", nullptr));
        lblCurrentRz->setText(QCoreApplication::translate("MainWindow", "Rz", nullptr));
        lblCurrentUnitX->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        lblCurrentY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lblCurrentRx->setText(QCoreApplication::translate("MainWindow", "Rx", nullptr));
        label_74->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        label_75->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        lblCurrentZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        lblCurrentUnitZ->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        lblCurrentX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_79->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        lblCurrentUnitY->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        chkcarPulPos->setText(QCoreApplication::translate("MainWindow", "Pulse ", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Multi Points", nullptr));
        btnTeaching->setText(QCoreApplication::translate("MainWindow", "Teaching", nullptr));
        btnPlayback->setText(QCoreApplication::translate("MainWindow", "Play back", nullptr));
        btnClearData->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetPoints->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "X (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetPoints->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Y (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetPoints->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Z (mm)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetPoints->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Rx (deg)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetPoints->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Ry (deg)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetPoints->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Rz (deg)", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "Delete Table", nullptr));
        btnJobExec->setText(QCoreApplication::translate("MainWindow", "JOB EXECUSE", nullptr));
        btnExport->setText(QCoreApplication::translate("MainWindow", "LOAD JOB", nullptr));
        btnX1->setText(QCoreApplication::translate("MainWindow", "X-", nullptr));
        btnX2->setText(QCoreApplication::translate("MainWindow", "X+", nullptr));
        btnY1->setText(QCoreApplication::translate("MainWindow", "Y-", nullptr));
        btnY2->setText(QCoreApplication::translate("MainWindow", "Y+", nullptr));
        tbnZ1->setText(QCoreApplication::translate("MainWindow", "Z-", nullptr));
        btnZ2->setText(QCoreApplication::translate("MainWindow", "Z+", nullptr));
        btnR1->setText(QCoreApplication::translate("MainWindow", "R-", nullptr));
        btnR2->setText(QCoreApplication::translate("MainWindow", "R+", nullptr));
        btnP1->setText(QCoreApplication::translate("MainWindow", "P-", nullptr));
        btnP2->setText(QCoreApplication::translate("MainWindow", "P+", nullptr));
        btnYaw1->setText(QCoreApplication::translate("MainWindow", "Yaw-", nullptr));
        btnYaw2->setText(QCoreApplication::translate("MainWindow", "Yaw+", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Move Joint", nullptr));
        lblUnitCar1->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        lblUnitCar4->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        chkCartesianPos->setText(QCoreApplication::translate("MainWindow", "Cartesian ", nullptr));
        lblUnitCar5->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        tbxMoveY->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2323</p></body></html>", nullptr));
        tbxMovSpeed->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">5</span></p></body></html>", nullptr));
        lblMovRy->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        tbxMoveYaw->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">75633</span></p></body></html>", nullptr));
        btnMoveJ->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        lblUnitCar3->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        lblMovRz->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        tbxMovePitch->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">719</span></p></body></html>", nullptr));
        lblMovY->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        tbxMoveX->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2939</p></body></html>", nullptr));
        tbxMoveRoll->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1045</p></body></html>", nullptr));
        lblUnitCar6->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        lblMovRx->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        lblMovX->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        lblMovZ->setText(QCoreApplication::translate("MainWindow", "U", nullptr));
        lblUnitCar2->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        tbxMoveZ->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">-127</span></p></body></html>", nullptr));
        lblMovRz_2->setText(QCoreApplication::translate("MainWindow", "Speed (%)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Manual", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Send Data", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Receive Data", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("MainWindow", "SAVE JOB", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Load Job", nullptr));
        btnACK->setText(QCoreApplication::translate("MainWindow", "ACK", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Auto", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Page", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Communcation Panel", nullptr));
        tbxPort->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">10040</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP Address", nullptr));
        tbxIPAdress->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">192.168.1.15</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        btnConnected->setText(QCoreApplication::translate("MainWindow", "Connected", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Robot Connection", nullptr));
        btnQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
