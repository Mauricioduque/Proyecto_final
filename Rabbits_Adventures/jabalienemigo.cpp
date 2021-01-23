#include "jabalienemigo.h"

JabaliEnemigo::JabaliEnemigo(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    direccion = -1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/jabali.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(50);
}


void JabaliEnemigo::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 100;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 800)
    {
        posSprite = 0;
    }
    if(this->pos().x() < 100 || this->pos().x() >= 500) {
        direccion = -direccion;
        setTransform(QTransform(direccion, 0, 0, 1, 0, 0));
    }
    setPos(this->pos().x() + (direccion*7), this->pos().y());
}


QRectF JabaliEnemigo::boundingRect() const {

    return QRectF(0,0,98,100);
}

void JabaliEnemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,100, 100);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int JabaliEnemigo::type() const
{
    return Type;
}
