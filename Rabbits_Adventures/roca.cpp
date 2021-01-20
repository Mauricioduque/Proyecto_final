#include "roca.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "aguila.h"
#include "primermundo.h"
#include "ppconejo.h"


Roca::Roca(float x,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    //dibuja la bala

    posx=x;
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

    float t=5*T;
    //posx=x();
    //Verificación de colisión del conejo con la piedras

  //ECUACIONES DE MOVIMIENTO:caída libre
   //Y(t)=y(t-1)+v(t-1)*T-g/2*T*T
    //V(t)=V(t-1)-g*T
   // posy=H-(0.5*g*T*T);
    posy=posy+v*t+(0.5*g*t*t);
    v=v+g*t;
    posx=posx+Vx*T*direccion;
    setPos(posx,posy);

    if(pos().y()>600){
        var=0;
//        scene()->removeItem(this);
//        delete this;
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0; i < colliding_items.size(); ++i){
        if(typeid (*(colliding_items[i]))== typeid (PPConejo)){
            colis=true;
            return;
        }
    }

}
