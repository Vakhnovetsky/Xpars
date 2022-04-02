#include "xpars.h"
#include "ui_xpars.h"
#include <QtGui>
#include <QtXml>
#include <QMap>
#include <QTextCodec>
#include "dialog.h"
#include "ui_dialog.h"
#include "mywidj.h"
#include <QProgressDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QtDebug>
#include <QLocale>

#define P_TEXT(aaa) QTextCodec::codecForName("KOI8-R")->toUnicode(aaa);

Xpars::Xpars(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Xpars)
{
    rc = QTextCodec::codecForName("Windows-1251");
    QTextCodec::setCodecForCStrings(rc);

    ui->setupUi(this);

    load_stations();

    load_object();

    addComboBox();

    addShop();

    flag_openEdit = 0; //Флаг количества открытых окон "Параметры объекта"

    MyW = new MyWidj(this);
    setCentralWidget(MyW);

    connect(this, SIGNAL(MnemoSignal(const QString &)), MyW, SLOT(NameMnemo(const QString&)));


    connect(this, SIGNAL(SignalZero(int)), MyW, SLOT(Zero_n_pole(int)));
    connect(this, SIGNAL(SignalMap(QString, int, int, int, int, int, int, int, int, int, int, int, int, int, QString, QString)), MyW, SLOT(Add_pole(QString, int, int, int, int, int, int, int, int, int, int, int, int, int, QString, QString)));

    connect(this, SIGNAL(SignalPaint()), MyW, SLOT(act_paint()));
    connect(this, SIGNAL(signal_KillAllPole()), MyW, SLOT(Slot_KillAllPole()));
    connect(MyW, SIGNAL(SignalOutNumObj(int)), this, SLOT(SlotTTNumObj(int)));
    connect(MyW, SIGNAL(SignalOutPole(int,int,int,int,int,int,int,int,int,QString,QString)), this, SLOT(SlotOutPole(int,int,int,int,int,int,int,int,int,QString,QString)));
    connect(MyW, SIGNAL(SignalDelNumPole(int)), this, SLOT(SlotDelNumPole(int)));
    connect(MyW, SIGNAL(SignalOpenEdit(int)), this, SLOT(SlotOpenEdit(int))); //Отправление номера выделенного объекта в класс Xpars для открытия окна параметров объекта
    connect(MyW, SIGNAL(SignalPosMouse(int, int)), this, SLOT (SlotPosMouse(int, int)));

    connect(ui->action_open, SIGNAL(activated()), this, SLOT(Open()));
    connect(ui->action_save, SIGNAL(activated()), this, SLOT(Save_Object()));
    connect(ui->action_Excel, SIGNAL(activated()), this, SLOT(Export_Excel()));
    connect(ui->action_close, SIGNAL(activated()), this, SLOT(close()));
    connect(ui->action_add_object, SIGNAL(activated()), this, SLOT(Add_Object()));

    connect(ui->action_kill_all_pole_2, SIGNAL(activated()), this, SLOT(KillAllPole()));

    connect(ui->action, SIGNAL(activated()), this, SLOT(ShowObjectPanel()));
    connect(ui->action_2, SIGNAL(activated()), this, SLOT(ShowObjectProp()));
    connect(ui->action_3, SIGNAL(activated()), this, SLOT(ShowElementMagazin()));
    connect(ui->action_setka, SIGNAL(activated()), MyW, SLOT(Slot_ShowSetka()));
    connect(ui->action_4, SIGNAL(activated()), this, SLOT(ShowAbout()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(addTableSlot()));
    connect(ui->tableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(load_sv()));
    connect(ui->tableWidget_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ShowPalette()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(save_sv()));

    status_st = new QLabel(this);
    status_st->setText("Количество станций: ");
    statusBar()->addWidget(status_st);

    status_std = new QLCDNumber(this);
    status_std->display(max_st);
    statusBar()->addWidget(status_std);


    status_obj = new QLabel(this);
    status_obj->setText("Количество объектов ");
    statusBar()->addWidget(status_obj);


    status_objd = new QLCDNumber(this);
    status_objd->display(n_obj);
    statusBar()->addWidget(status_objd);


    status_tt_num = new QLabel(this);
    status_tt_num->setText("Объект не выбран");
    statusBar()->addWidget(status_tt_num);


    status_tt_obj = new QLabel(this);
    status_tt_obj->setText("  ");
    statusBar()->addWidget(status_tt_obj);

    status_X_obj = new QLabel(this);
    status_X_obj->setText("");
    statusBar()->addWidget(status_X_obj);

    status_Y_obj = new QLabel(this);
    status_Y_obj->setText("");
    statusBar()->addWidget(status_Y_obj);

    status_PosMouse = new QLabel(this);
    status_PosMouse->setText("                   (" + QString::number(0) + ";" + QString::number(0) + ")                   ");
    statusBar()->addWidget(status_PosMouse);

    setWindowIcon(QIcon("logo_niivk.gif"));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resize(1500,830);
}

Xpars::~Xpars()
{
    delete ui;
}

void Xpars::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Xpars::zeroing()
{
    int i;

    tt_station=-1; //текущая станция
    tt_win=-1; //текущая мнемосхема
    tt_table_station = 0; //текущая станция для перечня объектов

    current_station = -1;
    current_win = -1;

    ColorOn = "";
    ColorOff = "";

    t_obj = 0; //Текущий ключ объекта (№ объекта ключ+1)

    stw_n = 0; //Текущий номер win в объекте, ключ!!!!

    g_object temp;

    for (i=0; i<n_obj; i++)
    {
        temp.number = 0;
        temp.station = 0;
        temp.name = "";
        temp.slang = "";
        temp.type = 0;
        temp.subtype = 0;
        temp.line = 0;
        temp.kptsoff = 0;
        temp.tsoff = 0;
        temp.kptson = 0;
        temp.tson = 0;
        temp.kptuon = 0;
        temp.tu1on = 0;
        temp.tu2on = 0;
        temp.tstuon = 0;
        temp.kptuoff = 0;
        temp.tu1off = 0;
        temp.tu2off = 0;
        temp.tstuoff = 0;
        temp.min_value = 0;
        temp.max_value = 0;
        temp.ring = 0;
        temp.k_value = 0;
        temp.kou = 0;
        temp.kou2 = 0;
        temp.kds = 0;
        temp.group = 0;
        temp.station_cnt = 0;
        object.insert(i, temp);
    }
}

void Xpars::load_stations()
{
    //************************************
    //Костыль по кодировке в файле station.cfg (часть 1 из 2)

    QFile file1("station.cfg");
    QByteArray a;

    if (file1.open(QIODevice::ReadOnly))
    {
        a = file1.readAll();//чтение всех данных с файла сразу!
        QByteArray y("KOI8-R");
        a.replace(30,10,y);
    }
    file1.close();

    if (file1.open(QIODevice::WriteOnly))
    {
        file1.write(a);
    }
    file1.close();
    //************************************

    QDomDocument doc;
    QFile f("station.cfg");

    if (f.open(QIODevice::ReadOnly))
    {
        if(doc.setContent(&f))
        {
            QDomElement domElement = doc.documentElement();
            QDomNode node = domElement.firstChild();
            max_st = doc.elementsByTagName("station").count(); //Количество станций в файле station.cfg



            t_st=0; //Текущая станция

            while (!node.isNull())
            {
                if (node.toElement().tagName() == "station")
                {
                    QDomNode chld = node.firstChild();

                    parseEntry(node.toElement());

                    t_st++;
                }
                node = node.nextSibling();
            }
        }
    f.close();
    }

    //************************************
    //Костыль по кодировке в файле station.cfg (часть 2 из 2)

    if (file1.open(QIODevice::ReadOnly))
    {
        a = file1.readAll();//чтение всех данных с файла сразу!
        QByteArray y("ISO-8859-1");
        a.replace(30,6,y);
    }
    file1.close();

    if (file1.open(QIODevice::WriteOnly))
    {
        file1.write(a);
    }
    file1.close();

    //************************************
}

void Xpars::parseEntry(const QDomElement &elt)
{
    QDomNode node = elt.firstChild();

    g_station temp;
    temp.num = node.firstChild().toText().nodeValue().toInt();

    while (!node.isNull())
    {
        if (node.toElement().tagName() == "station")
            parseEntry(node.toElement());
        else
        {
            if (node.isElement())
            {
                QDomElement delt = node.toElement();

                if (node.nodeName() == "name")
                {
                    temp.name = delt.text();
                }

                if (node.nodeName() == "slang")
                {
                    temp.slang = delt.text();
                }

                if (node.nodeName() == "number")
                {
                    temp.number = delt.text().toInt();
                }

                if (node.nodeName() == "type")
                {
                    temp.type = delt.text().toInt();
                }

                if (node.nodeName() == "delay")
                {
                    temp.delay = delt.text().toInt();
                }

                if (node.nodeName() == "noarch")
                {
                    temp.noarch = delt.text().toInt();
                }

                if (node.nodeName() == "win")
                {
                    QDomNode chld = delt.firstChild();

                    t_win = delt.firstChild().toText().nodeValue().toInt(); //Номер текущего win

                    temp.win[t_win].win_num = t_win;
                    temp.max_win = t_win;

                    while (!chld.isNull())
                    {
                        if (chld.isElement())
                        {
                            QDomElement chldElement = chld.toElement();

                            if (chldElement.tagName() == "name")
                            {
                                temp.win[t_win].name = chldElement.text();
                            }

                            if (chldElement.tagName() == "file")
                            {
                                temp.win[t_win].file = chldElement.text();
                            }
                        }
                        chld = chld.nextSibling();
                    }
                    chld.~QDomNode();
                }
            }
        }
        node = node.nextSibling();
    }
    station.insert(t_st,temp);
}

void Xpars::load_object()
{
    //************************************
    //Костыль по кодировке в файле object.cfg (часть 1 из 2)


    QFile file1("object.cfg");
    QByteArray a;

    if (file1.open(QIODevice::ReadOnly))
    {
        a = file1.readAll();//чтение всех данных с файла сразу!
        QByteArray y("KOI8-R");
        a.replace(30,10,y);
    }
    file1.close();

    if (file1.open(QIODevice::WriteOnly))
    {
        file1.write(a);
    }
    file1.close();
    //************************************

    QDomDocument doc;
    QFile f("object.cfg");
    if (f.open(QIODevice::ReadOnly))
    {
        if(doc.setContent(&f))
        {
            QDomElement domElement = doc.documentElement();

            QDomNode node = domElement.firstChild();

            n_obj = doc.elementsByTagName("object").count(); //Количество объектов в файле object.cfg 3183

            zeroing();

            QProgressDialog* pprd = new QProgressDialog("Загрузка", 0,0, n_obj);
            pprd->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

            while (!node.isNull())
            {
                qApp->processEvents();
                if (node.toElement().tagName() == "object")
                {
                    pprd->setValue(t_obj);
                    st_n = 0; //Текущий порядковый номер станции в объекте
                    QDomNode chld = node.firstChild();

                    parseObjEntry(node.toElement());

                    t_obj++;
                }
                node = node.nextSibling();
            }
            delete pprd;
        }
    }
    f.close();

    //************************************
    //Костыль по кодировке в файле object.cfg (часть 2 из 2)

    if (file1.open(QIODevice::ReadOnly))
    {
        a = file1.readAll();//чтение всех данных с файла сразу!
        QByteArray y("ISO-8859-1");
        a.replace(30,6,y);
    }
    file1.close();

    if (file1.open(QIODevice::WriteOnly))
    {
        file1.write(a);
    }
    file1.close();

    //************************************


}

void Xpars::parseObjEntry(const QDomElement &elt)
{
    object[t_obj].station_cnt = 0;

    QDomNode node = elt.firstChild();
    while (!node.isNull())
    {
        if (node.toElement().tagName() == "object")
            parseObjEntry(node.toElement());
        else
        {
            if (node.isElement())
            {
                QDomElement delt = node.toElement();
                if (node.nodeName() == "Number")
                {
                    object[t_obj].number = delt.text().toInt();
                }

                if (node.nodeName() == "Station")
                {
                    object[t_obj].station = delt.text().toInt();
                }

                if (node.nodeName() == "Name")
                {
                    object[t_obj].name = delt.text();
                }

                if (node.nodeName() == "Slang")
                {
                    object[t_obj].slang = delt.text();
                }

                if (node.nodeName() == "Type")
                {
                    object[t_obj].type = delt.text().toInt();
                }

                if (node.nodeName() == "Subtype")
                {
                    object[t_obj].subtype = delt.text().toInt();
                }

                if (node.nodeName() == "Line")
                {
                    object[t_obj].line = delt.text().toInt();
                }

                if (node.nodeName() == "KPTSoff")
                {
                    object[t_obj].kptsoff = delt.text().toInt();
                }

                if (node.nodeName() == "TSoff")
                {
                    object[t_obj].tsoff = delt.text().toInt();
                }

                if (node.nodeName() == "KPTSon")
                {
                    object[t_obj].kptson = delt.text().toInt();
                }

                if (node.nodeName() == "TSon")
                {
                    object[t_obj].tson = delt.text().toInt();
                }

                if (node.nodeName() == "KPTUon")
                {
                    object[t_obj].kptuon = delt.text().toInt();
                }

                if (node.nodeName() == "KPTUon")
                {
                    object[t_obj].kptuon = delt.text().toInt();
                }

                if (node.nodeName() == "TU1on")
                {
                    object[t_obj].tu1on = delt.text().toInt();
                }

                if (node.nodeName() == "TU2on")
                {
                    object[t_obj].tu2on = delt.text().toInt();
                }

                if (node.nodeName() == "TSTUon")
                {
                    object[t_obj].tstuon = delt.text().toInt();
                }

                if (node.nodeName() == "KPTUoff")
                {
                    object[t_obj].kptuoff = delt.text().toInt();
                }

                if (node.nodeName() == "TU1off")
                {
                    object[t_obj].tu1off = delt.text().toInt();
                }

                if (node.nodeName() == "TU2off")
                {
                    object[t_obj].tu2off = delt.text().toInt();
                }

                if (node.nodeName() == "TSTUoff")
                {
                    object[t_obj].tstuoff = delt.text().toInt();
                }

                if (node.nodeName() == "min_value")
                {
                    object[t_obj].min_value = delt.text().toInt();
                }

                if (node.nodeName() == "max_value")
                {
                    object[t_obj].max_value = delt.text().toInt();
                }

                if (node.nodeName() == "ring")
                {
                    object[t_obj].ring = delt.text().toInt();
                }

                if (node.nodeName() == "k_value")
                {
                    object[t_obj].k_value = delt.text().toInt();
                }

                if (node.nodeName() == "KOU")
                {
                    object[t_obj].kou = delt.text().toInt();
                }

                if (node.nodeName() == "KOU")
                {
                    object[t_obj].kou2 = delt.text().toInt();
                }

                if (node.nodeName() == "Kds")
                {
                    object[t_obj].kds = delt.text().toInt();
                }

                if (node.nodeName() == "Group")
                {
                    object[t_obj].group = delt.text().toInt();
                }

                if (node.nodeName() == "station_w")
                {
                    object[t_obj].st[st_n].st_num = delt.firstChild().toText().nodeValue().toInt(); // Номер станции, на котором расположен объект

                    parseObjEntry(node.toElement());
                    st_n++;

                    object[t_obj].station_cnt = st_n;

                    stw_n = 0; //Текущий номер win в объекте
                }

                if (node.nodeName() == "win")
                {

                    object[t_obj].st[st_n].win[stw_n].win_num = delt.firstChild().toText().nodeValue().toInt();// Номер win, на котором расположен объект

                    parseObjEntry(node.toElement());

                    stw_n++;

                    object[t_obj].st[st_n].win_cnt = stw_n;

                }

                if (node.nodeName() == "type")
                {
                    object[t_obj].st[st_n].win[stw_n].type = delt.text().toInt();
                }

                if (node.nodeName() == "X")
                {
                    object[t_obj].st[st_n].win[stw_n].X = delt.text().toInt();
                }

                if (node.nodeName() == "Y")
                {
                    object[t_obj].st[st_n].win[stw_n].Y = delt.text().toInt();
                }

                if (node.nodeName() == "W")
                {
                    object[t_obj].st[st_n].win[stw_n].W = delt.text().toInt();
                }

                if (node.nodeName() == "H")
                {
                    object[t_obj].st[st_n].win[stw_n].H = delt.text().toInt();
                }

                if (node.nodeName() == "im_X")
                {
                    object[t_obj].st[st_n].win[stw_n].im_X = delt.text().toInt();
                }

                if (node.nodeName() == "im_Y")
                {
                    object[t_obj].st[st_n].win[stw_n].im_Y = delt.text().toInt();
                }

                if (node.nodeName() == "im_W")
                {
                    object[t_obj].st[st_n].win[stw_n].im_W = delt.text().toInt();
                }

                if (node.nodeName() == "im_H")
                {
                    object[t_obj].st[st_n].win[stw_n].im_H = delt.text().toInt();
                }

                if (node.nodeName() == "font")
                {
                    object[t_obj].st[st_n].win[stw_n].font = delt.text().toInt();
                }

                if (node.nodeName() == "color_on")
                {
                    object[t_obj].st[st_n].win[stw_n].color_on = delt.text();
                }

                if (node.nodeName() == "color_off")
                {
                    object[t_obj].st[st_n].win[stw_n].color_off = delt.text();
                }
            }
        }
        node = node.nextSibling();
    }
}

void Xpars::Save_Object()
{
    QString file_name = QFileDialog::getSaveFileName(0,"","object.cfg","object.cfg");

    QFile f(file_name);
    if (f.open(QIODevice::WriteOnly))
    {

        QTextStream out(&f);
        out<<"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n<opml version=\"1.0\">\n";

        for(int i=0; i<n_obj; i++)
        {
            out.setCodec("KOI8-R");
            out<<"<object>"<<"\n"<<"\t"<<"<Number>"<<object[i].number<<"</Number>"<<"\n"<<"\t"<<"<Station>"<<object[i].station<<"</Station>\n";
            out<<"\t<Name>"<<object[i].name<<"</Name>\n\t<Slang>"<<object[i].slang<<"</Slang>\n";
            out<<"\t<Type>"<<object[i].type<<"</Type>\n\t<Subtype>"<<object[i].subtype<<"</Subtype>\n";

            out<<"\t<Line>"<<object[i].line<<"</Line>\n";


            if (object[i].kptsoff != 0) out<<"\t<KPTSoff>"<<object[i].kptsoff<<"</KPTSoff>\n";
            if (object[i].tsoff != 0) out<<"\t<TSoff>"<<object[i].tsoff<<"</TSoff>\n";
            if (object[i].kptson != 0) out<<"\t<KPTSon>"<<object[i].kptson<<"</KPTSon>\n";
            if (object[i].tson != 0) out<<"\t<TSon>"<<object[i].tson<<"</TSon>\n";
            if (object[i].kptuon != 0) out<<"\t<KPTUon>"<<object[i].kptuon<<"</KPTUon>\n";
            if (object[i].tu1on != 0) out<<"\t<TU1on>"<<object[i].tu1on<<"</TU1on>\n";
            if (object[i].tu2on != 0) out<<"\t<TU2on>"<<object[i].tu2on<<"</TU2on>\n";
            if (object[i].tstuon != 0) out<<"\t<TSTUon>"<<object[i].tstuon<<"</TSTUon>\n";
            if (object[i].kptuoff != 0) out<<"\t<KPTUoff>"<<object[i].kptuoff<<"</KPTUoff>\n";
            if (object[i].tu1off != 0) out<<"\t<TU1off>"<<object[i].tu1off<<"</TU1off>\n";
            if (object[i].tu2off != 0) out<<"\t<TU2off>"<<object[i].tu2off<<"</TU2off>\n";
            if (object[i].tstuoff != 0 )out<<"\t<TSTUoff>"<<object[i].tstuoff<<"</TSTUoff>\n";

            if (object[i].kou != 0) out<<"\t<KOU>"<<object[i].kou<<"</KOU>\n";
            if (object[i].group != 0) out<<"\t<Group>"<<object[i].group<<"</Group>\n";
            if (object[i].kds != 0) out<<"\t<Kds>"<<object[i].kds<<"</Kds>\n";

            if (object[i].type == 4)
            {
                out<<"\t<min_value>"<<object[i].min_value<<"</min_value>\n";
                out<<"\t<max_value>"<<object[i].max_value<<"</max_value>\n";
            }

            if (object[i].ring != 0) out<<"\t<ring>"<<object[i].ring<<"</ring>\n";
            if (object[i].k_value != 0) out<<"\t<k_value>"<<object[i].k_value<<"</k_value>\n";

            for (int j=0; j<object[i].station_cnt; j++)
            {
                out<<"\t\t<station_w>"<<object[i].st[j].st_num<<"\n";

                for (int t=0; t<object[i].st[j].win_cnt; t++)
                {
                    out<<"\t\t\t<win>"<<object[i].st[j].win[t].win_num<<"\n";
                    out<<"\t\t\t\t<type>"<<object[i].st[j].win[t].type<<"</type>\n";
                    out<<"\t\t\t\t<X>"<<object[i].st[j].win[t].X<<"</X>\n";
                    out<<"\t\t\t\t<Y>"<<object[i].st[j].win[t].Y<<"</Y>\n";
                    out<<"\t\t\t\t<W>"<<object[i].st[j].win[t].W<<"</W>\n";
                    out<<"\t\t\t\t<H>"<<object[i].st[j].win[t].H<<"</H>\n";

                    if (object[i].st[j].win[t].im_X > 0)
                    {
                        out<<"\t\t\t\t<im_X>"<<object[i].st[j].win[t].im_X<<"</im_X>\n";
                    }
                    else out<<"\t\t\t\t<im_X>0</im_X>\n";

                    if (object[i].st[j].win[t].im_Y > 0)
                    {
                        out<<"\t\t\t\t<im_Y>"<<object[i].st[j].win[t].im_Y<<"</im_Y>\n";
                    }
                    else out<<"\t\t\t\t<im_Y>0</im_Y>\n";

                    if (object[i].st[j].win[t].im_W > 0)
                    {
                        out<<"\t\t\t\t<im_W>"<<object[i].st[j].win[t].im_W<<"</im_W>\n";
                    }
                    else out<<"\t\t\t\t<im_W>0</im_W>\n";

                    if (object[i].st[j].win[t].im_H > 0)
                    {
                        out<<"\t\t\t\t<im_H>"<<object[i].st[j].win[t].im_H<<"</im_H>\n";
                    }
                    else out<<"\t\t\t\t<im_H>0</im_H>\n";;

                    out<<"\t\t\t\t<font>"<<object[i].st[j].win[t].font<<"</font>\n";
                    out<<"\t\t\t\t<color_on>"<<object[i].st[j].win[t].color_on<<"</color_on>\n";
                    out<<"\t\t\t\t<color_off>"<<object[i].st[j].win[t].color_off<<"</color_off>\n";
                    out<<"\t\t\t</win>\n";
                }
                out<<"\t\t</station_w>\n";
            }
            out<<"</object>\n";
        }
        out<<"</opml>\n";
    }
    f.close();
}

void Xpars::Export_Excel()
{
    int i_pp = 0;
    float value_k = 0;
    QLocale loc;
    QString file_name_excel = QFileDialog::getSaveFileName(this,"","","*.csv");

    QMessageBox msgBox21;
    msgBox21.setWindowTitle("Внимание!");
    msgBox21.setText("Для корректного экспорта тегов убедитесь, что файл kp.cfg корректно заполнен!\n\nЗначение первого параметра в строке(признак телемеханики):\n1=УСО (КП СМ1820)\n2=ТЭМ-74\n3=ПТК-ТЛС");
    msgBox21.exec();

    load_stativ();

    QFile csvFile(file_name_excel);
    // Открываем, или создаём файл, если он не существует
    if(csvFile.open( QIODevice::WriteOnly ))
    {
        // Создаём текстовый поток, в который будем писать данные
        QTextStream textStream( &csvFile );
        QStringList stringList; // Вспомогательный объект QSqtringList, который сформирует строку

        stringList << "№";
        stringList << "Имя подстанции";
        stringList << "Технологическое название тега";
        stringList << "Имя тега"; // пока нет
        stringList << "Тип сигнала";
        stringList << "Линия";
        stringList << "Логический номер КП";
        stringList << "Физический номер КП(основной)";
        stringList << "Физический номер КП(резервный)";
        stringList << "Канал ТС/ТУ/ТИ";
        stringList << "Группа ТУ";  //новый
        stringList << "Объект ТУ";  //новый
        stringList << "Тип данных тега";  //новый
        stringList << "Масштабирование,K1";  //умножение
        stringList << "Масштабирование,K2";  //сложение
        stringList << "Тип масштабирования";
        textStream <<  stringList.join(";") +  "\n";


        for(int i=0; i<n_obj; i++)
        {
            if (object[i].kptson !=0 && object[i].tson!=0 && object[i].subtype !=6 && object[i].type !=5)
            {
                value_k = 0;
                i_pp++;
                stringList.clear();
                stringList << QString::number(i_pp);

                if (object[i].type == 4)
                {
                    stringList << station[object[i].station].name;
                    stringList << object[i].name + ".Телеизмерение";

                    if (object[i].subtype == 0)
                    {
                        stringList <<  Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_TI");
                    }
                    else
                    {
                        stringList <<  Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_U_TI");
                    }

                    stringList << "ТИ";
                    stringList << QString::number(object[i].line+1);
                    stringList << QString::number(object[i].kptson);
                    stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptson-1].kp_fiz1_number);
                    stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptson-1].kp_fiz2_number);
                    stringList << QString::number(object[i].tson);
                    stringList << "";
                    stringList << "";
                    stringList << "float";

                    switch(object[i].subtype)
                    {
                    case 0:
                        {
                            value_k = object[i].k_value;
                            value_k /=500;
                            stringList << loc.toString(value_k);
                            stringList << loc.toString(0);
                            break;
                        }


                    case 1:
                        {
                            value_k = 1;
                            value_k /=100;
                            stringList << loc.toString(value_k);
                            value_k = 750;
                            value_k /=100;
                            stringList << loc.toString(value_k);
                            break;
                        }

                    case 2:
                        {
                            value_k = 1;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            value_k = 600;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            break;
                        }

                    case 3:
                        {
                            value_k = 1;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            value_k = 750;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            break;
                        }


                    case 4:
                        {
                            value_k = 1;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            value_k = 100;
                            value_k /=50;
                            stringList << loc.toString(value_k);
                            break;
                        }

                    case 5:
                        {
                            value_k = 1;
                            value_k /=2;
                            stringList << loc.toString(value_k);
                            stringList << loc.toString(0);
                            break;
                        }

                    case 6:
                        {
                            value_k = 5;
                            value_k /=200;
                            stringList << loc.toString(value_k);
                            stringList << loc.toString(0);
                            break;
                        }

                    case 7:
                        {
                            value_k = 5;
                            value_k /=100;
                            stringList << loc.toString(value_k);
                            stringList << loc.toString(0);
                            break;
                        }

                    default: stringList << " ";
                            break;

                    }

                    stringList << "Линейное";

                    textStream <<  stringList.join(";") +  "\n";

                }

                else
                {
                        stringList << station[object[i].station].name;

                        if (object[i].kptsoff!=0 && object[i].tsoff!=0)
                        {
                            stringList << object[i].name + ".Включено.Телесигнализация";
                            stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_Vkl_TS");
                        }
                        else
                        {
                            stringList << object[i].name + ".Телесигнализация";
                            stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_TS");
                        }

                        stringList << "ТС";
                        stringList << QString::number(object[i].line+1);
                        stringList << QString::number(object[i].kptson);
                        stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptson-1].kp_fiz1_number);
                        stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptson-1].kp_fiz2_number);
                        stringList << QString::number(object[i].tson);
                        stringList << "";
                        stringList << "";
                        stringList << "bool";
                        textStream <<  stringList.join(";") +  "\n";
                }

            }

            if (object[i].kptsoff!=0 && object[i].tsoff!=0)
            {
                i_pp++;
                stringList.clear();
                stringList << QString::number(i_pp);
                stringList << station[object[i].station].name;
                stringList << object[i].name + ".Отключено.Телесигнализация";
                stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_Otkl_TS");
                stringList << "ТС";
                stringList << QString::number(object[i].line+1);
                stringList << QString::number(object[i].kptsoff);
                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptsoff-1].kp_fiz1_number);
                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptsoff-1].kp_fiz2_number);
                stringList << QString::number(object[i].tsoff);
                stringList << "";
                stringList << "";
                stringList << "bool";
                textStream <<  stringList.join(";") +  "\n";
            }

            if (object[i].kptuon !=0 && object[i].subtype !=6)
            {
                i_pp++;
                stringList.clear();
                stringList << QString::number(i_pp);
                stringList << station[object[i].station].name;

                if (kp_cfg[object[i].line].telemehanika == 1)
                {
                    stringList << object[i].name + ".Включить.Телеуправления";
                    stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_Vkl_TU");
                }
                else
                {
                    stringList << object[i].name + ".Телеуправления";
                    stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_TU");
                }

                stringList << "ТУ";
                stringList << QString::number(object[i].line+1);
                stringList << QString::number(object[i].kptuon);
                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptuon-1].kp_fiz1_number);
                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptuon-1].kp_fiz2_number);

                if ((kp_cfg[object[i].line].telemehanika == 2) || (kp_cfg[object[i].line].telemehanika == 3)) stringList << QString::number(object[i].tu1on); //Для ТЭМ-74 и ПТК-ТЛС
                    else stringList << QString::number(object[i].tstuon); //Для УСО СМ1820

                stringList << "";
                stringList << "";
                stringList << "byte/int";

                textStream <<  stringList.join(";") +  "\n";
            }

            if (object[i].kptuoff !=0 && kp_cfg[object[i].line].telemehanika == 1)
            {
                i_pp++;
                stringList.clear();
                stringList << QString::number(i_pp);
                stringList << station[object[i].station].name;
                stringList << object[i].name  + ".Отключить.Телеуправления";
                stringList << Translate(station[object[i].station].name)+"_"+Translate(object[i].name+"_Otkl_TU");
                stringList << "ТУ";
                stringList << QString::number(object[i].line+1);
                stringList << QString::number(object[i].kptuoff);

                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptuoff-1].kp_fiz1_number);
                stringList << QString::number(kp_cfg[object[i].line].stativ[object[i].kptuoff-1].kp_fiz2_number);

                if ( (kp_cfg[object[i].line].telemehanika == 2) || (kp_cfg[object[i].line].telemehanika == 3) ) stringList << QString::number(object[i].tu1off); //Для ТЭМ-74 и ПТК-ТЛС
                    else stringList << QString::number(object[i].tstuoff); //Для УСО СМ1820

               stringList << "";
               stringList << "";
               stringList << "byte/int";

               textStream <<  stringList.join(";") +  "\n";
            }
        }
        csvFile.close();
    }   
 QMessageBox msgBox;
 msgBox.setWindowTitle("Экспорт тегов в csv");
 msgBox.setFixedSize(200,200);
 msgBox.setText("Экспорт тегов закончен\n\nЭкспортировано " + QString::number(i_pp) + " тегов");
 msgBox.exec();
}

