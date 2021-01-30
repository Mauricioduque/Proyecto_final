/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase bullet: objeto disparado por el cazador enemigo del segundo mundo, encargado de
 salir disparado en una trayectoria parabólica, por medio del método move() asociado a un timer

 */

#include "bullet.h"
#include "ppconejo.h"
#include <math.h>

//constructor que recibe  Vx y angulo en Y para calcular la velocidad y cargar el sprite
Bullet::Bullet(float x,float Velx, float ang,bool f,QGraphicsItem *parent) : QGraphicsItem(parent)
{
     //recibo
     posx=x;
     vx=Velx;
     w=ang*(pi/180); //grados a rad
     v=vx*tan(w);
     a=x;
     b=Velx;
     c=v;
     if(f)direccion=1;
     else direccion=-1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/bullet (1).png");
    posSprite=0;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(int(1000*T));
}


//SLOT que varia la posición de la bala a partir de las ecuaciones de movimiento parabolico
//y se verifica si hay colision con el conejo
void Bullet::move(){
 // posy=y();

   float t=4*T;
//posx=x();

        //ECUACIONES DE MOVIMIENTO:Parábolico
        //Y(t)=y(t-1)+v(t-1)*T-g/2*T*T
        //V(t)=V(t-1)-g*T

      posy=posy+v*t+(0.5*g*t*t); //tener en cuenta Vy y Vx para el angulo de disp
      v=v+g*t;
      posx=posx+vx*t*direccion;
      setPos(posx,posy);
      if(posy>600){
          posx=a;
          posy=180;
          vx=b;
          v=c;
      }

//if(pos().y()>600){
//    var=0;
//       scene()->removeItem(this);
//        delete this;
//}
 //   Verificación de colisión del conejo con el fuego
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0; i < colliding_items.size(); ++i){
        if(typeid (*(colliding_items[i]))== typeid (PPConejo)){
            emit estadoJuego(3);
            return;
        }
    }

}

//Margen del sprite
QRectF Bullet::boundingRect() const {

    return QRectF(0,0,55,25);
}

//Dibuja el sprite
void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,55, 25);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Bullet::type() const
{
    return Type;
}
