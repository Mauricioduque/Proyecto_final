#include "muros.h"

#include <QPainter>

Muros::Muros(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":images/conveyorR.png");

}

void Muros::nextSprite(){

    posSprite += 193;
    if (posSprite >= 1544 ) {
        posSprite = 0;

    }
}

QRectF Muros::boundingRect() const {
    return QRectF(0,0,190,56);

}

void Muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, sprite, posSprite, 0,190, 56);
    setTransformOriginPoint(boundingRect().center());
}
