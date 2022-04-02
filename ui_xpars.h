/********************************************************************************
** Form generated from reading UI file 'xpars.ui'
**
** Created: Wed 27. Dec 13:18:46 2017
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPARS_H
#define UI_XPARS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Xpars
{
public:
    QAction *action_open;
    QAction *action_save;
    QAction *action_add_object;
    QAction *action_close;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_Excel;
    QAction *action_kill_all_pole;
    QAction *action_kill_all_pole_2;
    QAction *action_setka;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton;

    void setupUi(QMainWindow *Xpars)
    {
        if (Xpars->objectName().isEmpty())
            Xpars->setObjectName(QString::fromUtf8("Xpars"));
        Xpars->resize(1171, 1052);
        Xpars->setMouseTracking(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8("release/logo_niivk.gif"), QSize(), QIcon::Normal, QIcon::Off);
        Xpars->setWindowIcon(icon);
        action_open = new QAction(Xpars);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        action_save = new QAction(Xpars);
        action_save->setObjectName(QString::fromUtf8("action_save"));
        action_add_object = new QAction(Xpars);
        action_add_object->setObjectName(QString::fromUtf8("action_add_object"));
        action_close = new QAction(Xpars);
        action_close->setObjectName(QString::fromUtf8("action_close"));
        action = new QAction(Xpars);
        action->setObjectName(QString::fromUtf8("action"));
        action->setCheckable(false);
        action->setChecked(false);
        action_2 = new QAction(Xpars);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_2->setCheckable(false);
        action_2->setChecked(false);
        action_3 = new QAction(Xpars);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_3->setCheckable(false);
        action_3->setChecked(false);
        action_4 = new QAction(Xpars);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_Excel = new QAction(Xpars);
        action_Excel->setObjectName(QString::fromUtf8("action_Excel"));
        action_kill_all_pole = new QAction(Xpars);
        action_kill_all_pole->setObjectName(QString::fromUtf8("action_kill_all_pole"));
        action_kill_all_pole_2 = new QAction(Xpars);
        action_kill_all_pole_2->setObjectName(QString::fromUtf8("action_kill_all_pole_2"));
        action_kill_all_pole_2->setCheckable(false);
        action_kill_all_pole_2->setEnabled(true);
        action_setka = new QAction(Xpars);
        action_setka->setObjectName(QString::fromUtf8("action_setka"));
        centralWidget = new QWidget(Xpars);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Xpars->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Xpars);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1171, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        Xpars->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Xpars);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Xpars->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Xpars);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Xpars->setStatusBar(statusBar);
        dockWidget_3 = new QDockWidget(Xpars);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidget_3->setMinimumSize(QSize(390, 78));
        dockWidget_3->setMaximumSize(QSize(390, 78));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        dockWidget_3->setWidget(dockWidgetContents_3);
        Xpars->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_3);
        dockWidget = new QDockWidget(Xpars);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setEnabled(true);
        dockWidget->setMinimumSize(QSize(455, 500));
        dockWidget->setMaximumSize(QSize(455, 1000));
        dockWidget->setWindowIcon(icon);
        dockWidget->setFloating(false);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        tableWidget = new QTableWidget(dockWidgetContents);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(0, 30, 455, 500));
        tableWidget->setMinimumSize(QSize(455, 500));
        tableWidget->setMaximumSize(QSize(455, 969));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        comboBox = new QComboBox(dockWidgetContents);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(0, 0, 171, 22));
        dockWidget->setWidget(dockWidgetContents);
        Xpars->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);
        dockWidget_2 = new QDockWidget(Xpars);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidget_2->setEnabled(true);
        dockWidget_2->setMinimumSize(QSize(175, 410));
        dockWidget_2->setMaximumSize(QSize(175, 410));
        dockWidget_2->setFloating(false);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        tableWidget_2 = new QTableWidget(dockWidgetContents_2);
        if (tableWidget_2->columnCount() < 1)
            tableWidget_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        if (tableWidget_2->rowCount() < 11)
            tableWidget_2->setRowCount(11);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(8, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(9, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(10, __qtablewidgetitem15);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 0, 174, 357));
        tableWidget_2->setMinimumSize(QSize(174, 357));
        tableWidget_2->setMaximumSize(QSize(174, 356));
        QFont font;
        font.setKerning(false);
        tableWidget_2->setFont(font);
        tableWidget_2->setRowCount(11);
        pushButton = new QPushButton(dockWidgetContents_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 360, 75, 23));
        dockWidget_2->setWidget(dockWidgetContents_2);
        Xpars->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action_open);
        menu->addAction(action_save);
        menu->addAction(action_Excel);
        menu->addAction(action_close);
        menu_2->addAction(action);
        menu_2->addAction(action_2);
        menu_2->addAction(action_3);
        menu_2->addAction(action_setka);
        menu_3->addAction(action_add_object);
        menu_3->addAction(action_kill_all_pole_2);
        menu_4->addAction(action_4);

        retranslateUi(Xpars);

        QMetaObject::connectSlotsByName(Xpars);
    } // setupUi

    void retranslateUi(QMainWindow *Xpars)
    {
        Xpars->setWindowTitle(QApplication::translate("Xpars", "Xpars", 0, QApplication::UnicodeUTF8));
        action_open->setText(QApplication::translate("Xpars", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_save->setText(QApplication::translate("Xpars", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_add_object->setText(QApplication::translate("Xpars", "\320\235\320\276\320\262\321\213\320\271 \320\276\320\261\321\212\320\265\320\272\321\202", 0, QApplication::UnicodeUTF8));
        action_close->setText(QApplication::translate("Xpars", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("Xpars", "\320\237\320\265\321\200\320\265\321\207\320\265\320\275\321\214 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("Xpars", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("Xpars", "\320\234\320\260\320\263\320\260\320\267\320\270\320\275 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("Xpars", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0, QApplication::UnicodeUTF8));
        action_Excel->setText(QApplication::translate("Xpars", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \321\202\320\265\320\263\320\276\320\262 \320\262 csv", 0, QApplication::UnicodeUTF8));
        action_kill_all_pole->setText(QApplication::translate("Xpars", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\274\320\275\320\265\320\274\320\276\321\201\321\205\320\265\320\274\321\203", 0, QApplication::UnicodeUTF8));
        action_kill_all_pole_2->setText(QApplication::translate("Xpars", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\274\320\275\320\265\320\274\320\276\321\201\321\205\320\265\320\274\321\203", 0, QApplication::UnicodeUTF8));
        action_setka->setText(QApplication::translate("Xpars", "\320\241\320\265\321\202\320\272\320\260", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("Xpars", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("Xpars", "\320\222\320\270\320\264", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("Xpars", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("Xpars", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        dockWidget_3->setWindowTitle(QApplication::translate("Xpars", "\320\234\320\260\320\263\320\260\320\267\320\270\320\275 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("Xpars", "\320\237\320\265\321\200\320\265\321\207\320\265\320\275\321\214 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Xpars", "\320\230\320\274\321\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Xpars", "\320\242\320\270\320\277", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Xpars", "\320\241\321\202\320\260\320\275\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Xpars", "\320\235\320\276\320\274\320\265\321\200", 0, QApplication::UnicodeUTF8));
        dockWidget_2->setWindowTitle(QApplication::translate("Xpars", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("Xpars", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("Xpars", "\320\250\320\270\321\200\320\270\320\275\320\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("Xpars", "\320\222\321\213\321\201\320\276\321\202\320\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("Xpars", "\320\250\320\270\321\200\320\270\320\275\320\260 im", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("Xpars", "\320\222\321\213\321\201\320\276\321\202\320\260 im", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("Xpars", "X", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->verticalHeaderItem(5);
        ___qtablewidgetitem10->setText(QApplication::translate("Xpars", "Y", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->verticalHeaderItem(6);
        ___qtablewidgetitem11->setText(QApplication::translate("Xpars", "X im", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->verticalHeaderItem(7);
        ___qtablewidgetitem12->setText(QApplication::translate("Xpars", "Y im", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->verticalHeaderItem(8);
        ___qtablewidgetitem13->setText(QApplication::translate("Xpars", "\320\250\321\200\320\270\321\204\321\202", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->verticalHeaderItem(9);
        ___qtablewidgetitem14->setText(QApplication::translate("Xpars", "\320\246\320\262\320\265\321\202 \320\262\320\272\320\273", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->verticalHeaderItem(10);
        ___qtablewidgetitem15->setText(QApplication::translate("Xpars", "\320\246\320\262\320\265\321\202 \320\276\321\202\320\272\320\273", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Xpars", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Xpars: public Ui_Xpars {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPARS_H
