#ifndef MUROS_H
#define MUROS_H

#include <QGraphicsItem>
#include <QPixmap>

class Muros : public QGraphicsItem
{
public:
    enum{ Type = UserType + 13};
    Muros(int longitud,QGraphicsItem *parent = 0);
    void nextSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int tamano;
    int posSprite=0;
    QPixmap sprite;
};
#endif // MUROS_H
