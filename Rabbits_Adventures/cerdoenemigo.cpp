#include "cerdoenemigo.h"

CerdoEnemigo::CerdoEnemigo(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/cerdo.png");
}

int CerdoEnemigo::getDireccion()
{
    return direccion;
}

void CerdoEnemigo::setDireccion(int inDireccion)
{
    if(direccion != inDireccion)
    {
        direccion = inDireccion;
        if(direccion != 0)
        {
            QTransform transforma;
            if(direccion == -1)
            {
                transforma.scale(-1,1);
            }
            setTransform(transforma);
        }
    }
}

void CerdoEnemigo::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 54;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 514)
    {
        posSprite = 0;
    }
}


QRectF CerdoEnemigo::boundingRect() const {

    return QRectF(0,0,53,150);
}

void CerdoEnemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,53, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int CerdoEnemigo::type() const
{
    return Type;
}
