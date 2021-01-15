#include "cerdoenemigo.h"
#include "ppconejo.h"

CerdoEnemigo::CerdoEnemigo(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/cerdo.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(100);
}

void CerdoEnemigo::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 129;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 514)
    {
        posSprite = 0;
    }
    if(this->pos().x() < inicioPos|| this->pos().x() > finPos) {
        direccion = -direccion;
        setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (direccion*7), this->pos().y());

    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(PPConejo)){

            emit estadoJuego(1);
            return;
        }
    }
}



QRectF CerdoEnemigo::boundingRect() const {

    return QRectF(0,0,122,150);
}

void CerdoEnemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,122, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int CerdoEnemigo::type() const
{
    return Type;
}
