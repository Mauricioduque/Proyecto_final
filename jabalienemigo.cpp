#include "jabalienemigo.h"

JabaliEnemigo::JabaliEnemigo(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/jabalí.png");
}

int JabaliEnemigo::getDireccion()
{
    return direccion;
}

void JabaliEnemigo::setDireccion(int inDireccion)
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

void JabaliEnemigo::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 149;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 1188)
    {
        posSprite = 0;
    }
}


QRectF JabaliEnemigo::boundingRect() const {

    return QRectF(0,0,149,130);
}

void JabaliEnemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,149, 130);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int JabaliEnemigo::type() const
{
    return Type;
}
