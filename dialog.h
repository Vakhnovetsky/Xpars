#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "xpars.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    int getStation();
    QString getName();
    QString getSlang();
    int getType();
    int getSubtype();
    int getLine();

    int getKptsoff();
    int getTsoff();
    int getKptson();
    int getTson();
    int getKptuon();
    int getTu1on();
    int getTu2on();
    int getTstuon();
    int getKptuoff();

    int getTu1off();
    int getTu2off();
    int getTstuoff();
    int getMin_value();
    int getMax_value();
    int getRing();
    int getK_value();
    int getKou();
    int getKds();
    int getGroup();


    void outStation(int &Station);
    void outName(QString &Name);
    void outSlang(QString &Slang);
    void outType(int &Type);
    void outSubtype(int &Subtype);
    void outLine(int &Line);

    void outKptsoff(int &Kptsoff);
    void outTsoff(int &Tsoff);
    void outKptson(int &Kptson);
    void outTson(int &Tson);
    void outKptuon(int &Kptuon);
    void outTu1on(int &Tu1on);
    void outTu2on(int &Tu2on);
    void outTstuon(int &Tstuon);
    void outKptuoff(int &Kptuoff);

    void outTu1off(int &Tu1off);
    void outTu2off(int &Tu2off);
    void outTstuoff(int &Tstuoff);
    void outMin_value(int &Min_value);
    void outMax_value(int &Max_value);
    void outRing(int &Ring);
    void outK_value(int &K_value);
    void outKou(int &Kou);
    void outKds(int &Kds);
    void outGroup(int &Group);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
