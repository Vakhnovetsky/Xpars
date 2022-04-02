#ifndef MYWIDJ_H
#define MYWIDJ_H

#include <QWidget>
#include "myscene.h"

namespace Ui {
    class MyWidj;
}

class MyScene;

class MyWidj : public QWidget {
    Q_OBJECT
public:
    MyWidj(QWidget *parent = 0);
    ~MyWidj();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MyWidj *ui;
    MyScene* scene;

private slots:
    void NameMnemo(const QString& mnemo_n_f);
    void Add_pole(const QString& slang, const int& n_curObj, const int&type_object, const int&subtype_object, const int& type, const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void Zero_n_pole(const int& n);
    void act_paint();
    void SlotOutNumObj(const int& CurNum);
    void SlotOpenEdit(const int& OpenNum);//Отправление номера выделенного объекта в класс Xpars для открытия окна параметров объекта

    void SlotOutPole(const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);

    void SlotDelNumPole(const int & DelNumPole); //Передача номера объекта в класс Xpars для уничтожения поля объекта

    void Slot_KillAllPole();

    void Slot_ShowSetka();

    void SlotPosMouse(const int &x, const int &y);

signals:
    void MnemoSignal(const QString& mnemo_n_f);
    void SignalZero(const int& n);
    void SignalMap(const QString& slang, const int& n_curObj, const int&type_object, const int&subtype_object, const int& type, const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SignalPaint();

    void SignalOutNumObj(const int& CurNum);
    void SignalOpenEdit(const int& OpenNum);
    void SignalOutPole(const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);

    void SignalDelNumPole(const int & DelNumPole); //Передача номера объекта в класс Xpars для уничтожения поля объекта

    void Signal__KillAllPole();

    void Signal_ShowSetka();

    void SignalPosMouse(const int &x, const int &y);
};

#endif // MYWIDJ_H
