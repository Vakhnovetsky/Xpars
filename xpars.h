#ifndef XPARS_H
#define XPARS_H

#include <QMainWindow>
#include <QtXml>
#include "mywidj.h"
#include "dialog.h"
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QStringListModel>

struct g_win
{
    int win_num; //Номер win
    QString name; //Название мнемосхемы
    QString file; //Имя файла мнемосхемы
};

struct g_station
{
    int num; //Номер станции
    QString name; //Название подстанции
    QString slang; //Название станции
    int number; //Порядковый номер станции в меню
    int type; //Тип подстанции
    int delay; //Задержка для выдачи команды
    int noarch; // 1-не пишутся в архив
    int max_win; //Количество win у станции
    QMap <int, g_win> win;
};

struct ob_win
{
    int win_num; // Номер win, на котором расположен объект
    int type;
    int X;
    int Y;
    int W;
    int H;
    int im_X;
    int im_Y;
    int im_W;
    int im_H;
    int font;
    QString color_on;
    QString color_off;
};

struct ob_st
{
    int win_cnt;// количество win, на которых расположены объекты
    int st_num; // Номер станции, на котором расположен объект
    QMap <int, ob_win> win;
};

struct g_object
{
    int number; //Номер объекта
    int station; //Номер станции на которой расположен объект
    QString name;
    QString slang;
    int type;
    int subtype;
    int line;
    int kptsoff;
    int tsoff;
    int kptson;
    int tson;
    int kptuon;
    int tu1on;
    int tu2on;
    int tstuon;
    int kptuoff;
    int tu1off;
    int tu2off;
    int tstuoff;
    int min_value; //минимально домустимое значение (ТИ)
    int max_value; //максимально допустимое значение (ТИ)
    int ring; // признак выдачи звукового сигнала при выходе значения за допустимые пределы (ТИ)
    int k_value; // коэффициент пересчета (ТИ)
    int kou; // признак блокировки управления объктом кномки КОУ
    int kou2; // признак блокировки управления объктом кномки КОУ2
    int kds; // признак блокировки управления объктом кномки КДС
    int group;  // номер группового управления, в которую входит объект
    int station_cnt; // количество станций, на которых расположены объект
    QMap <int, ob_st> st;
};

struct g_stativ_cfg
{
    int kp_log_number;
    int kp_fiz1_number;
    int kp_fiz2_number;
    int TS;
    int TU;
    int TI;
};

struct g_kp_cfg
{
    int telemehanika;
    int num_stativ;
    QString port1;
    QString port2;
    QString port3;
    QString port4;
    int speed;
    int chotnost;
    int stopbit;
    int amount_kp;
    QMap <int, g_stativ_cfg> stativ;
};



namespace Ui {
    class Xpars;
}

class QTextCodec;
class MyWidj;
class Dialog;


class Xpars : public QMainWindow
{
    Q_OBJECT
public:
    Xpars(QWidget *parent = 0);
    ~Xpars();

    void load_stations();
    void parseEntry(const QDomElement & elt);

    void load_object();
    void parseObjEntry(const QDomElement & elt);

    void load_stativ();

    void zeroing();

    void addComboBox(); // Добавление имен станций в выпадающий список

    void addTable(int& flow); //Добавление ячеек в таблицу Перечня объектов

    void addShop(); //Добавление кнопок в магазин объектов

    void addTableSV();//Добавление ячеек в таблицу свойств объекта

    void OutDateScene(); //Отправка сигнала на обнуление QMap pole, отправка данных в QMap pole, отправка сигнала на нарисовку на сцене

    QString Translate(const QString& str);

    int max_st, //Количество станций в файле station.cfg
        t_st, //Текущая станция
        t_win; //Номер текущего win

    int n_obj, //Количество объектов в файле object.cfg
        t_obj; //Текущий объект

    int st_n,
        stw_n, //Текущий номер win в объекте
        t_obj_sr; //Для сравнения текущего объекта

    int tt_station, tt_win, tt_table_station, tt_num_obj, current_station, current_win;

