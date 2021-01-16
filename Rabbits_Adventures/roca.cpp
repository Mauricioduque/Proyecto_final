#include "roca.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "aguila.h"
#include "primermundo.h"
#include "ppconejo.h"


Roca::Roca(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    //dibuja la bala


    sprite=QPixmap(":/roca.png");
  //  setScale(0.25);

   // connect
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(move()));
    timer2->start(int(1000*T));
   // timer2->start(50);

}
QRectF Roca::boundingRect() const
{
    return QRectF(0,0,35,35);
}

void Roca::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,35, 35);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Roca::type() const
{
    return Type;
}

void Roca::move()
{
   // posy=y();
    posx=x();
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

    posy=H-(0.5*g*T*T);
    setPos(posx,y()+posy);
  //  setPos(x()-30,y()+150);
    if(pos().y()>600){
        scene()->removeItem(this);
        delete this;
    }
}
//void Roca::move()
//{

//    if(this->pos().x() < inicioPos|| this->pos().x() > finPos) {
//        direccion = -direccion;
//        setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));

//    }
//    setPos(this->pos().x() + (direccion*7), this->pos().y()+150);
//        if(pos().y()>600){
//            scene()->removeItem(this);
//            delete this;
//        }


//}

