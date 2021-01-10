#include "zanahoria.h"


Zanahoria::Zanahoria(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/zanahoria.png");
    posSprite=0;
}

Zanahoria::~Zanahoria()
{

}



QRectF Zanahoria::boundingRect() const
{
    return QRectF(0,0,45,60);
}

void Zanahoria::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Zanahoria::type() const
{
    return Type;
}