    int posMouseX, posMouseY; //Координаты мышки!

    QString mnemo_file_name; //Имя файла открытой мнемосхемы
    QString ColorOn, ColorOff; //Временные переменные, получаемые при изменении палитры для последующего сохранения в свойствах объекта
    QStringListModel model;

protected:
    void changeEvent(QEvent *e);


private slots:
    void Save_Object(); //Функция сохраненя файла Object.cfg
    void Export_Excel();
    void Open(); //Открытие мнемосхемы
    void Add_Object(); //Функция добавления объекта
    void addTableSlot();
    void load_sv();
    void save_sv(); //Изменение свойств объектов по нажатию кнопки "Изменить" в окне свойств объектов

    void ShowObjectPanel(); //Показать/скрыть окно перечня объектов
    void ShowObjectProp(); //Показать/скрыть окно свойств объекта
    void ShowElementMagazin(); //Показать/скрыть окно магазина элементов

    void ShowAbout(); //Показать окно о программе

    void ShowPalette(); //Показать палитру для выбора цвета в окне свойств объектов

    //Слоты нажатия на кнопки в окне магазина элементов
    void PushButton_TU();
    void PushButton_ZAZ();
    void PushButton_RUB_G();
    void PushButton_RUB_V();
    void PushButton_RUB1_G();
    void PushButton_RUB1_V();
    void PushButton_U_TXT();
    void PushButton_OUT();
    void PushButton_F_BUT();
    void PushButton_NF_BUT();
    void PushButton_LAMP();
    void PushButton_RECT();
    void PushButton_RECT4();
    void PushButton_T_RECT();
    void PushButton_TXT();
    void PushButton_OUT_TM();
    void PushButton_NEXT();
    void PushButton_PREV();
    void PushButton_UP_W();
    void PushButton_DOWN_W();
    void PushButton_STATION();
    void PushButton_SHOW_L();
    void PushButton_HIDE_T();
    void PushButton_RECTM();
    void PushButton_SIGNAL_M();
    void PushButton_STATION_P();

    void NewPole(const int& type);

    void SlotTTNumObj(const int& CurNum); //Текущий номер объекта из MyScene

    void SlotDelNumPole(const int & DelNumPole); //Номера объекта из MyScene для уничтожения поля объекта

    void SlotOpenEdit(const int& OpenNum); //Номера объекта из MyScene для открытия параметров объекта

    //свойства объекта из MyScene
    void SlotOutPole(const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);

    void KillAllPole();

    void Slot_notShowSetka();

    void SlotPosMouse(const int& x, const int& y);


private:
    QTextCodec *rc;
    Ui::Xpars *ui;
    //Ui::Xpars ui;


    MyWidj *MyW;
    Dialog *ww;

    QMap <int, g_station> station;

    QMap <int, g_object> object;

    QMap <int, g_kp_cfg> kp_cfg;

    QLabel* status_obj;
    QLabel* status_st;
    QLabel* status_X_obj, *status_Y_obj;
    QLCDNumber* status_objd, *status_std;
    QLabel* status_tt_obj, *status_tt_num;
    QPushButton *Button_TU, *Button_ZAZ, *Button_RUB_G, *Button_RUB_V, *Button_RUB1_G, *Button_RUB1_V, *Button_U_TXT, *Button_F_BUT, *Button_NF_BUT, *Button_LAMP, *Button_RECT, *Button_RECT4, *Button_T_RECT, *Button_TXT, *Button_OUT, *Button_OUT_TM;
    QLabel* status_PosMouse;

    int flag_openEdit;

protected:
    /*virtual*/ void paintEvent(QPaintEvent* pe);

signals:
    void MnemoSignal(const QString& mnemo_n_f);
    void SignalZero(const int& n);
    void SignalMap(const QString& slang, const int& n_curObj, const int&type_object, const int&subtype_object, const int& type, const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SignalPaint();
    void signal_KillAllPole();
};

#endif // XPARS_H