void Xpars::Add_Object()
{
    if (flag_openEdit>0) return;

    flag_openEdit++;

    ww = new Dialog(this);
    ww->setWindowTitle("Добавление объекта №" + QString::number(n_obj+1));

    if(ww->exec())
    {
        object[n_obj].number = n_obj+1;
        object[n_obj].station = ww->getStation();
        object[n_obj].name = ww->getName();
        object[n_obj].slang = ww->getSlang();
        object[n_obj].type = ww->getType();
        object[n_obj].subtype = ww->getSubtype();
        object[n_obj].line = ww->getLine();

        object[n_obj].kptsoff = ww->getKptsoff();
        object[n_obj].tsoff = ww->getTsoff();
        object[n_obj].kptson = ww->getKptson();
        object[n_obj].tson = ww->getTson();
        object[n_obj].kptuon = ww->getKptuon();
        object[n_obj].tu1on = ww->getTu1on();
        object[n_obj].tu2on = ww->getTu2on();
        object[n_obj].tstuon = ww->getTstuon();
        object[n_obj].kptuoff = ww->getKptuoff();
        object[n_obj].tu1off = ww->getTu1off();
        object[n_obj].tu2off = ww->getTu2off();
        object[n_obj].tstuoff = ww->getTstuoff();
        object[n_obj].min_value = ww->getMin_value();
        object[n_obj].max_value = ww->getMax_value();
        object[n_obj].ring = ww->getRing();
        object[n_obj].k_value = ww->getK_value();
        object[n_obj].kou = ww->getKou();
        object[n_obj].kds = ww->getKds();
        object[n_obj].group = ww->getGroup();

        object[n_obj].station_cnt = 0; // количество станций, на которых расположены объект

        n_obj++;
        status_objd->display(n_obj);
        addTable(tt_station);
    }
    flag_openEdit--;
}

