/********************************************************************************
** Form generated from reading UI file 'dialogfile.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFILE_H
#define UI_DIALOGFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogFile
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QDateTimeEdit *dateTimeEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEditJOBNAME;
    QPushButton *pushButtonOpenFile;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSaveFile;
    QPushButton *pushButtonGetFile;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *DialogFile)
    {
        if (DialogFile->objectName().isEmpty())
            DialogFile->setObjectName(QString::fromUtf8("DialogFile"));
        DialogFile->resize(400, 449);
        horizontalLayout_3 = new QHBoxLayout(DialogFile);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(DialogFile);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        dateTimeEdit = new QDateTimeEdit(groupBox);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setEnabled(false);
        dateTimeEdit->setGeometry(QRect(20, 400, 341, 22));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 350, 339, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEditJOBNAME = new QTextEdit(layoutWidget);
        textEditJOBNAME->setObjectName(QString::fromUtf8("textEditJOBNAME"));

        horizontalLayout_2->addWidget(textEditJOBNAME);

        pushButtonOpenFile = new QPushButton(layoutWidget);
        pushButtonOpenFile->setObjectName(QString::fromUtf8("pushButtonOpenFile"));

        horizontalLayout_2->addWidget(pushButtonOpenFile);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 320, 341, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnSaveFile = new QPushButton(layoutWidget1);
        btnSaveFile->setObjectName(QString::fromUtf8("btnSaveFile"));

        horizontalLayout->addWidget(btnSaveFile);

        pushButtonGetFile = new QPushButton(layoutWidget1);
        pushButtonGetFile->setObjectName(QString::fromUtf8("pushButtonGetFile"));

        horizontalLayout->addWidget(pushButtonGetFile);

        plainTextEdit = new QPlainTextEdit(groupBox);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 30, 341, 281));
        QFont font;
        font.setPointSize(10);
        plainTextEdit->setFont(font);

        horizontalLayout_3->addWidget(groupBox);


        retranslateUi(DialogFile);

        QMetaObject::connectSlotsByName(DialogFile);
    } // setupUi

    void retranslateUi(QDialog *DialogFile)
    {
        DialogFile->setWindowTitle(QCoreApplication::translate("DialogFile", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DialogFile", "JOG ....", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("DialogFile", "yyyy/MM/dd hh:mm ", nullptr));
        textEditJOBNAME->setHtml(QCoreApplication::translate("DialogFile", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">PICK-CONV.JBI</p></body></html>", nullptr));
        pushButtonOpenFile->setText(QCoreApplication::translate("DialogFile", "OPEN FILE ", nullptr));
        btnSaveFile->setText(QCoreApplication::translate("DialogFile", "SAVE FILE TO PC", nullptr));
        pushButtonGetFile->setText(QCoreApplication::translate("DialogFile", "GET FILE FROM CONTROLLER", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogFile: public Ui_DialogFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFILE_H
