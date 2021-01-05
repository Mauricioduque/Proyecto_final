#include "zanahoria.h"


Zanahoria::Zanahoria(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap("");
    posSprite=0;
}

Zanahoria::~Zanahoria()
{

}

void Zanahoria::nextSprite()
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

QRectF Zanahoria::boundingRect() const
{
    return QRectF(0,0,39,41);
}

void Zanahoria::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Zanahoria::type() const
{
    return Type;
}
