#include "murosnota.h"

MurosNota::MurosNota(int _longitud, QGraphicsItem *parent) : QGraphicsItem(parent)
  , longitud(_longitud)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/tierra.png");
    posSprite = 0;
}

MurosNota::~MurosNota()
{

}

void MurosNota::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 65;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 518)
    {
        posSprite = 0;
    }
}

QRectF MurosNota::boundingRect() const
{
    return QRectF(0,0,63*longitud,63);
}

void MurosNota::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 63*longitud; i++)
    {
        painter->drawPixmap(i*63,0, sprite, posSprite, 0,63, 63);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int MurosNota::type() const
{
    return Type;
}
