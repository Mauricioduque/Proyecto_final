#include "lechuga.h"

Lechuga::Lechuga(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/lechuga.png");
    posSprite=0;
}

Lechuga::~Lechuga()
{

}


QRectF Lechuga::boundingRect() const
{
    return QRectF(0,0,39,41);
}

void Lechuga::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Lechuga::type() const
{
    return Type;
}
