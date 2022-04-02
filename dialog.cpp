#include "dialog.h"
#include "ui_dialog.h"
#include "xpars.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int Dialog::getStation()
{
    int station = ui->lineEdit_station->text().toInt();
    return station;
}

QString Dialog::getName()
{
    QString name = ui->lineEdit_name->text();
    return name;
}

QString Dialog::getSlang()
{
    QString slang = ui->lineEdit_slang->text();
    return slang;
}

int Dialog::getType()
{
    int type = ui->lineEdit_type->text().toInt();
    return type;
}

int Dialog::getSubtype()
{
    int subtype = ui->lineEdit_subtype->text().toInt();
    return subtype;
}

int Dialog::getLine()
{
    int line = ui->lineEdit_line->text().toInt();
    return line;
}

int Dialog::getKptsoff()
{
    int kptsoff = ui->lineEdit_kptsoff->text().toInt();
    return kptsoff;
}

int Dialog::getTsoff()
{
    int tsoff = ui->lineEdit_tsoff->text().toInt();
    return tsoff;
}

int Dialog::getKptson()
{
    int kptson = ui->lineEdit_kptson->text().toInt();
    return kptson;
}

int Dialog::getTson()
{
    int tson = ui->lineEdit_tson->text().toInt();
    return tson;
}

int Dialog::getKptuon()
{
    int kptuon = ui->lineEdit_kptuon->text().toInt();
    return kptuon;
}

int Dialog::getTu1on()
{
    int tu1on = ui->lineEdit_tu1on->text().toInt();
    return tu1on;
}

int Dialog::getTu2on()
{
    int tu2on = ui->lineEdit_tu2on->text().toInt();
    return tu2on;
}

int Dialog::getTstuon()
{
    int tstuon = ui->lineEdit_tstuon->text().toInt();
    return tstuon;
}

int Dialog::getKptuoff()
{
    int kptuoff = ui->lineEdit_kptuoff->text().toInt();
    return kptuoff;
}

int Dialog::getTu1off()
{
    int tu1off = ui->lineEdit_tu1off->text().toInt();
    return tu1off;
}

int Dialog::getTu2off()
{
    int tu2off = ui->lineEdit_tu2off->text().toInt();
    return tu2off;
}

int Dialog::getTstuoff()
{
    int tstuoff = ui->lineEdit_tstuoff->text().toInt();
    return tstuoff;
}

int Dialog::getMin_value()
{
    int min_value = ui->lineEdit_min_value->text().toInt(); //минимально домустимое значение (ТИ)
    return min_value;
}

int Dialog::getMax_value()
{
    int max_value = ui->lineEdit_max_value->text().toInt(); //максимально допустимое значение (ТИ)
    return max_value;
}

int Dialog::getRing()
{
    int ring = ui->lineEdit_ring->text().toInt(); // признак выдачи звукового сигнала при выходе значения за допустимые пределы (ТИ)
    return ring;
}

int Dialog::getK_value()
{
    int k_value = ui->lineEdit_k_value->text().toInt(); // коэффициент пересчета (ТИ)
    return k_value;
}

int Dialog::getKou()
{
    int kou;
    if (ui->checkBox_kou->isChecked())
        kou = 1; // признак блокировки управления объктом кномки КОУ
        else kou = 0;
    return kou;
}

int Dialog::getKds()
{
    int kds;
    if (ui->checkBox_kds->isChecked())
        kds = 1; // признак блокировки управления объктом кномки КДС
        else
        kds = 0;
    return kds;
}

int Dialog::getGroup()
{
    int group = ui->lineEdit_group->text().toInt();  // номер группового управления, в которую входит объект
    return group;
}

void Dialog::outStation(int &Station)
{
    ui->lineEdit_station->setText(QString::number(Station));
}

void Dialog::outName(QString &Name)
{
    ui->lineEdit_name->setText(Name);
}

void Dialog::outSlang(QString &Slang)
{
    ui->lineEdit_slang->setText(Slang);
}

void Dialog::outType(int &Type)
{
    ui->lineEdit_type->setText(QString::number(Type));
}

void Dialog::outSubtype(int &Subtype)
{
    ui->lineEdit_subtype->setText(QString::number(Subtype));
}

void Dialog::outLine(int &Line)
{
    ui->lineEdit_line->setText(QString::number(Line));
}

void Dialog::outKptsoff(int &Kptsoff)
{
    ui->lineEdit_kptsoff->setText(QString::number(Kptsoff));
}

void Dialog::outTsoff(int &Tsoff)
{
    ui->lineEdit_tsoff->setText(QString::number(Tsoff));
}

void Dialog::outKptson(int &Kptson)
{
    ui->lineEdit_kptson->setText(QString::number(Kptson));
}

void Dialog::outTson(int &Tson)
{
    ui->lineEdit_tson->setText(QString::number(Tson));
}

void Dialog::outKptuon(int &Kptuon)
{
    ui->lineEdit_kptuon->setText(QString::number(Kptuon));
}

void Dialog::outTu1on(int &Tu1on)
{
    ui->lineEdit_tu1on->setText(QString::number(Tu1on));
}

void Dialog::outTu2on(int &Tu2on)
{
    ui->lineEdit_tu2on->setText(QString::number(Tu2on));
}

void Dialog::outTstuon(int &Tstuon)
{
    ui->lineEdit_tstuon->setText(QString::number(Tstuon));
}

void Dialog::outKptuoff(int &Kptuoff)
{
    ui->lineEdit_kptuoff->setText(QString::number(Kptuoff));
}

void Dialog::outTu1off(int &Tu1off)
{
    ui->lineEdit_tu1off->setText(QString::number(Tu1off));
}

void Dialog::outTu2off(int &Tu2off)
{
    ui->lineEdit_tu2off->setText(QString::number(Tu2off));
}

void Dialog::outTstuoff(int &Tstuoff)
{
    ui->lineEdit_tstuoff->setText(QString::number(Tstuoff));
}

void Dialog::outMin_value(int &Min_value)
{
    ui->lineEdit_min_value->setText(QString::number(Min_value));
}

void Dialog::outMax_value(int &Max_value)
{
    ui->lineEdit_max_value->setText(QString::number(Max_value));
}

void Dialog::outRing(int &Ring)
{
    ui->lineEdit_ring->setText(QString::number(Ring));
}

void Dialog::outK_value(int &K_value)
{
    ui->lineEdit_k_value->setText(QString::number(K_value));
}

void Dialog::outKou(int &Kou)
{
    if (Kou == 1)
    {
        ui->checkBox_kou->setChecked(true);
    }
}

void Dialog::outKds(int &Kds)
{
    if (Kds == 1)
    {
        ui->checkBox_kds->setChecked(true);
    }
}

void Dialog::outGroup(int &Group)
{
    ui->lineEdit_group->setText(QString::number(Group));
}
