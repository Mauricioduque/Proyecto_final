#include "muros.h"

#include <QPainter>

Muros::Muros(int longitud,QGraphicsItem *parent): QGraphicsItem(parent)

{
    tamano=longitud;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/conveyorR.png");

}

void Muros::nextSprite(){

    posSprite += 125;
    if (posSprite >= 1000 ) {
        posSprite = 0;

    }
}

QRectF Muros::boundingRect() const {
    return QRectF(0,0,125*tamano,56);

}

void Muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    for(int i = 0; i < 125*tamano; i++)
    {
        painter->drawPixmap(i*125,0, sprite, posSprite, 0,125, 56);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Muros::type() const
{
    return Type;
}
