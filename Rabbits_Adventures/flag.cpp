#include "flag.h"
#include "ppconejo.h"

Flag::Flag(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/flag.png");
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer3->start(100);
}

void Flag::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 85;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 250)
    {
        posSprite = 0;
    }
    //setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));
     setPos(this->pos().x(), this->pos().y());

      QList<QGraphicsItem *> colliding_items = collidingItems();
     //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(PPConejo)){

             emit estadoJuego(0);
             return;
         }
     }
}

QRectF Flag::boundingRect() const {

    return QRectF(0,0,85,81);
}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,85, 81);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Flag::type() const
{
    return Type;
}