#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QMessageBox>
#include <QMap>

// ���� ����������� �������� pole
#define BUT		1       //������ ��
#define RECT		2       //������������� � ������� ��
#define TXT		4       //�����
#define OUT		5       //���� ��
#define LINE1		6	//������ ������� ������������
#define LINE2		7	//������ ������� ��������������
#define ZAZEM		8       //����������
#define LINE3		9	//��������� ������������
#define LINE4		10	//��������� ��������������
#define LAMP		11      //�����
#define RECT1		12      //������������� ��� ������ ��
#define BUTP		13      // ????
#define PUSH		14	//������ ��� ��������
#define PUSHF		15	//������ � ���������
#define RECTM		16      //������� ������
#define TXTU		17      //����� ���������� ��
#define NEXT		18	//��������� �������
#define PREV		19	//���������� �������
#define UP_W		20	//���������� ����
#define DOWN_W		21	//��������� ����
#define STATION		22	//�������� �������
#define SHOW_L		23	//�������� ������� �������
#define HIDE_T		24	//��������� �������
#define SIGNAL_M	25	//��������� ���������
#define STATION_P	26	//�������� ��������� ����������� ������
#define TXTM		27      // ???
#define NOTKP           28	//������ ����� � �� ???
#define RECT4           29	//������������� � 4 �����������
#define OUT_TEM_74      30	//���� �� ���-74

struct ob_pole
{
    int n_curObj; //����� �������
    QString slang;
    int type_object;
    int subtype_object;
    int type; //��� �����������
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
    QGraphicsRectItem *b; //��������� �� ������
    QGraphicsRectItem *b0; //��������� �� ������
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

    QString name_mn; //��� ������� ��������
    int n_pole; //���������� ����� �� ��������
    QPointF PosMouse; //������� �����

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
    int tt_number; //������� ����
    QMessageBox *pmbx;

    int flag, dx, dy; //���� ���������� ������������ ������� �����.

    int flag_setka; //���� ��� ��������� �����

private slots:
    void SlotNameMnemo(const QString& mnemo_n_f);
    void SlotAdd_pole(const QString& slang, const int& n_curObj, const int&type_object, const int&subtype_object, const int& type, const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SlotZero_n_pole(const int& n);
    void Slotact_paint();
    void Slot_KillAllPole();
    void Slot_ShowSetka();

signals:
    void SignalCurNum(const int& CurNum); //�������� �������� ������ ������� � ����� Xpars ��� ����������� � ������ ���������
    void SignalOpenEdit(const int& OpenNum); //����������� ������ ����������� ������� � ����� Xpars ��� �������� ���� ���������� �������
    void SignalOutPole(const int& X, const int& Y, const int& W, const int& H, const int& im_X, const int& im_Y, const int& im_W, const int& im_H, const int& font, const QString& color_on, const QString& color_off);
    void SignalDelNumPole(const int & DelNumPole); //�������� ������ ������� � ����� Xpars ��� ����������� ���� �������
    void SignalPosMouse(const int& x, const int & y);
};

#endif // MYSCENE_H
