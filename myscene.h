#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QMessageBox>
#include <QMap>

// Типы отображения объектов pole
#define BUT		1       //Кнопка ТУ
#define RECT		2       //Прямоугольник с текстом ТС
#define TXT		4       //Текст
#define OUT		5       //Окно ТИ
#define LINE1		6	//Ручной автомат вертикальный
#define LINE2		7	//Ручной автомат горизонтальный
#define ZAZEM		8       //Заземление
#define LINE3		9	//Рубильник вертикальный
#define LINE4		10	//Рубильник горизонтальный
#define LAMP		11      //Лампа
#define RECT1		12      //Прямоугольник без текста ТС
#define BUTP		13      // ????
#define PUSH		14	//Кнопка без фиксации
#define PUSHF		15	//Кнопка с фиксацией
#define RECTM		16      //Двойное псевдо
#define TXTU		17      //Текст управления ТУ
#define NEXT		18	//Следующая станция
#define PREV		19	//Предыдущая станция
#define UP_W		20	//Предыдущее окно
#define DOWN_W		21	//Следующее окно
#define STATION		22	//Показать станцию
#define SHOW_L		23	//Показать верхний уровень
#define HIDE_T		24	//Закрывать надпись
#define SIGNAL_M	25	//Индикация изменений
#define STATION_P	26	//Показать программу экстренного снятия
#define TXTM		27      // ???
#define NOTKP           28	//Потеря связи с КП ???
#define RECT4           29	//Прямоугольник с 4 состояниями
#define OUT_TEM_74      30	//Окно ТИ ТЭМ-74

struct ob_pole
{
    int n_curObj; //Номер объекта
    QString slang;
    int type_object;
    int subtype_object;
    int type; //Тип отображения
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
    QGraphicsRectItem *b; //Указатель на объект
    QGraphicsRectItem *b0; //Указатель на объект
    QGraphicsEllipseItem *b1;
    QGraphicsTextItem *b2;

};

class MyScene : public QGraphicsScene
{
Q_OBJECT
public:
    explicit MyScene(QObject *parent = 0);

    void Paint();
    void RePaint(int& i);

    void drawButton(const int& i);
    void drawCircle(const int& i);
    void drawText(const int& i);
    void drawOut(const int& i);
    void drawRectangle(const int& i);
    void drawPole(const int& i);

    QString name_mn; //Имя текущей подложки
    int n_pole; //количество полей на картинке
    QPointF PosMouse; //Позиция мышки

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsItem * item;
    QGraphicsEllipseItem *p;
    QMap <int, ob_pole> pole;
    int tt_number; //Текущее поле
    QMessageBox *pmbx;

    int flag, dx, dy; //Флаг разрешение передвижения объекта мышью.

    int flag_setka; //Флаг для отрисовки сетки

private slots:
    void SlotNameMnemo(const QString& mnemo_n_f);
    void SlotAdd_pole(const QString& slang, const int& n_curObj, const int&type_object, const int&subtype_object, const int& type, const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SlotZero_n_pole(const int& n);
    void Slotact_paint();
    void Slot_KillAllPole();
    void Slot_ShowSetka();

signals:
    void SignalCurNum(const int& CurNum); //Передача текущего номера объекта в класс Xpars для отображения в строке состояния
    void SignalOpenEdit(const int& OpenNum); //Отправление номера выделенного объекта в класс Xpars для открытия окна параметров объекта
    void SignalOutPole(const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SignalDelNumPole(const int & DelNumPole); //Передача номера объекта в класс Xpars для уничтожения поля объекта
    void SignalPosMouse(const int& x, const int & y);
};

#endif // MYSCENE_H