void Xpars::Open()
{
    int n;
    QString NameFile;

    NameFile = QFileDialog::getOpenFileName(this, tr("Open File"), ".", "*.bmp"); //Путь к мнемосхеме

    if (NameFile == "") return;

    mnemo_file_name = NameFile;

    for (int ii = 0; ii<mnemo_file_name.length(); ii++)
    {
        if (mnemo_file_name.data()[ii] == '/')
        {
            n = ii;
        }
    }

    QString file_names = mnemo_file_name.right(mnemo_file_name.length()-n-1); //Имя мнемосхемы

    //Определим номер текущей станции и номера текущего win

    for (int i=0; i<max_st; i++)
    {
        for (int j=0; j<=station[i].max_win; j++)
        {
            if (station[i].win[j].file == file_names)
            {
                tt_station = i;
                tt_win = j;
            }
        }
    }

    addTable(tt_station); // Обновление окна "Перечень объектов"

    OutDateScene(); //Отправка сигнала на обнуление QMap pole, отправка данных в QMap pole, отправка сигнала на нарисовку на сцене
}

void Xpars::OutDateScene()
{
    emit SignalZero(0); //Обнуление количества полей

        for (int i=0; i<n_obj; i++)
        {
           for (int j=0; j<object[i].station_cnt; j++)
               {
                    if (object[i].st[j].st_num == tt_station)
                    {
                        for (int y=0; y<object[i].st[j].win_cnt; y++)
                        {
                            if (object[i].st[j].win[y].win_num == tt_win)
                            {
                                emit SignalMap(object[i].slang, object[i].number, object[i].type, object[i].subtype, object[i].st[j].win[y].type, object[i].st[j].win[y].X, object[i].st[j].win[y].Y, object[i].st[j].win[y].W, object[i].st[j].win[y].H, object[i].st[j].win[y].im_X, object[i].st[j].win[y].im_Y, object[i].st[j].win[y].im_W, object[i].st[j].win[y].im_H, object[i].st[j].win[y].font, object[i].st[j].win[y].color_on, object[i].st[j].win[y].color_off);
                            }
                        }
                    }
               }
        }
      emit MnemoSignal(mnemo_file_name); //Передача пути файла в класс MyWidj
}

