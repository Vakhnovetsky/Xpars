#include "mywidj.h"
#include "ui_mywidj.h"

MyWidj::MyWidj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidj)
{
    ui->setupUi(this);

    scene = new MyScene;
    ui->graphicsView->setScene(scene);

    setMouseTracking(true);


    connect(this, SIGNAL(MnemoSignal(QString)), scene, SLOT(SlotNameMnemo(QString)));
    connect(this, SIGNAL(SignalZero(int)), scene, SLOT(SlotZero_n_pole(int)));
    connect(this, SIGNAL(SignalMap(QString,int, int, int, int, int,int,int,int,int,int,int,int,int,QString,QString)), scene, SLOT(SlotAdd_pole(QString,int,int,int, int, int,int,int,int,int,int,int,int,int,QString,QString)));
    connect(this, SIGNAL(SignalPaint()), scene, SLOT(Slotact_paint()));
    connect(this, SIGNAL(Signal__KillAllPole()), scene, SLOT(Slot_KillAllPole()));
    connect(this, SIGNAL(Signal_ShowSetka()), scene, SLOT(Slot_ShowSetka()));

    connect(scene, SIGNAL(SignalCurNum(int)), this, SLOT(SlotOutNumObj(int)));
    connect(scene, SIGNAL(SignalOpenEdit(int)), this, SLOT(SlotOpenEdit(int)));

    connect(scene, SIGNAL(SignalOutPole(int,int,int,int,int,int,int,int,int,QString,QString)), this, SLOT(SlotOutPole(int,int,int,int,int,int,int,int,int,QString,QString)));
    connect(scene, SIGNAL(SignalDelNumPole(int)), this, SLOT(SlotDelNumPole(int)));
    connect(scene, SIGNAL(SignalPosMouse(int, int)), this, SLOT(SlotPosMouse(int, int)));
}

void MyWidj::NameMnemo(const QString &name)
{
    emit MnemoSignal(name);
}

void MyWidj::Zero_n_pole(const int &n)
{
    emit SignalZero(n);
}

void MyWidj::act_paint()
{
    emit SignalPaint();
}

void MyWidj::Add_pole(const QString &slang, const int &n_curObj, const int&type_object, const int&subtype_object, const int &type, const int &X, const int &Y, const int &W, const int &H, const int &im_X, const int &im_Y, const int &im_W, const int &im_H, const int &font, const QString &color_on, const QString &color_off)
{
    emit SignalMap(slang, n_curObj, type_object, subtype_object, type, X, Y, W, H, im_X, im_Y, im_W, im_H, font, color_on, color_off);
}

void MyWidj::SlotOutNumObj(const int &CurNum)
{
    emit SignalOutNumObj(CurNum);
}

void MyWidj::SlotOpenEdit(const int &OpenNum)
{
    emit SignalOpenEdit(OpenNum);
}

void MyWidj::SlotOutPole(const int &X, const int &Y, const int &W, const int &H, const int &im_X, const int &im_Y, const int &im_W, const int &im_H, const int &font, const QString &color_on, const QString &color_off)
{
    emit SignalOutPole(X, Y, W, H, im_X, im_Y, im_W, im_H, font, color_on, color_off);
}

void MyWidj::SlotDelNumPole(const int &DelNumPole)
{
    emit SignalDelNumPole(DelNumPole);
}

void MyWidj::Slot_KillAllPole()
{
    emit Signal__KillAllPole();
}

void MyWidj::Slot_ShowSetka()
{
    emit Signal_ShowSetka();
}

void MyWidj::SlotPosMouse(const int &x, const int &y)
{
    emit SignalPosMouse(x, y);
}


MyWidj::~MyWidj()
{
    delete ui;
}

void MyWidj::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
