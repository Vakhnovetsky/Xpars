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
    int win_num; //����� win
    QString name; //�������� ����������
    QString file; //��� ����� ����������
};

struct g_station
{
    int num; //����� �������
    QString name; //�������� ����������
    QString slang; //�������� �������
    int number; //���������� ����� ������� � ����
    int type; //��� ����������
    int delay; //�������� ��� ������ �������
    int noarch; // 1-�� ������� � �����
    int max_win; //���������� win � �������
    QMap <int, g_win> win;
};

struct ob_win
{
    int win_num; // ����� win, �� ������� ���������� ������
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
    int win_cnt;// ���������� win, �� ������� ����������� �������
    int st_num; // ����� �������, �� ������� ���������� ������
    QMap <int, ob_win> win;
};

struct g_object
{
    int number; //����� �������
    int station; //����� ������� �� ������� ���������� ������
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
    int min_value; //���������� ���������� �������� (��)
    int max_value; //����������� ���������� �������� (��)
    int ring; // ������� ������ ��������� ������� ��� ������ �������� �� ���������� ������� (��)
    int k_value; // ����������� ��������� (��)
    int kou; // ������� ���������� ���������� ������� ������ ���
    int kou2; // ������� ���������� ���������� ������� ������ ���2
    int kds; // ������� ���������� ���������� ������� ������ ���
    int group;  // ����� ���������� ����������, � ������� ������ ������
    int station_cnt; // ���������� �������, �� ������� ����������� ������
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

    void addComboBox(); // ���������� ���� ������� � ���������� ������

    void addTable(int& flow); //���������� ����� � ������� ������� ��������

    void addShop(); //���������� ������ � ������� ��������

    void addTableSV();//���������� ����� � ������� ������� �������

    void OutDateScene(); //�������� ������� �� ��������� QMap pole, �������� ������ � QMap pole, �������� ������� �� ��������� �� �����

    QString Translate(const QString& str);

    int max_st, //���������� ������� � ����� station.cfg
        t_st, //������� �������
        t_win; //����� �������� win

    int n_obj, //���������� �������� � ����� object.cfg
        t_obj; //������� ������

    int st_n,
        stw_n, //������� ����� win � �������
        t_obj_sr; //��� ��������� �������� �������

    int tt_station, tt_win, tt_table_station, tt_num_obj, current_station, current_win;

    int posMouseX, posMouseY; //���������� �����!

    QString mnemo_file_name; //��� ����� �������� ����������
    QString ColorOn, ColorOff; //��������� ����������, ���������� ��� ��������� ������� ��� ������������ ���������� � ��������� �������
    QStringListModel model;

protected:
    void changeEvent(QEvent *e);


private slots:
    void Save_Object(); //������� ��������� ����� Object.cfg
    void Export_Excel();
    void Open(); //�������� ����������
    void Add_Object(); //������� ���������� �������
    void addTableSlot();
    void load_sv();
    void save_sv(); //��������� ������� �������� �� ������� ������ "��������" � ���� ������� ��������

    void ShowObjectPanel(); //��������/������ ���� ������� ��������
    void ShowObjectProp(); //��������/������ ���� ������� �������
    void ShowElementMagazin(); //��������/������ ���� �������� ���������

    void ShowAbout(); //�������� ���� � ���������

    void ShowPalette(); //�������� ������� ��� ������ ����� � ���� ������� ��������

    //����� ������� �� ������ � ���� �������� ���������
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

    void SlotTTNumObj(const int& CurNum); //������� ����� ������� �� MyScene

    void SlotDelNumPole(const int & DelNumPole); //������ ������� �� MyScene ��� ����������� ���� �������

    void SlotOpenEdit(const int& OpenNum); //������ ������� �� MyScene ��� �������� ���������� �������

    //�������� ������� �� MyScene
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