void Xpars::paintEvent(QPaintEvent *)
{

}

void Xpars::addComboBox()
{
    for (int i=0; i<max_st; i++)
    {
        ui->comboBox->addItem(station[i].name);
    }

    tt_table_station = ui->comboBox->currentIndex();

    addTable(tt_table_station);
}

void Xpars::addTable(int& flow)
{
    int flow_stantion, row, column;
    row = 0;
    flow_stantion = flow;
    QString type;

    for (int i=0; i<n_obj; i++)
    {
        column=0;
        if (object[i].station == flow_stantion)
        {
            ui->tableWidget->setRowCount(row+1);

            QTableWidgetItem *newItem1 = new QTableWidgetItem(object[i].name);
            ui->tableWidget->setItem(row, column, newItem1);
            column++;

            switch(object[i].type)
            {
                case 0: type = "РЕЗЕРВ";
                    break;
                case 1: type = "ТС";
                    break;
                case 2: type = "Псевдо";
                    break;
                case 3: type = "Зазем";
                    break;
                case 4: type = "ТИ";
                    break;
                case 5: if (object[i].subtype == 0) type = "ТУ ДБЗ/ДШТО";
                    break;
                case 6: type = "ТУ";
                    break;
                case 7: type = "ТУ Ш";
                    break;
                default: type = "Диагностика";
            }
            QTableWidgetItem *newItem2 = new QTableWidgetItem(type);
            ui->tableWidget->setItem(row, column, newItem2);
            newItem2->setFlags(Qt::ItemIsEnabled);
            column++;

            QTableWidgetItem *newItem3 = new QTableWidgetItem(station[object[i].station].name);
            ui->tableWidget->setItem(row, column, newItem3);
            newItem3->setFlags(Qt::ItemIsEnabled);
            column++;

            QTableWidgetItem *newItem4 = new QTableWidgetItem(QString::number(object[i].number));
            ui->tableWidget->setItem(row, column, newItem4);
            newItem4->setFlags(Qt::ItemIsEnabled);
            column++;

            row++;
        }
    }
    ui->comboBox->setCurrentIndex(flow_stantion);
}

void Xpars::addTableSlot()
{
    tt_table_station = ui->comboBox->currentIndex();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Имя"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Тип"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Станция"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Номер"));

    addTable(tt_table_station);
}

void Xpars::load_sv()
{
    int i, y;

    if (flag_openEdit>0)
    {
        QMessageBox msgBox;
        msgBox.setText("Окно параметров объекта уже открыто");
        msgBox.exec();
        return;
    }

    flag_openEdit++;

    ui->action_add_object->setDisabled(true); //Блокируем в меню "новый объект"

    i = ui->tableWidget->currentRow();
    QTableWidgetItem *Iitem = new QTableWidgetItem;
    Iitem = ui->tableWidget->item(i,3);

    y = Iitem->text().toInt()-1; //Номер выделенного объекта

    ww = new Dialog(this);

    ww->show();
    ww->setWindowTitle("Параметры объекта №" + QString::number(object[y].number));

    ww->outStation(object[y].station);
    ww->outName(object[y].name);
    ww->outSlang(object[y].slang);
    ww->outType(object[y].type);
    ww->outSubtype(object[y].subtype);
    ww->outLine(object[y].line);

    ww->outKptsoff(object[y].kptsoff);
    ww->outTsoff(object[y].tsoff);
    ww->outKptson(object[y].kptson);
    ww->outTson(object[y].tson);
    ww->outKptuon(object[y].kptuon);
    ww->outTu1on(object[y].tu1on);
    ww->outTu2on(object[y].tu2on);
    ww->outTstuon(object[y].tstuon);
    ww->outKptuoff(object[y].kptuoff);

    ww->outTu1off(object[y].tu1off);
    ww->outTu2off(object[y].tu2off);
    ww->outTstuoff(object[y].tstuoff);
    ww->outMin_value(object[y].min_value);
    ww->outMax_value(object[y].max_value);
    ww->outRing(object[y].ring);
    ww->outK_value(object[y].k_value);
    ww->outKou(object[y].kou);
    ww->outKds(object[y].kds);
    ww->outGroup(object[y].group);

    if (ww->exec())
    {
        object[y].station = ww->getStation();
        object[y].name = ww->getName();
        if (ww->getSlang() != object[y].slang)
        {
            object[y].slang = ww->getSlang();
            OutDateScene(); //Отправка сигнала на обнуление QMap pole, отправка данных в QMap pole, отправка сигнала на нарисовку на сцене
        }
        object[y].type = ww->getType();
        object[y].subtype = ww->getSubtype();
        object[y].line = ww->getLine();

        object[y].kptsoff = ww->getKptsoff();
        object[y].tsoff = ww->getTsoff();
        object[y].kptson = ww->getKptson();
        object[y].tson = ww->getTson();
        object[y].kptuon = ww->getKptuon();
        object[y].tu1on = ww->getTu1on();
        object[y].tu2on = ww->getTu2on();
        object[y].tstuon = ww->getTstuon();
        object[y].kptuoff = ww->getKptuoff();
        object[y].tu1off = ww->getTu1off();
        object[y].tu2off = ww->getTu2off();
        object[y].tstuoff = ww->getTstuoff();
        object[y].min_value = ww->getMin_value();
        object[y].max_value = ww->getMax_value();
        object[y].ring = ww->getRing();
        object[y].k_value = ww->getK_value();
        object[y].kou = ww->getKou();
        object[y].kds = ww->getKds();
        object[y].group = ww->getGroup();
        addTable(tt_station); // Обновление окна "Перечень объектов"
    }
    ui->action_add_object->setEnabled(true); //Разблокируем в меню "новый объект"
    flag_openEdit--;
}

