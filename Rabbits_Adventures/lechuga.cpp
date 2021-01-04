#include "lechuga.h"

Lechuga::Lechuga(QGraphicsItem *parent): QGraphicsItem(parent)
    , posSprite(0)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap("");
}

Lechuga::~Lechuga()
{

}

void Lechuga::nextSprite()
{
    //Manejo de Sprites
    //Distancia en cada sprite
    posSprite += 38;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 300)
    {
        posSprite = 0;
    }
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
