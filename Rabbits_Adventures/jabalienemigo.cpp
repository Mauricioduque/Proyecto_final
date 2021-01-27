#include "jabalienemigo.h"
#include "ppconejo.h"

JabaliEnemigo::JabaliEnemigo(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    direccion = -1;
    inicioPos=inicio;
    finPos=fin;
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
    if(this->pos().x() < inicioPos|| this->pos().x() >= finPos) {
        direccion = -direccion;
        setTransform(QTransform(direccion, 0, 0, 1, 0, 0));
    }
    setPos(this->pos().x() + (direccion*7), this->pos().y());
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(PPConejo)){

            emit estadoJuego(2);
            return;
        }
    }
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