void Xpars::addShop()
{
    QPixmap pix("but.png");
    QPushButton *Button_TU = new QPushButton("", ui->dockWidgetContents_3);
    Button_TU->setIcon(pix);
    Button_TU->setGeometry(0, 1, 28, 28);
    Button_TU->setToolTip("Кнопка ТУ");
    connect(Button_TU, SIGNAL(clicked()), this, SLOT(PushButton_TU()));

    pix.load("zaz.png");
    QPushButton *Button_ZAZ = new QPushButton("", ui->dockWidgetContents_3);
    Button_ZAZ->setIcon(pix);
    Button_ZAZ->setGeometry(30, 1, 28, 28);
    Button_ZAZ->setToolTip("Заземление");
    connect(Button_ZAZ, SIGNAL(clicked()), this, SLOT(PushButton_ZAZ()));

    pix.load("rub_g.png");
    QPushButton *Button_RUB_G = new QPushButton("", ui->dockWidgetContents_3);
    Button_RUB_G->setIcon(pix);
    Button_RUB_G->setGeometry(60, 1, 28, 28);
    Button_RUB_G->setToolTip("Рубильник горизонтальный");
    connect(Button_RUB_G, SIGNAL(clicked()), this, SLOT(PushButton_RUB_G()));

    pix.load("rub_v.png");
    QPushButton *Button_RUB_V = new QPushButton("", ui->dockWidgetContents_3);
    Button_RUB_V->setIcon(pix);
    Button_RUB_V->setGeometry(90, 1, 28, 28);
    Button_RUB_V->setToolTip("Рубильник вертикальный");
    connect(Button_RUB_V, SIGNAL(clicked()), this, SLOT(PushButton_RUB_V()));

    pix.load("rub1_g.png");
    QPushButton *Button_RUB1_G = new QPushButton("", ui->dockWidgetContents_3);
    Button_RUB1_G->setIcon(pix);
    Button_RUB1_G->setGeometry(120, 1, 28, 28);
    Button_RUB1_G->setToolTip("Автомат горизонтальный");
    connect(Button_RUB1_G, SIGNAL(clicked()), this, SLOT(PushButton_RUB1_G()));

    pix.load("rub1_v.png");
    QPushButton *Button_RUB1_V = new QPushButton("", ui->dockWidgetContents_3);
    Button_RUB1_V->setIcon(pix);
    Button_RUB1_V->setGeometry(150, 1, 28, 28);
    Button_RUB1_V->setToolTip("Автомат вертикальный");
    connect(Button_RUB1_V, SIGNAL(clicked()), this, SLOT(PushButton_RUB1_V()));

    pix.load("u_txt.png");
    QPushButton *Button_U_TXT = new QPushButton("", ui->dockWidgetContents_3);
    Button_U_TXT->setIcon(pix);
    Button_U_TXT->setGeometry(180, 1, 28, 28);
    Button_U_TXT->setToolTip("Текст управления ТУ");
    connect(Button_U_TXT, SIGNAL(clicked()), this, SLOT(PushButton_U_TXT()));

    pix.load("out.png");
    QPushButton *Button_OUT = new QPushButton("", ui->dockWidgetContents_3);
    Button_OUT->setIcon(pix);
    Button_OUT->setGeometry(210, 1, 28, 28);
    Button_OUT->setToolTip("Окно ТИ");
    connect(Button_OUT, SIGNAL(clicked()), this, SLOT(PushButton_OUT()));

    pix.load("next.png");
    QPushButton *Button_NEXT = new QPushButton("", ui->dockWidgetContents_3);
    Button_NEXT->setIcon(pix);
    Button_NEXT->setGeometry(240, 1, 28, 28);
    Button_NEXT->setToolTip("Следующая станция");
    connect(Button_NEXT, SIGNAL(clicked()), this, SLOT(PushButton_NEXT()));

    pix.load("prev.png");
    QPushButton *Button_PREV = new QPushButton("", ui->dockWidgetContents_3);
    Button_PREV->setIcon(pix);
    Button_PREV->setGeometry(270, 1, 28, 28);
    Button_PREV->setToolTip("Предыдущая станция");
    connect(Button_PREV, SIGNAL(clicked()), this, SLOT(PushButton_PREV()));

    pix.load("station.png");
    QPushButton *Button_STATION = new QPushButton("", ui->dockWidgetContents_3);
    Button_STATION->setIcon(pix);
    Button_STATION->setGeometry(300, 1, 28, 28);
    Button_STATION->setToolTip("Показать станцию");
    connect(Button_STATION, SIGNAL(clicked()), this, SLOT(PushButton_STATION()));

    pix.load("show_l.png");
    QPushButton *Button_SHOW_L = new QPushButton("", ui->dockWidgetContents_3);
    Button_SHOW_L->setIcon(pix);
    Button_SHOW_L->setGeometry(330, 1, 28, 28);
    Button_SHOW_L->setToolTip("Показать верхний уровень");
    connect(Button_SHOW_L, SIGNAL(clicked()), this, SLOT(PushButton_SHOW_L()));

    pix.load("hide_t.png");
    QPushButton *Button_HIDE_T = new QPushButton("", ui->dockWidgetContents_3);
    Button_HIDE_T->setIcon(pix);
    Button_HIDE_T->setGeometry(360, 1, 28, 28);
    Button_HIDE_T->setToolTip("Закрывать надпись");
    connect(Button_HIDE_T, SIGNAL(clicked()), this, SLOT(PushButton_HIDE_T()));

    //#######################

    pix.load("f_but.png");
    QPushButton *Button_F_BUT = new QPushButton("", ui->dockWidgetContents_3);
    Button_F_BUT->setIcon(pix);
    Button_F_BUT->setGeometry(0, 30, 28, 28);
    Button_F_BUT->setToolTip("Кнопка с фиксацией");
    connect(Button_F_BUT, SIGNAL(clicked()), this, SLOT(PushButton_F_BUT()));

    pix.load("nf_but.png");
    QPushButton *Button_NF_BUT = new QPushButton("", ui->dockWidgetContents_3);
    Button_NF_BUT->setIcon(pix);
    Button_NF_BUT->setGeometry(30, 30, 28, 28);
    Button_NF_BUT->setToolTip("Кнопка без фиксации");
    connect(Button_NF_BUT, SIGNAL(clicked()), this, SLOT(PushButton_NF_BUT()));

    pix.load("lamp.png");
    QPushButton *Button_LAMP = new QPushButton("", ui->dockWidgetContents_3);
    Button_LAMP->setIcon(pix);
    Button_LAMP->setGeometry(60, 30, 28, 28);
    Button_LAMP->setToolTip("Лампа");
    connect(Button_LAMP, SIGNAL(clicked()), this, SLOT(PushButton_LAMP()));

    pix.load("rect.png");
    QPushButton *Button_RECT = new QPushButton("", ui->dockWidgetContents_3);
    Button_RECT->setIcon(pix);
    Button_RECT->setGeometry(90, 30, 28, 28);
    Button_RECT->setToolTip("Прямоугольник без текста ТС");
    connect(Button_RECT, SIGNAL(clicked()), this, SLOT(PushButton_RECT()));

    pix.load("rect4.png");
    QPushButton *Button_RECT4 = new QPushButton("", ui->dockWidgetContents_3);
    Button_RECT4->setIcon(pix);
    Button_RECT4->setGeometry(120, 30, 28, 28);
    Button_RECT4->setToolTip("Прямоугольник без текста ТС с 4 состояниями");
    connect(Button_RECT4, SIGNAL(clicked()), this, SLOT(PushButton_RECT4()));

    pix.load("t_rect.png");
    QPushButton *Button_T_RECT = new QPushButton("", ui->dockWidgetContents_3);
    Button_T_RECT->setIcon(pix);
    Button_T_RECT->setGeometry(150, 30, 28, 28);
    Button_T_RECT->setToolTip("Прямоугольник с текстом ТС");
    connect(Button_T_RECT, SIGNAL(clicked()), this, SLOT(PushButton_T_RECT()));

    pix.load("txt.png");
    QPushButton *Button_TXT = new QPushButton("", ui->dockWidgetContents_3);
    Button_TXT->setIcon(pix);
    Button_TXT->setGeometry(180, 30, 28, 28);
    Button_TXT->setToolTip("Текст");
    connect(Button_TXT, SIGNAL(clicked()), this, SLOT(PushButton_TXT()));

    pix.load("out.png");
    QPushButton *Button_OUT_TM = new QPushButton("", ui->dockWidgetContents_3);
    Button_OUT_TM->setIcon(pix);
    Button_OUT_TM->setGeometry(210, 30, 28, 28);
    Button_OUT_TM->setToolTip("Окно ТИ ТЭМ-74");
    connect(Button_OUT_TM, SIGNAL(clicked()), this, SLOT(PushButton_OUT_TM()));

    pix.load("up_w.png");
    QPushButton *Button_UP_W = new QPushButton("", ui->dockWidgetContents_3);
    Button_UP_W->setIcon(pix);
    Button_UP_W->setGeometry(240, 30, 28, 28);
    Button_UP_W->setToolTip("Предыдущее окно");
    connect(Button_UP_W, SIGNAL(clicked()), this, SLOT(PushButton_UP_W()));

    pix.load("down_w.png");
    QPushButton *Button_DOWN_W = new QPushButton("", ui->dockWidgetContents_3);
    Button_DOWN_W->setIcon(pix);
    Button_DOWN_W->setGeometry(270, 30, 28, 28);
    Button_DOWN_W->setToolTip("Следующее окно");
    connect(Button_DOWN_W, SIGNAL(clicked()), this, SLOT(PushButton_DOWN_W()));

    pix.load("rectm.png");
    QPushButton *Button_RECTM = new QPushButton("", ui->dockWidgetContents_3);
    Button_RECTM->setIcon(pix);
    Button_RECTM->setGeometry(300, 30, 28, 28);
    Button_RECTM->setToolTip("Двойное псевдо");
    connect(Button_RECTM, SIGNAL(clicked()), this, SLOT(PushButton_RECTM()));

    pix.load("signal_m.png");
    QPushButton *Button_SIGNAL_M = new QPushButton("", ui->dockWidgetContents_3);
    Button_SIGNAL_M->setIcon(pix);
    Button_SIGNAL_M->setGeometry(330, 30, 28, 28);
    Button_SIGNAL_M->setToolTip("Индикация изменений");
    connect(Button_SIGNAL_M, SIGNAL(clicked()), this, SLOT(PushButton_SIGNAL_M()));

    pix.load("station_p.png");
    QPushButton *Button_STATION_P = new QPushButton("", ui->dockWidgetContents_3);
    Button_STATION_P->setIcon(pix);
    Button_STATION_P->setGeometry(360, 30, 28, 28);
    Button_STATION_P->setToolTip("Показать программу экстренного снятия");
    connect(Button_STATION_P, SIGNAL(clicked()), this, SLOT(PushButton_STATION_P()));
}

