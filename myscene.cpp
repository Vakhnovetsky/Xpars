#include "myscene.h"
#include <QGraphicsScene>
#include "mywidj.h"
#include <QGraphicsView>
#include <QGraphicsSceneEvent>
#include <QGraphicsItem>
#include <QKeyEvent>

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 1008, 684);
    n_pole = 0;
    flag = 0;
    dx = 0;
    dy = 0;

    flag_setka = 0;

    tt_number = -1;

    Paint();
}

void MyScene::SlotNameMnemo(const QString &name)
{
    name_mn = name;

    Paint();
}

void MyScene::SlotZero_n_pole(const int &n)
{
    n_pole = n;
}

void MyScene::SlotAdd_pole(const QString &slang, const int &n_curObj, const int&type_object, const int&subtype_object, const int &type, const int &X, const int &Y, const int &W, const int &H, const int &im_X, const int &im_Y, const int &im_W, const int &im_H, const int &font, const QString &color_on, const QString &color_off)
{
    n_pole++;

    pole[n_pole].slang = slang;
    pole[n_pole].n_curObj = n_curObj;
    pole[n_pole].type_object = type_object;
    pole[n_pole].subtype_object = subtype_object;
    pole[n_pole].type = type;
    pole[n_pole].X = X;
    pole[n_pole].Y = Y;
    pole[n_pole].W = W;
    pole[n_pole].H = H;
    pole[n_pole].im_X = im_X;
    pole[n_pole].im_Y = im_Y;
    pole[n_pole].im_W = im_W;
    pole[n_pole].im_H = im_H;
    pole[n_pole].font = font;
    pole[n_pole].color_on = color_on;
    pole[n_pole].color_off = color_off;
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        if (pole[tt_number].n_curObj<1) return;
        emit SignalOpenEdit(pole[tt_number].n_curObj); //Отправление номера выделенного объекта в класс Xpars для открытия окна параметров объекта
    }

}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int old_tt_number;

    old_tt_number = tt_number;

    tt_number = -1;
    if (mouseEvent->button() == Qt::LeftButton)
    {
            QGraphicsItem * item = itemAt(mouseEvent->scenePos());
            tt_number = item->data(0).toInt();

            emit SignalCurNum(pole[tt_number].n_curObj); //Отправление номера выделенного объекта в класс Xpars для отображения в строке состояния

            if (tt_number == 0)
            {
                RePaint(old_tt_number);
                return; 
            }

            if (tt_number != old_tt_number)
            {
                RePaint(old_tt_number);
            }

            RePaint(tt_number);

            PosMouse = mouseEvent->scenePos();
            dx = PosMouse.x() - pole[tt_number].X;
            dy = PosMouse.y() - pole[tt_number].Y;

            flag = 1;

            //Отправление свойств поля выделенного объекта в класс Xpars для отображения в окне свойств

            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
    }


    if (mouseEvent->button() == Qt::RightButton)
    {
        QGraphicsItem * item = itemAt(mouseEvent->scenePos());
        int tt_n = item->data(0).toInt();

        emit SignalCurNum(pole[tt_n].n_curObj); //Отправление номера выделенного объекта в класс Xpars для отображения в строке состояния

        RePaint(old_tt_number); //Убираю выделение поля объекта

        if (tt_n > 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Вы действительно хотите удалить поле объекта №" + QString::number(pole[tt_n].n_curObj) + "?");
            msgBox.setWindowTitle("Удаление поля объекта");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            int n_del = msgBox.exec();

            if (n_del == QMessageBox::Yes)
            {
                emit SignalDelNumPole(pole[tt_n].n_curObj); //Функция передачи номера объекта в класс Xpars для уничтожения поля.

                for (int i = tt_n; i<=n_pole; i++)
                {
                    pole[i].slang = pole[i+1].slang;
                    pole[i].n_curObj = pole[i+1].n_curObj;
                    pole[i].type = pole[i+1].type;
                    pole[i].X = pole[i+1].X;
                    pole[i].Y = pole[i+1].Y;
                    pole[i].W = pole[i+1].W;
                    pole[i].H = pole[i+1].H;
                    pole[i].im_X = pole[i+1].im_X;
                    pole[i].im_Y = pole[i+1].im_Y;
                    pole[i].im_W = pole[i+1].im_W;
                    pole[i].im_H = pole[i+1].im_H;
                    pole[i].font = pole[i+1].font;
                    pole[i].color_on = pole[i+1].color_on;
                    pole[i].color_off = pole[i+1].color_off;
                    pole[i].b0 = pole[i+1].b0;
                    pole[i].b = pole[i+1].b;
                    pole[i].b1 = pole[i+1].b1;
                    pole[i].b2 = pole[i+1].b2;
                }

                pole.remove(n_pole);

                n_pole--;

                tt_number = -1;

                Paint();

            }
            else
            {
                tt_number = -1;
                emit SignalCurNum(tt_number); //Отправление номера выделенного объекта в класс Xpars для отображения в строке состояния
            }
        }
        else
        {
            tt_number = -1;
            emit SignalCurNum(tt_number); //Отправление номера выделенного объекта в класс Xpars для отображения в строке состояния
        }
    }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    PosMouse = mouseEvent->scenePos();

    emit SignalPosMouse(PosMouse.x(), PosMouse.y());


    if (tt_number <= 0) return;

    if (flag == 1)
    {
        switch (pole[tt_number].type)
        {
            case BUT:          //Кнопка ТУ
            case RECT:         //Прямоугольник с текстом ТС
            case PUSH:         //Кнопка без фиксации
            case PUSHF:        //Кнопка с фиксацией
            case SIGNAL_M:     //Индикация изменений
            {
                pole[tt_number].im_X = PosMouse.x() - dx;
                pole[tt_number].X = PosMouse.x() - dx;
                pole[tt_number].im_Y = PosMouse.y() - dy;
                pole[tt_number].Y = PosMouse.y() - dy;

            }
                break;
            case RECTM:        //Двойное псевдо
            {
                    int mm_x = pole[tt_number].im_X - pole[tt_number].X;
                    int mm_y = pole[tt_number].im_Y - pole[tt_number].Y;
                    pole[tt_number].im_X = PosMouse.x() + mm_x - dx;
                    pole[tt_number].X = PosMouse.x() - dx;
                    pole[tt_number].im_Y = PosMouse.y() + mm_y - dy;
                    pole[tt_number].Y = PosMouse.y() - dy;

            }
                break;
            default:
            {
                pole[tt_number].X = PosMouse.x() - dx;
                pole[tt_number].Y = PosMouse.y() - dy;
            }     
        }
		
        RePaint(tt_number);       
        emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
    }
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    flag = 0;
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
     if (tt_number < 0) return;

     switch (event->key())
     {

     case Qt::Key_Left:
        {
            if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Left)
            {
                switch (pole[tt_number].type)
                {
                    case BUT:           //Кнопка ТУ
                        {
                            pole[tt_number].W--;
                            break;
                        }
                    case RECTM:         //Двойное псевдо
                        {
                            pole[tt_number].im_W--;
                        }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }

            if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Left)
            {
                switch (pole[tt_number].type)
                {
                    case BUT:          //Кнопка ТУ
                        {
                            pole[tt_number].im_W--;
                            break;
                        }
                    case LAMP:      //Лампа
                    case RECT:      //Прямоугольник с текстом ТС
                    case PUSH:      //Кнопка без фиксации
                    case PUSHF:     //Кнопка c фиксации
                    case RECTM:     //Двойное псевдо
                    case RECT1:     //Прямоугольник без текста ТС
                    case RECT4:     //Прямоугольник с 4 состояниями
                    case HIDE_T:    //Закрывать надпись
                    case SIGNAL_M:  //Индикация изменений
                    case NEXT:      //Следующая станция
                    case PREV:      //Предыдущая станция
                    case UP_W:      //Предыдущее окно
                    case DOWN_W:    //Следующее окно
                    case STATION:   //Показать станцию
                    case SHOW_L:    //Показать верхний уровень
                    case STATION_P: //Показать программу экстренного снятия
                    case ZAZEM:     //Заземление
                    case LINE1:     //Ручной автомат вертикальный
                    case LINE2:     //Ручной автомат горизонтальный
                    case LINE3:     //Рубильник вертикальный
                    case LINE4:     //Рубильник горизонтальный
                        {
                            pole[tt_number].W--;
                        }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }

            if (event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Left)
            {
                switch (pole[tt_number].type)
                {
                    case BUT:           //Кнопка ТУ


                        {
                            pole[tt_number].X--;
                            break;
                        }
                    case RECT:          //Прямоугольник с текстом ТС
                    case PUSH:          //Кнопка без фиксации
                    case PUSHF:         //Кнопка с фиксацией
                    case RECTM:         //Двойное псевдо
                    case SIGNAL_M:      //Индикация изменений
                        {
                            pole[tt_number].im_X--;
                            break;
                        }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }         
            else
            {
                switch (pole[tt_number].type)
                {
                    case BUT:          //Кнопка ТУ
                    case RECT:         //Прямоугольник с текстом ТС
                    case RECTM:        //Двойное псевдо
                    case PUSH:         //Кнопка без фиксации
                    case PUSHF:        //Кнопка с фиксацией
                    case SIGNAL_M:     //Индикация изменений
                    {
                        pole[tt_number].im_X--;
                        pole[tt_number].X--;
                        break;
                    }
                    default:
                    {
                        pole[tt_number].X--;
                    }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }
        }



     case Qt::Key_Right:
     {
        if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Right)
        {
            switch (pole[tt_number].type)
            {
                case BUT:          //Кнопка ТУ
                    {
                        pole[tt_number].W++;
                        break;
                    }
                case RECTM:         //Двойное псевдо
                    {
                        pole[tt_number].im_W++;
                    }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Right)
        {
            switch (pole[tt_number].type)
            {
            case BUT:          //Кнопка ТУ
                {
                    pole[tt_number].im_W++;
                    break;
                }
            case LAMP:      //Лампа
            case RECT:      //Прямоугольник с текстом ТС
            case PUSH:      //Кнопка без фиксации
            case PUSHF:     //Кнопка c фиксации
            case RECTM:     //Двойное псевдо
            case RECT1:     //Прямоугольник без текста ТС
            case RECT4:     //Прямоугольник с 4 состояниями
            case HIDE_T:    //Закрывать надпись
            case SIGNAL_M:  //Индикация изменений
            case NEXT:      //Следующая станция
            case PREV:      //Предыдущая станция
            case UP_W:      //Предыдущее окно
            case DOWN_W:    //Следующее окно
            case STATION:   //Показать станцию
            case SHOW_L:    //Показать верхний уровень
            case STATION_P: //Показать программу экстренного снятия
            case ZAZEM:     //Заземление
            case LINE1:     //Ручной автомат вертикальный
            case LINE2:     //Ручной автомат горизонтальный
            case LINE3:     //Рубильник вертикальный
            case LINE4:     //Рубильник горизонтальный
                {
                    pole[tt_number].W++;
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        if (event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Right)
        {
            switch (pole[tt_number].type)
            {
                {
                    case BUT:           //Кнопка ТУ


                        {
                            pole[tt_number].X++;
                            break;
                        }
                    case RECT:          //Прямоугольник с текстом ТС
                    case PUSH:          //Кнопка без фиксации
                    case PUSHF:         //Кнопка с фиксацией
                    case RECTM:         //Двойное псевдо
                    case SIGNAL_M:      //Индикация изменений
                        {
                            pole[tt_number].im_X++;
                            break;
                        }
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        else
        {
            switch (pole[tt_number].type)
            {
                case BUT:          //Кнопка ТУ
                case RECT:         //Прямоугольник с текстом ТС
                case RECTM:        //Двойное псевдо
                case PUSH:         //Кнопка без фиксации
                case PUSHF:        //Кнопка с фиксацией
                case SIGNAL_M:     //Индикация изменений
                {
                    pole[tt_number].im_X++;
                    pole[tt_number].X++;
                    break;
                }
                default:
                {
                    pole[tt_number].X++;
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }
    }


     case Qt::Key_Down:
     {
        if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Down)
        {
            switch (pole[tt_number].type)
            {
                case BUT:          //Кнопка ТУ
                {
                        pole[tt_number].H++;
                        break;
                }
                case RECTM:         //Двойное псевдо
                {
                        pole[tt_number].im_H++;
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Down)
        {
            switch (pole[tt_number].type)
            {
            case BUT:          //Кнопка ТУ
                {
                    pole[tt_number].im_H++;
                    break;
                }
            case LAMP:      //Лампа
            case RECT:      //Прямоугольник с текстом ТС
            case PUSH:      //Кнопка без фиксации
            case PUSHF:     //Кнопка c фиксации
            case RECTM:     //Двойное псевдо
            case RECT1:     //Прямоугольник без текста ТС
            case RECT4:     //Прямоугольник с 4 состояниями
            case HIDE_T:    //Закрывать надпись
            case SIGNAL_M:  //Индикация изменений
            case NEXT:      //Следующая станция
            case PREV:      //Предыдущая станция
            case UP_W:      //Предыдущее окно
            case DOWN_W:    //Следующее окно
            case STATION:   //Показать станцию
            case SHOW_L:    //Показать верхний уровень
            case STATION_P: //Показать программу экстренного снятия
            case ZAZEM:     //Заземление
            case LINE1:     //Ручной автомат вертикальный
            case LINE2:     //Ручной автомат горизонтальный
            case LINE3:     //Рубильник вертикальный
            case LINE4:     //Рубильник горизонтальный
                {
                    pole[tt_number].H++;
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        if (event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Down)
        {
            switch (pole[tt_number].type)
            {
                {
                    case BUT:           //Кнопка ТУ


                        {
                            pole[tt_number].Y++;
                            break;
                        }
                    case RECT:          //Прямоугольник с текстом ТС
                    case PUSH:          //Кнопка без фиксации
                    case PUSHF:         //Кнопка с фиксацией
                    case RECTM:         //Двойное псевдо
                    case SIGNAL_M:      //Индикация изменений
                        {
                            pole[tt_number].im_Y++;
                            break;
                        }
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }

        else
        {
            switch (pole[tt_number].type)
            {
                case BUT:          //Кнопка ТУ
                case RECT:         //Прямоугольник с текстом ТС
                case RECTM:        //Двойное псевдо
                case PUSH:         //Кнопка без фиксации
                case PUSHF:        //Кнопка с фиксацией
                case SIGNAL_M:     //Индикация изменений
                {
                    pole[tt_number].im_Y++;
                    pole[tt_number].Y++;
                    break;
                }
                default:
                {
                    pole[tt_number].Y++;
                }
            }
            emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
            RePaint(tt_number);
            break;
        }
    }

        case Qt::Key_Up:
        {
            if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Up)
            {
                switch (pole[tt_number].type)
                {
                    case BUT:          //Кнопка ТУ
                    {
                        pole[tt_number].H--;
                        break;
                    }
                    case RECTM:         //Двойное псевдо
                    {
                        pole[tt_number].im_H--;
                    }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }

            if (event->modifiers() == Qt::ShiftModifier && event->key() == Qt::Key_Up)
            {
                switch (pole[tt_number].type)
                {
                case BUT:          //Кнопка ТУ
                    {
                        pole[tt_number].im_H--;
                        break;
                    }
                case LAMP:      //Лампа
                case RECT:      //Прямоугольник с текстом ТС
                case PUSH:      //Кнопка без фиксации
                case PUSHF:     //Кнопка c фиксации
                case RECTM:     //Двойное псевдо
                case RECT1:     //Прямоугольник без текста ТС
                case RECT4:     //Прямоугольник с 4 состояниями
                case HIDE_T:    //Закрывать надпись
                case SIGNAL_M:  //Индикация изменений
                case NEXT:      //Следующая станция
                case PREV:      //Предыдущая станция
                case UP_W:      //Предыдущее окно
                case DOWN_W:    //Следующее окно
                case STATION:   //Показать станцию
                case SHOW_L:    //Показать верхний уровень
                case STATION_P: //Показать программу экстренного снятия
                case ZAZEM:     //Заземление
                case LINE1:     //Ручной автомат вертикальный
                case LINE2:     //Ручной автомат горизонтальный
                case LINE3:     //Рубильник вертикальный
                case LINE4:     //Рубильник горизонтальный
                    {
                        pole[tt_number].H--;
                    }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }

            if (event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Up)
            {
                switch (pole[tt_number].type)
                {
                    {
                        case BUT:           //Кнопка ТУ
                            {
                                pole[tt_number].Y--;
                                break;
                            }
                        case RECT:          //Прямоугольник с текстом ТС
                        case PUSH:          //Кнопка без фиксации
                        case PUSHF:         //Кнопка с фиксацией
                        case RECTM:         //Двойное псевдо
                        case SIGNAL_M:      //Индикация изменений
                            {
                                pole[tt_number].im_Y--;
                                break;
                            }
                    }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }

            else
            {
                switch (pole[tt_number].type)
                {
                    case BUT:          //Кнопка ТУ
                    case RECT:         //Прямоугольник с текстом ТС
                    case RECTM:        //Двойное псевдо
                    case PUSH:         //Кнопка без фиксации
                    case PUSHF:        //Кнопка с фиксацией
                    case SIGNAL_M:     //Индикация изменений
                    {
                        pole[tt_number].im_Y--;
                        pole[tt_number].Y--;
                        break;
                    }
                    default:
                    {
                        pole[tt_number].Y--;
                    }
                }
                emit SignalOutPole(pole[tt_number].X, pole[tt_number].Y, pole[tt_number].W, pole[tt_number].H, pole[tt_number].im_X, pole[tt_number].im_Y, pole[tt_number].im_W, pole[tt_number].im_H, pole[tt_number].font, pole[tt_number].color_on, pole[tt_number].color_off);
                RePaint(tt_number);
                break;
            }
        }
     }
}


void MyScene::RePaint(int& i)
{
    switch (pole[i].type)
    {
        case BUT:
            {
                removeItem(pole[i].b);
                removeItem(pole[i].b0);
                drawButton(i);

            }
            break;
        case LAMP:
            {
                removeItem(pole[i].b1);
                drawCircle(i);
            }
            break;
        case TXT:
        case TXTU:
            {
                removeItem(pole[i].b); //???
                removeItem(pole[i].b2);
                drawText(i);
            }
            break;
        case OUT:
        case OUT_TEM_74:
            {
                removeItem(pole[i].b);//!
                removeItem(pole[i].b2);
                drawOut(i);
            }
            break;
        case RECT:      //Прямоугольник с текстом ТС
        case PUSH:      //Кнопка без фиксации
        case PUSHF:     //Кнопка c фиксации
        case SIGNAL_M:  //Индикация изменений
            {
                removeItem(pole[i].b);
                removeItem(pole[i].b2);
                drawRectangle(i);
            }
            break;
        case RECTM:     //Двойное псевдо
            {
                removeItem(pole[i].b);
                removeItem(pole[i].b0);
                drawRectangle(i);
            }
            break;
        case RECT1:     //Прямоугольник без текста ТС
        case RECT4:     //Прямоугольник с 4 состояниями
        case HIDE_T:    //Закрывать надпись
            {
                removeItem(pole[i].b);
                drawRectangle(i);
            }
            break;
        case NEXT:
        case PREV:
        case UP_W:
        case DOWN_W:
        case STATION:
        case SHOW_L:
        case STATION_P:
        case ZAZEM:
        case LINE1:
        case LINE2:
        case LINE3:
        case LINE4:
            {
                removeItem(pole[i].b);
                drawPole(i);
            }
            break;
    }
}

void MyScene::Paint()
{
    int i_line;

    clear();
    if (name_mn == "")
        setBackgroundBrush(Qt::lightGray);
    else setBackgroundBrush(QPixmap(name_mn));

    if (flag_setka == 1)
    {
        for (i_line = 100; i_line<684; i_line+=100)
        {
            this->addLine(0, i_line, 1008, i_line, QColor(Qt::darkGray));
        }

        for (i_line = 100; i_line<1008; i_line+=100)
        {
            this->addLine(i_line, 0, i_line, 684, QColor(Qt::darkGray));
        }
    }

    if (n_pole != 0)
    {
        for (int i = 1; i<=n_pole; i++)
        {
            switch (pole[i].type)
            {
                case BUT:
                    drawButton(i);
                    break;
                case LAMP:
                    drawCircle(i);
                    break;
                case TXT:
                case TXTU:
                    drawText(i);
                    break;
                case OUT:
                case OUT_TEM_74:
                    drawOut(i);
                    break;
                case RECT:      //Прямоугольник с текстом ТС
                case PUSH:      //Кнопка без фиксации
                case PUSHF:     //Кнопка c фиксации
                case RECTM:     //Двойное псевдо
                case RECT1:     //Прямоугольник без текста ТС
                case RECT4:     //Прямоугольник с 4 состояниями
                case HIDE_T:    //Закрывать надпись
                case SIGNAL_M:  //Индикация изменений
                    drawRectangle(i);
                    break;
                case NEXT:
                case PREV:
                case UP_W:
                case DOWN_W:
                case STATION:
                case SHOW_L:
                case STATION_P:
                case ZAZEM:
                case LINE1:
                case LINE2:
                case LINE3:
                case LINE4:
                    drawPole(i);
                    break;
            }
        }
    }

}

void MyScene::Slotact_paint()
{
    if (name_mn !=0)
        Paint();
}

void MyScene::drawButton(const int &i)
{
    pole[i].b0 = new QGraphicsRectItem(0, this);
    pole[i].b0->setBrush(QBrush(Qt::transparent));
    pole[i].b0->setRect(QRectF(pole[i].X, pole[i].Y, pole[i].W-1, pole[i].H-1));
    pole[i].b0->setData(0, i);

    pole[i].b = new QGraphicsRectItem(0, this);
    pole[i].b->setBrush(QColor(pole[i].color_on));

    if (i == tt_number)
    {
        pole[i].b->setPen(QColor(Qt::magenta));
    }
    else pole[i].b->setPen(QColor(Qt::black));

    pole[i].b->setRect(QRectF(pole[i].im_X, pole[i].im_Y, pole[i].im_W-1, pole[i].im_H-1));
    pole[i].b->setData(0, i);
}

void MyScene::drawCircle(const int &i)
{ 
    pole[i].b1 = new QGraphicsEllipseItem(0, this);
    pole[i].b1->setBrush(QColor(pole[i].color_on));

    if (i == tt_number)
    {
        pole[i].b1->setPen(QColor(Qt::magenta));
    }
    else pole[i].b1->setPen(QColor(Qt::black));

    pole[i].b1->setRect(QRectF(pole[i].X-pole[i].W/2, pole[i].Y-pole[i].H/2, pole[i].W, pole[i].H));
    pole[i].b1->setData(0, i);
}

void MyScene::drawText(const int &i)
{
    pole[i].b2 = new QGraphicsTextItem(0, this);
    pole[i].b2->setFont(QFont ("Luxi Sans", pole[i].font, QFont::Bold));
    pole[i].b2->setPlainText(pole[i].slang);
    pole[i].b2->setDefaultTextColor(pole[i].color_on);
    pole[i].b2->moveBy(pole[i].X, pole[i].Y);
    pole[i].b2->setData(0, i);
    pole[i].b2->setZValue(2);

    pole[i].b = new QGraphicsRectItem(0, this);

    if (pole[i].type_object == 5 && pole[i].subtype_object == 6)
    {
        if (i == tt_number)
        {
            pole[i].b->setPen(QColor(Qt::magenta));
        }
        else pole[i].b->setPen(QColor(Qt::black));

        pole[i].b->setBrush(QBrush(Qt::darkGray));
        pole[i].b->setRect(pole[i].X-3, pole[i].Y-3, pole[i].b2->boundingRect().width()+6, pole[i].b2->boundingRect().height()+6);
        pole[i].b->setData(0, i);
    }
    else
    {
        if (i == tt_number)
        {
            pole[i].b->setPen(QColor(Qt::magenta));
            pole[i].b->setBrush(QBrush(Qt::transparent));
            pole[i].b->setRect(pole[i].X+3, pole[i].Y+3, pole[i].b2->boundingRect().width()-3, pole[i].b2->boundingRect().height()-3);
            pole[i].b->show();
        }
        else
        {
            pole[i].b->setPen(QPen(Qt::transparent));
            pole[i].b->setBrush(QBrush(Qt::transparent));
            pole[i].b->setData(0, i);
            pole[i].b->hide();
        }


    }
    pole[i].b->setZValue(1);
}

void MyScene::drawOut(const int &i)
{
    pole[i].b2 = new QGraphicsTextItem(0, this);
    pole[i].b2->setFont(QFont ("Luxi Sans", pole[i].font, QFont::Bold)); //Luxi Sans "Times New Roman"

    if (pole[i].subtype_object == 0)
        pole[i].b2->setPlainText("000");
    else
        pole[i].b2->setPlainText("0.00");

    pole[i].b2->setDefaultTextColor(Qt::black);
    pole[i].b2->moveBy(pole[i].X, pole[i].Y);
    pole[i].b2->setData(0, i);
    pole[i].b2->setZValue(2);

    pole[i].b = new QGraphicsRectItem(0, this);
    pole[i].b->setBrush(QBrush(Qt::white));

    if (i == tt_number)
    {
        pole[i].b->setPen(QColor(Qt::magenta));
    }
    else pole[i].b->setPen(QColor(Qt::black));

    pole[i].b->setRect(pole[i].X-3, pole[i].Y-3, pole[i].b2->boundingRect().width()+6, pole[i].b2->boundingRect().height());
    pole[i].b->setData(0, i);
    pole[i].b->setZValue(1);
}

void MyScene::drawRectangle(const int &i)
{

    pole[i].b = new QGraphicsRectItem(0, this);
    pole[i].b->setBrush(QColor::QColor(pole[i].color_on));

    if (i == tt_number)
    {
        pole[i].b->setPen(QColor(Qt::magenta));
    }
    else pole[i].b->setPen(QColor(Qt::black));

    pole[i].b->setRect(pole[i].X, pole[i].Y, pole[i].W-1, pole[i].H-1);
    pole[i].b->setData(0, i);
    pole[i].b->setZValue(1);

    if (pole[i].type == RECTM) //Двойное псевдо!
    {
        pole[i].b0 = new QGraphicsRectItem(0, this);
        pole[i].b0->setBrush(QColor::QColor(pole[i].color_off));

        if (i == tt_number)
        {
            pole[i].b0->setPen(QColor(Qt::magenta));
        }
        else pole[i].b0->setPen(QColor(Qt::black));

        pole[i].b0->setRect(pole[i].im_X, pole[i].im_Y, pole[i].im_W-1, pole[i].im_H-1);
        pole[i].b0->setData(0, i);
    }

    if ((pole[i].type == RECT) || (pole[i].type == PUSH) || (pole[i].type == PUSHF) || (pole[i].type == SIGNAL_M))
    {
        pole[i].b2 = new QGraphicsTextItem(0, this);

        pole[i].b2->setFont(QFont ("Luxi Sans", pole[i].font, QFont::Bold));
        pole[i].b2->setPlainText(pole[i].slang);
        pole[i].b2->moveBy(pole[i].im_X, pole[i].im_Y);
        pole[i].b2->setData(0, i);
        pole[i].b2->setZValue(2);
    }
}

void MyScene::drawPole(const int &i)
{
    pole[i].b = new QGraphicsRectItem(0, this);
    pole[i].b->setBrush(QBrush(Qt::transparent));

    if (i == tt_number)
    {
        pole[i].b->setPen(QColor(Qt::magenta));
    }
    else pole[i].b->setPen(QColor(Qt::black));

    pole[i].b->setRect(pole[i].X, pole[i].Y, pole[i].W, pole[i].H);
    pole[i].b->setData(0, i);
}

void MyScene::Slot_KillAllPole()
{
    if (n_pole<1)
    {
        QMessageBox msgBox3;
        msgBox3.setText("Удалять нечего!");
        msgBox3.exec();
    }

    else
    {
        while (n_pole>0)
        {
            emit SignalCurNum(pole[n_pole].n_curObj); //Отправление номера выделенного объекта в класс Xpars для отображения в строке состояния
            emit SignalDelNumPole(pole[n_pole].n_curObj); //Функция передачи номера объекта в класс Xpars для уничтожения поля.
            pole.remove(n_pole);
            n_pole--;
        }

        tt_number = -1;

        Paint();
    }
}

void MyScene::Slot_ShowSetka()
{
    if (flag_setka == 0) flag_setka = 1;
    else flag_setka = 0;

    Paint();
}
