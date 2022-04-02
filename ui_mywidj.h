/********************************************************************************
** Form generated from reading UI file 'mywidj.ui'
**
** Created: Wed 27. Dec 13:18:46 2017
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDJ_H
#define UI_MYWIDJ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidj
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QWidget *MyWidj)
    {
        if (MyWidj->objectName().isEmpty())
            MyWidj->setObjectName(QString::fromUtf8("MyWidj"));
        MyWidj->resize(1010, 686);
        MyWidj->setMaximumSize(QSize(1010, 686));
        MyWidj->setMouseTracking(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8("release/logo_niivk.gif"), QSize(), QIcon::Normal, QIcon::Off);
        MyWidj->setWindowIcon(icon);
        graphicsView = new QGraphicsView(MyWidj);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1008, 685));
        graphicsView->setMinimumSize(QSize(1008, 685));
        graphicsView->setMaximumSize(QSize(1008, 685));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        retranslateUi(MyWidj);

        QMetaObject::connectSlotsByName(MyWidj);
    } // setupUi

    void retranslateUi(QWidget *MyWidj)
    {
        MyWidj->setWindowTitle(QApplication::translate("MyWidj", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyWidj: public Ui_MyWidj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDJ_H