void Xpars::ShowObjectPanel()
{
    if (ui->dockWidget->isVisible() == true)
        ui->dockWidget->hide();
    else
        ui->dockWidget->show();
}

void Xpars::ShowObjectProp()
{
    if (ui->dockWidget_2->isVisible() == true)
        ui->dockWidget_2->hide();
    else
        ui->dockWidget_2->show();
}

void Xpars::ShowElementMagazin()
{
    if (ui->dockWidget_3->isVisible() == true)
        ui->dockWidget_3->hide();
    else
        ui->dockWidget_3->show();
}

void Xpars::SlotTTNumObj(const int &CurNum)
{
    int w, ii;
    w=-1;
    ColorOn = "";
    ColorOff = "";

    tt_num_obj = CurNum;
    if (tt_num_obj <= 0)
    {
        status_tt_num->setText("Объект не выбран");
        status_tt_obj->setText("");
        status_X_obj->setText("");
        status_Y_obj->setText("");
        ui->tableWidget->setCurrentCell(-1, 0); //Убираем выделение ячейки после нажатия на пустое место
        tt_num_obj = -1;
    }
    else
    {      
        if (tt_table_station == ui->comboBox->currentIndex())
        {
            for (ii=0; ii<n_obj; ii++)
            {
                if (object[ii].station == tt_table_station)
                {
                    w++;
                    if (object[ii].number == CurNum)
                    {
                        ui->tableWidget->setCurrentCell(w, 0); //Выделение ячейки при нажатии на поле объекта на подложке
                        break;
                    }
                }
            }
        }

        status_tt_num->setText("Номер объекта: " + QString::number(tt_num_obj) + "   ");

        status_tt_obj->setText("Имя объекта: " + object[tt_num_obj-1].slang + "   ");

           for (int j=0; j<object[tt_num_obj-1].station_cnt; j++)
               {
                    if (object[tt_num_obj-1].st[j].st_num == tt_station)
                    {
                        for (int y=0; y<object[tt_num_obj-1].st[j].win_cnt; y++)
                        {
                            if (object[tt_num_obj-1].st[j].win[y].win_num == tt_win)
                            {
                                current_station = j;
                                current_win = y;
                            }
                        }
                    }
               }

    }
    addTableSV(); //Добавление ячеек в таблицу свойств объекта
}

void Xpars::addTableSV() //Обновление таблицы свойств объекта
{
    if (tt_num_obj>0)
    {
        QTableWidgetItem *Item1 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].W));
        ui->tableWidget_2->setItem(0, 0, Item1);

        QTableWidgetItem *Item2 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].H));
        ui->tableWidget_2->setItem(0, 1, Item2);

        QTableWidgetItem *Item3 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].im_W));
        ui->tableWidget_2->setItem(0, 2, Item3);

        QTableWidgetItem *Item4 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].im_H));
        ui->tableWidget_2->setItem(0, 3, Item4);

        QTableWidgetItem *Item5 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].X));
        ui->tableWidget_2->setItem(0, 4, Item5);

        QTableWidgetItem *Item6 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].Y));
        ui->tableWidget_2->setItem(0, 5, Item6);

        QTableWidgetItem *Item7 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].im_X));
        ui->tableWidget_2->setItem(0, 6, Item7);

        QTableWidgetItem *Item8 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].im_Y));
        ui->tableWidget_2->setItem(0, 7, Item8);

        QTableWidgetItem *Item9 = new QTableWidgetItem(QString::number(object[tt_num_obj-1].st[current_station].win[current_win].font));
        ui->tableWidget_2->setItem(0, 8, Item9);

        QTableWidgetItem *Item10 = new QTableWidgetItem();
        Item10->setBackgroundColor(QColor(object[tt_num_obj-1].st[current_station].win[current_win].color_on));
        Item10->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_2->setItem(0, 9, Item10);

        QTableWidgetItem *Item11 = new QTableWidgetItem();
        Item11->setBackgroundColor(QColor(object[tt_num_obj-1].st[current_station].win[current_win].color_off));
        Item11->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_2->setItem(0, 10, Item11);
    }
    else
    {
        QTableWidgetItem *Item1 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 0, Item1);

        QTableWidgetItem *Item2 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 1, Item2);

        QTableWidgetItem *Item3 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 2, Item3);

        QTableWidgetItem *Item4 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 3, Item4);

        QTableWidgetItem *Item5 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 4, Item5);

        QTableWidgetItem *Item6 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 5, Item6);

        QTableWidgetItem *Item7 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 6, Item7);

        QTableWidgetItem *Item8 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 7, Item8);

        QTableWidgetItem *Item9 = new QTableWidgetItem("");
        ui->tableWidget_2->setItem(0, 8, Item9);

        QTableWidgetItem *Item10 = new QTableWidgetItem();
        Item10->setBackgroundColor(Qt::white);
        Item10->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_2->setItem(0, 9, Item10);

        QTableWidgetItem *Item11 = new QTableWidgetItem();
        Item11->setBackgroundColor(Qt::white);
        Item11->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_2->setItem(0, 10, Item11);
    }
}

void Xpars::ShowPalette()
{
    int i;
    i = ui->tableWidget_2->currentRow();

    if (i!=9 && i!=10) return;

    if (current_station < 0 || current_win < 0) return;

    if (i == 9)
    {
        ColorOn = QColorDialog::getColor().name();
        ui->tableWidget_2->item(0, i)->setBackground(QColor(ColorOn));
    }

    if (i == 10)
    {
        ColorOff = QColorDialog::getColor().name();
        ui->tableWidget_2->item(0, i)->setBackground(QColor(ColorOff));
    }
}

void Xpars::SlotOutPole(const int &X, const int &Y, const int &W, const int &H, const int &im_X, const int &im_Y, const int &im_W, const int &im_H, const int &font, const QString &color_on, const QString &color_off)
{
    status_X_obj->setText("X: " + QString::number(X) + "    ");
    status_Y_obj->setText("Y: " + QString::number(Y) + "    ");


    object[tt_num_obj-1].st[current_station].win[current_win].X = X;
    object[tt_num_obj-1].st[current_station].win[current_win].Y = Y;
    object[tt_num_obj-1].st[current_station].win[current_win].W = W;
    object[tt_num_obj-1].st[current_station].win[current_win].H = H;
    object[tt_num_obj-1].st[current_station].win[current_win].im_X = im_X;
    object[tt_num_obj-1].st[current_station].win[current_win].im_Y = im_Y;
    object[tt_num_obj-1].st[current_station].win[current_win].im_W = im_W;
    object[tt_num_obj-1].st[current_station].win[current_win].im_H = im_H;
    object[tt_num_obj-1].st[current_station].win[current_win].font = font;
    object[tt_num_obj-1].st[current_station].win[current_win].color_on = color_on;
    object[tt_num_obj-1].st[current_station].win[current_win].color_off = color_off;

    addTableSV();
}

void Xpars::save_sv()
{
    if (current_station < 0 || current_win < 0) return;

    object[tt_num_obj-1].st[current_station].win[current_win].W = ui->tableWidget_2->item(0, 0)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].H = ui->tableWidget_2->item(0, 1)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].im_W = ui->tableWidget_2->item(0, 2)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].im_H = ui->tableWidget_2->item(0, 3)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].X = ui->tableWidget_2->item(0, 4)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].Y = ui->tableWidget_2->item(0, 5)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].im_X = ui->tableWidget_2->item(0, 6)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].im_Y = ui->tableWidget_2->item(0, 7)->text().toInt();
    object[tt_num_obj-1].st[current_station].win[current_win].font = ui->tableWidget_2->item(0, 8)->text().toInt();

    if (ColorOn != "")
    {
        object[tt_num_obj-1].st[current_station].win[current_win].color_on = ColorOn;
    }

    if (ColorOff != "")
    {
        object[tt_num_obj-1].st[current_station].win[current_win].color_off = ColorOff;
    }

    OutDateScene();
}

void Xpars::SlotDelNumPole(const int &DelNumPole)
{

    for (int i = current_win; i<object[DelNumPole-1].st[current_station].win_cnt - 1; i++)
    {
        object[DelNumPole-1].st[current_station].win[i].X = object[DelNumPole-1].st[current_station].win[i+1].X;
        object[DelNumPole-1].st[current_station].win[i].Y = object[DelNumPole-1].st[current_station].win[i+1].Y;
        object[DelNumPole-1].st[current_station].win[i].W = object[DelNumPole-1].st[current_station].win[i+1].W;
        object[DelNumPole-1].st[current_station].win[i].H = object[DelNumPole-1].st[current_station].win[i+1].H;
        object[DelNumPole-1].st[current_station].win[i].im_X = object[DelNumPole-1].st[current_station].win[i+1].im_X;
        object[DelNumPole-1].st[current_station].win[i].im_Y = object[DelNumPole-1].st[current_station].win[i+1].im_Y;
        object[DelNumPole-1].st[current_station].win[i].im_W = object[DelNumPole-1].st[current_station].win[i+1].im_W;
        object[DelNumPole-1].st[current_station].win[i].im_H = object[DelNumPole-1].st[current_station].win[i+1].im_H;
        object[DelNumPole-1].st[current_station].win[i].color_on = object[DelNumPole-1].st[current_station].win[i+1].color_on;
        object[DelNumPole-1].st[current_station].win[i].color_off = object[DelNumPole-1].st[current_station].win[i+1].color_off;
        object[DelNumPole-1].st[current_station].win[i].font = object[DelNumPole-1].st[current_station].win[i+1].font;
        object[DelNumPole-1].st[current_station].win[i].type = object[DelNumPole-1].st[current_station].win[i+1].type;
        object[DelNumPole-1].st[current_station].win[i].win_num = object[DelNumPole-1].st[current_station].win[i+1].win_num;
    }

        object[DelNumPole-1].st[current_station].win_cnt--;
        current_station = -1;
        current_win = -1;

        tt_num_obj = -1;

        status_tt_num->setText("Объект не выбран");
        status_tt_obj->setText("");
        status_X_obj->setText("");
        status_Y_obj->setText("");
        ui->tableWidget->setCurrentCell(-1, 0); //Убираем выделение ячейки после удаления поля

        addTableSV();
}

