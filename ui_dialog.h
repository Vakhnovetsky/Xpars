/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Wed 12. Apr 17:20:06 2017
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label_6;
    QPushButton *pushButton_add;
    QLabel *label_4;
    QGroupBox *groupBox_TS;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_kptson;
    QLineEdit *lineEdit_tson;
    QLineEdit *lineEdit_kptsoff;
    QLineEdit *lineEdit_tsoff;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_2;
    QLabel *label_5;
    QGroupBox *groupBox;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *lineEdit_kptuon;
    QLabel *label_16;
    QLineEdit *lineEdit_tu1on;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *lineEdit_kptuoff;
    QLineEdit *lineEdit_tstuon;
    QLabel *label_20;
    QLineEdit *lineEdit_tu2on;
    QLabel *label_21;
    QLabel *label_23;
    QLabel *label_19;
    QLineEdit *lineEdit_tstuoff;
    QLineEdit *lineEdit_tu2off;
    QLineEdit *lineEdit_tu1off;
    QLabel *label_22;
    QLabel *label_3;
    QLineEdit *lineEdit_type;
    QLabel *label_7;
    QLineEdit *lineEdit_slang;
    QPushButton *pushButton_cancel;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_line;
    QLabel *label;
    QGroupBox *groupBox_2;
    QLabel *label_24;
    QLineEdit *lineEdit_min_value;
    QLabel *label_25;
    QLineEdit *lineEdit_max_value;
    QLineEdit *lineEdit_k_value;
    QLabel *label_26;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_group;
    QCheckBox *checkBox_kou;
    QCheckBox *checkBox_kds;
    QLabel *label_27;
    QLineEdit *lineEdit_station;
    QLineEdit *lineEdit_ring;
    QLineEdit *lineEdit_subtype;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(423, 340);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(270, 40, 41, 21));
        pushButton_add = new QPushButton(Dialog);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setGeometry(QRect(120, 310, 75, 23));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(100, 40, 21, 21));
        groupBox_TS = new QGroupBox(Dialog);
        groupBox_TS->setObjectName(QString::fromUtf8("groupBox_TS"));
        groupBox_TS->setGeometry(QRect(220, 70, 191, 111));
        label_8 = new QLabel(groupBox_TS);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 71, 16));
        label_9 = new QLabel(groupBox_TS);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(120, 20, 71, 16));
        lineEdit_kptson = new QLineEdit(groupBox_TS);
        lineEdit_kptson->setObjectName(QString::fromUtf8("lineEdit_kptson"));
        lineEdit_kptson->setGeometry(QRect(30, 50, 31, 20));
        lineEdit_tson = new QLineEdit(groupBox_TS);
        lineEdit_tson->setObjectName(QString::fromUtf8("lineEdit_tson"));
        lineEdit_tson->setGeometry(QRect(30, 80, 31, 20));
        lineEdit_kptsoff = new QLineEdit(groupBox_TS);
        lineEdit_kptsoff->setObjectName(QString::fromUtf8("lineEdit_kptsoff"));
        lineEdit_kptsoff->setGeometry(QRect(150, 50, 31, 20));
        lineEdit_tsoff = new QLineEdit(groupBox_TS);
        lineEdit_tsoff->setObjectName(QString::fromUtf8("lineEdit_tsoff"));
        lineEdit_tsoff->setGeometry(QRect(150, 80, 31, 20));
        label_10 = new QLabel(groupBox_TS);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 50, 21, 21));
        label_11 = new QLabel(groupBox_TS);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 80, 21, 21));
        label_12 = new QLabel(groupBox_TS);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(120, 50, 21, 21));
        label_13 = new QLabel(groupBox_TS);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(120, 80, 21, 21));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 10, 31, 21));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 40, 41, 21));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 70, 191, 171));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 20, 71, 16));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(120, 50, 21, 21));
        lineEdit_kptuon = new QLineEdit(groupBox);
        lineEdit_kptuon->setObjectName(QString::fromUtf8("lineEdit_kptuon"));
        lineEdit_kptuon->setGeometry(QRect(30, 50, 31, 20));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(120, 20, 71, 16));
        lineEdit_tu1on = new QLineEdit(groupBox);
        lineEdit_tu1on->setObjectName(QString::fromUtf8("lineEdit_tu1on"));
        lineEdit_tu1on->setGeometry(QRect(30, 80, 31, 20));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 50, 21, 21));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 80, 21, 21));
        lineEdit_kptuoff = new QLineEdit(groupBox);
        lineEdit_kptuoff->setObjectName(QString::fromUtf8("lineEdit_kptuoff"));
        lineEdit_kptuoff->setGeometry(QRect(150, 50, 31, 20));
        lineEdit_tstuon = new QLineEdit(groupBox);
        lineEdit_tstuon->setObjectName(QString::fromUtf8("lineEdit_tstuon"));
        lineEdit_tstuon->setGeometry(QRect(30, 110, 31, 20));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 110, 21, 21));
        lineEdit_tu2on = new QLineEdit(groupBox);
        lineEdit_tu2on->setObjectName(QString::fromUtf8("lineEdit_tu2on"));
        lineEdit_tu2on->setGeometry(QRect(30, 140, 31, 20));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 140, 21, 21));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(120, 110, 21, 21));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(120, 80, 21, 21));
        lineEdit_tstuoff = new QLineEdit(groupBox);
        lineEdit_tstuoff->setObjectName(QString::fromUtf8("lineEdit_tstuoff"));
        lineEdit_tstuoff->setGeometry(QRect(150, 110, 31, 20));
        lineEdit_tu2off = new QLineEdit(groupBox);
        lineEdit_tu2off->setObjectName(QString::fromUtf8("lineEdit_tu2off"));
        lineEdit_tu2off->setGeometry(QRect(150, 140, 31, 20));
        lineEdit_tu1off = new QLineEdit(groupBox);
        lineEdit_tu1off->setObjectName(QString::fromUtf8("lineEdit_tu1off"));
        lineEdit_tu1off->setGeometry(QRect(150, 80, 31, 20));
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(120, 140, 21, 21));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 51, 21));
        lineEdit_type = new QLineEdit(Dialog);
        lineEdit_type->setObjectName(QString::fromUtf8("lineEdit_type"));
        lineEdit_type->setGeometry(QRect(120, 40, 31, 20));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(350, 40, 31, 21));
        lineEdit_slang = new QLineEdit(Dialog);
        lineEdit_slang->setObjectName(QString::fromUtf8("lineEdit_slang"));
        lineEdit_slang->setGeometry(QRect(250, 10, 161, 20));
        pushButton_cancel = new QPushButton(Dialog);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(220, 310, 75, 23));
        lineEdit_name = new QLineEdit(Dialog);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(40, 10, 161, 20));
        lineEdit_line = new QLineEdit(Dialog);
        lineEdit_line->setObjectName(QString::fromUtf8("lineEdit_line"));
        lineEdit_line->setGeometry(QRect(310, 40, 31, 20));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 31, 21));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 180, 191, 61));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 20, 21, 21));
        lineEdit_min_value = new QLineEdit(groupBox_2);
        lineEdit_min_value->setObjectName(QString::fromUtf8("lineEdit_min_value"));
        lineEdit_min_value->setGeometry(QRect(30, 20, 31, 20));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(70, 20, 21, 21));
        lineEdit_max_value = new QLineEdit(groupBox_2);
        lineEdit_max_value->setObjectName(QString::fromUtf8("lineEdit_max_value"));
        lineEdit_max_value->setGeometry(QRect(90, 20, 31, 20));
        lineEdit_k_value = new QLineEdit(groupBox_2);
        lineEdit_k_value->setObjectName(QString::fromUtf8("lineEdit_k_value"));
        lineEdit_k_value->setGeometry(QRect(150, 20, 31, 20));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(130, 20, 21, 21));
        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 240, 401, 61));
        lineEdit_group = new QLineEdit(groupBox_3);
        lineEdit_group->setObjectName(QString::fromUtf8("lineEdit_group"));
        lineEdit_group->setGeometry(QRect(160, 30, 31, 20));
        checkBox_kou = new QCheckBox(groupBox_3);
        checkBox_kou->setObjectName(QString::fromUtf8("checkBox_kou"));
        checkBox_kou->setGeometry(QRect(20, 30, 70, 21));
        checkBox_kds = new QCheckBox(groupBox_3);
        checkBox_kds->setObjectName(QString::fromUtf8("checkBox_kds"));
        checkBox_kds->setGeometry(QRect(90, 30, 70, 21));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(200, 30, 21, 21));
        lineEdit_station = new QLineEdit(Dialog);
        lineEdit_station->setObjectName(QString::fromUtf8("lineEdit_station"));
        lineEdit_station->setGeometry(QRect(60, 40, 31, 20));
        lineEdit_ring = new QLineEdit(Dialog);
        lineEdit_ring->setObjectName(QString::fromUtf8("lineEdit_ring"));
        lineEdit_ring->setGeometry(QRect(380, 40, 31, 20));
        lineEdit_subtype = new QLineEdit(Dialog);
        lineEdit_subtype->setObjectName(QString::fromUtf8("lineEdit_subtype"));
        lineEdit_subtype->setGeometry(QRect(210, 40, 31, 20));

        retranslateUi(Dialog);
        QObject::connect(pushButton_add, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "\320\233\320\270\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        pushButton_add->setText(QApplication::translate("Dialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "\320\242\320\270\320\277", 0, QApplication::UnicodeUTF8));
        groupBox_TS->setTitle(QApplication::translate("Dialog", "\320\241\320\270\320\263\320\275\320\260\320\273\321\213 \320\242\320\241", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "\320\222\320\232\320\233\320\256\320\247\320\225\320\235\320\236", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Dialog", "\320\236\320\242\320\232\320\233\320\256\320\247\320\225\320\235\320\236", 0, QApplication::UnicodeUTF8));
        lineEdit_kptson->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_tson->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_kptsoff->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_tsoff->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "\320\232\320\237", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Dialog", "\320\242\320\241", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Dialog", "\320\232\320\237", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Dialog", "\320\242\320\241", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "\320\241\320\273\320\265\320\275\320\263", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "\320\237\320\276\320\264\321\202\320\270\320\277", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "\320\241\320\270\320\263\320\275\320\260\320\273\321\213 \320\242\320\243", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Dialog", "\320\222\320\232\320\233\320\256\320\247\320\230\320\242\320\254", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Dialog", "\320\232\320\237", 0, QApplication::UnicodeUTF8));
        lineEdit_kptuon->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Dialog", "\320\236\320\242\320\232\320\233\320\256\320\247\320\230\320\242\320\254", 0, QApplication::UnicodeUTF8));
        lineEdit_tu1on->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Dialog", "\320\232\320\237", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("Dialog", "\320\242\320\2431", 0, QApplication::UnicodeUTF8));
        lineEdit_kptuoff->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_tstuon->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("Dialog", "\320\242\320\241", 0, QApplication::UnicodeUTF8));
        lineEdit_tu2on->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("Dialog", "\320\242\320\2432", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("Dialog", "\320\242\320\241", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("Dialog", "\320\242\320\2431", 0, QApplication::UnicodeUTF8));
        lineEdit_tstuoff->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_tu2off->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_tu1off->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("Dialog", "\320\242\320\2432", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "\320\241\321\202\320\260\320\275\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        lineEdit_type->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Dialog", "\320\227\320\262\321\203\320\272", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        lineEdit_line->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "\320\230\320\274\321\217", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\320\241\320\270\320\263\320\275\320\260\320\273\321\213 \320\242\320\230", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("Dialog", "Min", 0, QApplication::UnicodeUTF8));
        lineEdit_min_value->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("Dialog", "Max", 0, QApplication::UnicodeUTF8));
        lineEdit_max_value->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_k_value->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("Dialog", "k_v", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("Dialog", "\320\237\321\200\320\270\320\267\320\275\320\260\320\272\320\270", 0, QApplication::UnicodeUTF8));
        lineEdit_group->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        checkBox_kou->setText(QApplication::translate("Dialog", "\320\232\320\236\320\243", 0, QApplication::UnicodeUTF8));
        checkBox_kds->setText(QApplication::translate("Dialog", "\320\232\320\224\320\241", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("Dialog", "\320\223\320\240\320\237", 0, QApplication::UnicodeUTF8));
        lineEdit_station->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_ring->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
        lineEdit_subtype->setText(QApplication::translate("Dialog", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
