#include "roca.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "aguila.h"
#include "primermundo.h"
#include "ppconejo.h"


Roca::Roca(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    //dibuja la bala
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    sprite=QPixmap(":/roca.png");
  //  setScale(0.25);

    //connect
//    QTimer * timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

//    timer->start(100);

}
QRectF Roca::boundingRect() const
{
    return QRectF(0,0,39,41);
}

void Roca::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Roca::type() const
{
    return Type;
}

//void Roca::move()
//{
//    QList<QGraphicsItem *> colliding_items = collidingItems();
//    for(int i=0; i < colliding_items.size(); ++i){
//        if(typeid (*(colliding_items[i]))== typeid (PPConejo)){
//            //incrementa el puntaje
//           // juego->score->increase();
//            scene()->removeItem(colliding_items[i]);
//            scene()->removeItem(this);
//            delete colliding_items[i];
//            delete this;
//        }
//    }



//    setPos(x(),y()+10);
//    if(pos().y() + 50 < 0){
//        scene()->removeItem(this);
//        delete this;
//    }
//}