void Xpars::SlotOpenEdit(const int& OpenNum)
{
    if (tt_station<0) return;

    if (flag_openEdit>0)
    {
        QMessageBox msgBox;
        msgBox.setText("Окно параметров объекта уже открыто");
        msgBox.exec();
        return;
    }

    flag_openEdit++;

    int y = OpenNum-1;

    ui->action_add_object->setDisabled(true);

    ww = new Dialog(this);
    ww->show();
    ww->setWindowTitle("Параметры объекта №" + QString::number(object[y].number));

    ww->outStation(object[y].station);
    ww->outName(object[y].name);
    ww->outSlang(object[y].slang);
    ww->outType(object[y].type);
    ww->outSubtype(object[y].subtype);
    ww->outLine(object[y].line);

    ww->outKptsoff(object[y].kptsoff);
    ww->outTsoff(object[y].tsoff);
    ww->outKptson(object[y].kptson);
    ww->outTson(object[y].tson);
    ww->outKptuon(object[y].kptuon);
    ww->outTu1on(object[y].tu1on);
    ww->outTu2on(object[y].tu2on);
    ww->outTstuon(object[y].tstuon);
    ww->outKptuoff(object[y].kptuoff);

    ww->outTu1off(object[y].tu1off);
    ww->outTu2off(object[y].tu2off);
    ww->outTstuoff(object[y].tstuoff);
    ww->outMin_value(object[y].min_value);
    ww->outMax_value(object[y].max_value);
    ww->outRing(object[y].ring);
    ww->outK_value(object[y].k_value);
    ww->outKou(object[y].kou);
    ww->outKds(object[y].kds);
    ww->outGroup(object[y].group);

    if (ww->exec())
    {
        object[y].station = ww->getStation();
        object[y].name = ww->getName();
        if (ww->getSlang() != object[y].slang)
        {
            object[y].slang = ww->getSlang();
            OutDateScene(); //Отправка сигнала на обнуление QMap pole, отправка данных в QMap pole, отправка сигнала на нарисовку на сцене
        }
        object[y].type = ww->getType();
        object[y].subtype = ww->getSubtype();
        object[y].line = ww->getLine();

        object[y].kptsoff = ww->getKptsoff();
        object[y].tsoff = ww->getTsoff();
        object[y].kptson = ww->getKptson();
        object[y].tson = ww->getTson();
        object[y].kptuon = ww->getKptuon();
        object[y].tu1on = ww->getTu1on();
        object[y].tu2on = ww->getTu2on();
        object[y].tstuon = ww->getTstuon();
        object[y].kptuoff = ww->getKptuoff();
        object[y].tu1off = ww->getTu1off();
        object[y].tu2off = ww->getTu2off();
        object[y].tstuoff = ww->getTstuoff();
        object[y].min_value = ww->getMin_value();
        object[y].max_value = ww->getMax_value();
        object[y].ring = ww->getRing();
        object[y].k_value = ww->getK_value();
        object[y].kou = ww->getKou();
        object[y].kds = ww->getKds();
        object[y].group = ww->getGroup();
        addTable(tt_station); // Обновление окна "Перечень объектов"
    }
    ui->action_add_object->setEnabled(true); //Разблокируем в меню "новый объект"
    flag_openEdit--;
}


void Xpars::PushButton_TU()
{
    NewPole(BUT); //Кнопка ТУ
}

void Xpars::PushButton_ZAZ()
{
    NewPole(ZAZEM); //Заземление
}

void Xpars::PushButton_RUB_G()
{
    NewPole(LINE4); //Рубильник горизонтальный
}

void Xpars::PushButton_RUB_V()
{
    NewPole(LINE3); //Рубильник вертикальный
}

void Xpars::PushButton_RUB1_G()
{
    NewPole(LINE2); //Ручной автомат горизонтальный
}

void Xpars::PushButton_RUB1_V()
{
    NewPole(LINE1); //Ручной автомат вертикальный
}

void Xpars::PushButton_U_TXT()
{
    NewPole(TXTU); //Текст управления ТУ
}

void Xpars::PushButton_OUT()
{
    NewPole(OUT); //Окно ТИ
}

void Xpars::PushButton_F_BUT()
{
    NewPole(PUSHF); //Кнопка с фиксацией
}

void Xpars::PushButton_NF_BUT()
{
    NewPole(PUSH); //Кнопка без фиксации
}

void Xpars::PushButton_LAMP()
{
    NewPole(LAMP); //Лампа
}

void Xpars::PushButton_RECT()
{
    NewPole(RECT1); //Прямоугольник без текста ТС
}

void Xpars::PushButton_RECT4()
{
    NewPole(RECT4); //Прямоугольник с 4 состояниями
}

void Xpars::PushButton_T_RECT()
{
    NewPole(RECT); //Прямоугольник с текстом ТС
}

void Xpars::PushButton_TXT()
{
    NewPole(TXT); //Текст
}

void Xpars::PushButton_OUT_TM()
{
    NewPole(OUT_TEM_74); //Окно ТИ ТЭМ-74
}

void Xpars::PushButton_NEXT()
{
    NewPole(NEXT); //Следующая станция
}

void Xpars::PushButton_PREV()
{
    NewPole(PREV); //Предыдущая станция
}

void Xpars::PushButton_UP_W()
{
    NewPole(UP_W); //Предыдущее окно
}

void Xpars::PushButton_DOWN_W()
{
    NewPole(DOWN_W); //Следующее окно
}

void Xpars::PushButton_STATION()
{
    NewPole(STATION); //Показать станцию
}

void Xpars::PushButton_SHOW_L()
{
    NewPole(SHOW_L); //Показать верхний уровень
}

void Xpars::PushButton_HIDE_T()
{
    NewPole(HIDE_T); //Закрывать надпись
}

void Xpars::PushButton_RECTM()
{
    NewPole(RECTM); //Двойное псевдо
}
void Xpars::PushButton_SIGNAL_M()
{
    NewPole(SIGNAL_M); //Индикация изменений
}
void Xpars::PushButton_STATION_P()
{
    NewPole(STATION_P); //Показать программу экстренного снятия
}

