#include "pina.h"

Pina::Pina(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/piña.png");
    posSprite=0;
}

Pina::~Pina()
{

}


QRectF Pina::boundingRect() const
{
    return QRectF(0,0,39,41);
}

void Pina ::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Pina::type() const
{
    return Type;
}

