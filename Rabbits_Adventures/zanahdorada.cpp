#include "zanahdorada.h"
#include "ppconejo.h"

ZanahDorada::ZanahDorada(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/zanahoriad.png");
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(colision()));
    timer3->start(100);
    posSprite=0;
}

void ZanahDorada::colision()
{

      QList<QGraphicsItem *> colliding_items = collidingItems();
     //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(PPConejo)){

             emit estadoJuego(4);
             return;
         }
     }
}

QRectF ZanahDorada::boundingRect() const {

    return QRectF(0,0,100,80);
}

void ZanahDorada::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,100, 80);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int ZanahDorada::type() const
{
    return Type;
}
