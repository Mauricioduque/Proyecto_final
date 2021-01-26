#include "fuego.h"

#include <math.h>

Fuego::Fuego(float x,float  y,float centrox,float centroy,float vel, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    posx=x;
    posy=y;
    cx=centrox;
    cy=centroy;
    w=vel;


    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/fire.png");
    posSprite=0;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(int(1000*T));
}
void Fuego::move()
{

    //float t=5*T;

//    ECUACIONES DE MOV CIRCULAR UNIFORME:
//    X(n)=(X(n-1)-Cx)*cos(wT)-(Y(n-1)-cy)*sen(wT)+cx
//    Y(n)=(Y(n-1)-Cy)*cos(wT)+(X(n-1)-cx)*sen(wT)+cy
    float aux,auxy;
    aux=posx-cx;
    auxy=posy-cy;
    posx=(aux)*cos(w*T)-(auxy)*sin(w*T)+cx;
    posy=(auxy)*cos(w*T)+(aux)*sin(w*T)+cy;
   // posx=posx+100;

    setPos(int(posx),int(posy));


//    Verificación de colisión del conejo con el fuego
//    QList<QGraphicsItem *> colliding_items = collidingItems();
//    for(int i=0; i < colliding_items.size(); ++i){
//        if(typeid (*(colliding_items[i]))== typeid (PPConejo)){

//            col=true;

//            return;
//        }
//    }

}

QRectF Fuego::boundingRect() const {

    return QRectF(0,0,122,150);
}

void Fuego::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,122, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Fuego::type() const
{
    return Type;
}