void Xpars::NewPole(const int &type)
{
    if (mnemo_file_name == "") return;

    int id_st, id_win, i, y, flag_st, flag_win;
    flag_st=0;
    flag_win = 0;
    i=-1;
    i = ui->tableWidget->currentRow();

    if (i < 0) return;

    QTableWidgetItem *Iitems = new QTableWidgetItem;
    Iitems = ui->tableWidget->item(i,3);

    y = Iitems->text().toInt(); //Номер выделенного объекта

    for (int ii=0; ii< object[y-1].station_cnt; ii++)
    {
        if (object[y-1].st[ii].st_num == tt_station)
        {
            flag_st=1;

            for (int yy = 0; yy < object[y-1].st[ii].win_cnt; yy++)
            {
                if (object[y-1].st[ii].win[yy].win_num == tt_win)
                {
                    flag_win = 1;

                    id_st = ii;
                    id_win = yy;

                    break;
                }
            }

            if (flag_win == 0)
            {
                id_st = ii;
                id_win = object[y-1].st[ii].win_cnt;

                object[y-1].st[ii].win_cnt++;
                break;
            }
        }
    }

    if ((flag_win == 0) && (flag_st == 0))
    {
        id_st = object[y-1].station_cnt;
        id_win = object[y-1].st[object[y-1].station_cnt].win_cnt;

        object[y-1].st[object[y-1].station_cnt].win_cnt++;

        object[y-1].st[object[y-1].station_cnt].st_num = tt_station;
        object[y-1].station_cnt++;
    }

    object[y-1].st[id_st].win[id_win].type = type;
    object[y-1].st[id_st].win[id_win].X = 0;
    object[y-1].st[id_st].win[id_win].Y = 0;
    object[y-1].st[id_st].win[id_win].im_X = 0;
    object[y-1].st[id_st].win[id_win].im_Y = 0;
    object[y-1].st[id_st].win[id_win].win_num = tt_win;

    switch (type)
    {
    case BUT:
        {
            object[y-1].st[id_st].win[id_win].W = 20;
            object[y-1].st[id_st].win[id_win].H = 20;
            object[y-1].st[id_st].win[id_win].im_W = 20;
            object[y-1].st[id_st].win[id_win].im_H = 20;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    case LAMP:      //Лампа
        {
            object[y-1].st[id_st].win[id_win].W = 8;
            object[y-1].st[id_st].win[id_win].H = 8;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    case TXT:
        {
            object[y-1].st[id_st].win[id_win].W = 0;
            object[y-1].st[id_st].win[id_win].H = 0;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;          
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#ff0000";
            object[y-1].st[id_st].win[id_win].color_off = "#ffffff";

            OutDateScene();
        }
        break;
    case TXTU:
        {
            object[y-1].st[id_st].win[id_win].W = 0;
            object[y-1].st[id_st].win[id_win].H = 0;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#ffff00";
            object[y-1].st[id_st].win[id_win].color_off = "#000000";

            OutDateScene();
        }
        break;
    case OUT:
    case OUT_TEM_74:
        {
            object[y-1].st[id_st].win[id_win].W = 30;
            object[y-1].st[id_st].win[id_win].H = 14;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    case RECT:      //Прямоугольник с текстом ТС
        {
            object[y-1].st[id_st].win[id_win].W = 38;
            object[y-1].st[id_st].win[id_win].H = 20;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 10;
            object[y-1].st[id_st].win[id_win].color_on = "#ffff00";
            object[y-1].st[id_st].win[id_win].color_off = "#787878";

            OutDateScene();
        }
        break;
    case PUSH:      //Кнопка без фиксации
        {
            object[y-1].st[id_st].win[id_win].W = 34;
            object[y-1].st[id_st].win[id_win].H = 15;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#737373";
            object[y-1].st[id_st].win[id_win].color_off = "#737373";

            OutDateScene();
        }
        break;
    case PUSHF:     //Кнопка c фиксации
        {
            object[y-1].st[id_st].win[id_win].W = 34;
            object[y-1].st[id_st].win[id_win].H = 15;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#737373";

            OutDateScene();
        }
        break;
    case SIGNAL_M:  //Индикация изменений
        {
            object[y-1].st[id_st].win[id_win].W = 26;
            object[y-1].st[id_st].win[id_win].H = 13;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 8;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    case RECTM:     //Двойное псевдо
        {
            object[y-1].st[id_st].win[id_win].W = 10;
            object[y-1].st[id_st].win[id_win].H = 20;
            object[y-1].st[id_st].win[id_win].im_W = 10;
            object[y-1].st[id_st].win[id_win].im_H = 20;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#aa0000";
            object[y-1].st[id_st].win[id_win].color_off = "#aa0000";

            OutDateScene();
        }
        break;
    case RECT1:     //Прямоугольник без текста ТС
    case RECT4:     //Прямоугольник с 4 состояниями
        {
            object[y-1].st[id_st].win[id_win].W = 100;
            object[y-1].st[id_st].win[id_win].H = 6;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#ffff00";

            OutDateScene();
        }
        break;
    case HIDE_T:    //Закрывать надпись
        {
            object[y-1].st[id_st].win[id_win].W = 70;
            object[y-1].st[id_st].win[id_win].H = 15;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#ffffff";
            object[y-1].st[id_st].win[id_win].color_off = "#ffffff";

            OutDateScene();
        }
        break;
    case NEXT:      //Следующая станция
    case PREV:      //Предыдущая станция
        {
            object[y-1].st[id_st].win[id_win].W = 30;
            object[y-1].st[id_st].win[id_win].H = 40;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#000000";

            OutDateScene();
        }
        break;
    case UP_W:      //Предыдущее окно
    case DOWN_W:    //Следующее окно
        {
            object[y-1].st[id_st].win[id_win].W = 40;
            object[y-1].st[id_st].win[id_win].H = 30;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#000000";

            OutDateScene();
        }
        break;
    case STATION:   //Показать станцию
    case STATION_P: //Показать программу экстренного снятия
        {
            object[y-1].st[id_st].win[id_win].W = 70;
            object[y-1].st[id_st].win[id_win].H = 20;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#000000";

            OutDateScene();
        }
        break;
    case SHOW_L:    //Показать верхний уровень
        {
            object[y-1].st[id_st].win[id_win].W = 40;
            object[y-1].st[id_st].win[id_win].H = 60;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#000000";
            object[y-1].st[id_st].win[id_win].color_off = "#000000";

            OutDateScene();
        }
        break;
    case ZAZEM:     //Заземление
        {
            object[y-1].st[id_st].win[id_win].W = 14;
            object[y-1].st[id_st].win[id_win].H = 16;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#737373";
            object[y-1].st[id_st].win[id_win].color_off = "#b0b0b0";

            OutDateScene();
        }
        break;
    case LINE1:     //Ручной автомат вертикальный
    case LINE3:     //Рубильник вертикальный
        {
            object[y-1].st[id_st].win[id_win].W = 15;
            object[y-1].st[id_st].win[id_win].H = 22;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    case LINE2:     //Ручной автомат горизонтальный
    case LINE4:     //Рубильник горизонтальный
        {
            object[y-1].st[id_st].win[id_win].W = 22;
            object[y-1].st[id_st].win[id_win].H = 15;
            object[y-1].st[id_st].win[id_win].im_W = 0;
            object[y-1].st[id_st].win[id_win].im_H = 0;
            object[y-1].st[id_st].win[id_win].font = 0;
            object[y-1].st[id_st].win[id_win].color_on = "#00ff00";
            object[y-1].st[id_st].win[id_win].color_off = "#ff0000";

            OutDateScene();
        }
        break;
    }
}

void Xpars::ShowAbout()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("О программе");
    msgBox.setFixedSize(200,200);
    msgBox.setIconPixmap(QPixmap("logo_niivk.gif"));
    msgBox.setText("Версия 11.2017\n\nАО НИИВК им. М.А. Карцева\nhttp://niivk.ru/\n\nАвтор: Вахновецкий Я.И.\nVakhnovetsky@mail.ru");
    msgBox.exec();
}

void Xpars::KillAllPole()
{
    if (tt_station <0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setFixedSize(200,200);
        msgBox.setText("Удаление полей на мнемосхеме невозможно. Откройте необходимую мнемосхему!\n");
        msgBox.exec();

        return;
    }
    emit signal_KillAllPole();
}

void Xpars::load_stativ()
{
    QString kp_text, bufer_text, name_file_stativ, stativ_text;
    QFile file_kp("kp.cfg");
    int i, i_bufer, n_stativ, n_stroka_stativ_file;

    QTextStream stream(&file_kp);

    if(file_kp.open( QIODevice::ReadOnly ))
    {
        n_stativ = -1;
        kp_text = stream.readLine(); //Считаваем строку из файла. При каждом таком чтении считывается следующая строка!

        while (!kp_text.isEmpty())
        {
            if ((kp_text.indexOf("#") == -1) && (kp_text.indexOf(" ") == -1))
            {
                n_stativ++;
                i_bufer = 0;
                for (i=0; i<kp_text.length(); i++)
                {
                    if (kp_text[i] != ':')
                    {
                        bufer_text += kp_text[i];
                    }
                    else
                    {
                        switch (i_bufer)
                        {
                        case 0:
                            {
                                kp_cfg[n_stativ].telemehanika = bufer_text.toInt();
                            }
                        case 1:
                            {
                                kp_cfg[n_stativ].num_stativ = bufer_text.toInt();
                            }
                        case 2:
                            {
                                kp_cfg[n_stativ].port1 = bufer_text;
                            }
                        case 3:
                            {
                                kp_cfg[n_stativ].port2 = bufer_text;
                            }
                        case 4:
                            {
                                kp_cfg[n_stativ].port3 = bufer_text;
                            }
                        case 5:
                            {
                                kp_cfg[n_stativ].port4 = bufer_text;
                            }
                        case 6:
                            {
                                kp_cfg[n_stativ].speed = bufer_text.toInt();
                            }
                        case 7:
                            {
                                kp_cfg[n_stativ].chotnost = bufer_text.toInt();
                            }
                        case 8:
                            {
                                kp_cfg[n_stativ].stopbit = bufer_text.toInt();
                            }
                        case 9:
                            {
                                kp_cfg[n_stativ].amount_kp = bufer_text.toInt();
                            }
                        break;
                        }

                        bufer_text = "";
                        i_bufer++;

                    }
                }
            }
            kp_text = stream.readLine();
        }
        file_kp.close();
    }
    else
        {
        QMessageBox msgBox44;
        msgBox44.setText("Отсутсвует файл kp.cfg");
        msgBox44.exec();

        return;
        }

    //Теперь надо считать файлы Stativ!

    for (int i_stativ = 0; i_stativ<=n_stativ; i_stativ++)
    {
        name_file_stativ = "stativ"+QString::number(kp_cfg[i_stativ].num_stativ)+".cfg";
        QFile file_stativ(name_file_stativ);

        n_stroka_stativ_file = -1;
        bufer_text.clear();

        if(file_stativ.open( QIODevice::ReadOnly ))
        {
            QTextStream stream_stativ(&file_stativ);

            stativ_text = stream_stativ.readLine();

            while (!stativ_text.isEmpty()) //Бегаем по строкам файла
            {

                if ((stativ_text.indexOf("#") == -1)) //Откидываем строки - комментарии
                {
                    n_stroka_stativ_file++;
                    i_bufer = 0;

                    for (i=0; i<stativ_text.length(); i++)
                    {
                        if (stativ_text[i] != ':')
                        {
                            bufer_text += stativ_text[i];
                        }
                        else
                        {
                            switch (i_bufer)
                            {
                            case 0:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].kp_log_number = bufer_text.toInt();
                                }

                            case 1:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].kp_fiz1_number = bufer_text.toInt();
                                }

                            case 2:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].kp_fiz2_number = bufer_text.toInt();
                                }

                            case 3:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].TS = bufer_text.toInt();
                                }

                            case 4:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].TU = bufer_text.toInt();
                                }

                            case 5:
                                {
                                    kp_cfg[i_stativ].stativ[n_stroka_stativ_file].TI = bufer_text.toInt();
                                }
                            break;
                            }
                             bufer_text.clear();
                             i_bufer++;
                        }
                    }
                }
                stativ_text = stream_stativ.readLine();
            }
            file_stativ.close();
        }
        else
        {
            QMessageBox msgBox44;
            msgBox44.setText("Отсутсвует файл "+name_file_stativ);
            msgBox44.exec();
            return;
        }
    }
}

void Xpars::Slot_notShowSetka()
{
    QMessageBox msgBox13;
    msgBox13.setText("Сетка не работает");
    msgBox13.exec();
}

QString Xpars::Translate(const QString &str)
{
    QString fn;
    int i, rU, rL;
    QString validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_,()[]{}<>~!@#$%^&*+=?";
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
    QString rusUpper = QObject::tr("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ");
    QString rusLower = QObject::tr("абвгдеёжзийклмнопрстуфхцчшщыэюя");


    QStringList latUpper, latLower;
    latUpper <<"A"<<"B"<<"V"<<"G"<<"D"<<"E"<<"Jo"<<"Zh"<<"Z"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
             <<"O"<<"P"<<"R"<<"S"<<"T"<<"U"<<"F"<<"H"<<"C"<<"Ch"<<"Sh"<<"Sh"<<"I"<<"E"<<"Ju"<<"Ja";
    latLower <<"a"<<"b"<<"v"<<"g"<<"d"<<"e"<<"jo"<<"zh"<<"z"<<"i"<<"j"<<"k"<<"l"<<"m"<<"n"
                    <<"o"<<"p"<<"r"<<"s"<<"t"<<"u"<<"f"<<"h"<<"c"<<"ch"<<"sh"<<"sh"<<"i"<<"e"<<"ju"<<"ja";
    for (i=0; i < str.size(); i++)
    {
         if ( validChars.contains(str[i]) )
         {
             fn = fn + str[i];
         }
         else
            if (str[i] == ' ')
            {
            }
            else
            {
                rU = rusUpper.indexOf(str[i]);
                rL = rusLower.indexOf(str[i]);
                if (rU >= 0)
                    fn = fn + latUpper[rU];
                else
                    if (rL >= 0)
                        fn = fn + latLower[rL];
            }
            rU = -1;
            rL = -1;
   }
   return fn;
}

void Xpars::SlotPosMouse(const int &x, const int &y)
{
    status_PosMouse->setText("                   (" + QString::number(x) + ";" + QString::number(y) + ")                   ");
}
