#include "aguila.h"
#include "roca.h"

Aguila::Aguila(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/agu2.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(100);

//    QTimer *timer3=new QTimer(this);
//    connect(timer,SIGNAL(timeout()),this,SLOT(tirar_roca()));
//    timer3->start(10000);

}

void Aguila::nextSprite()
{

    //Manejo de Sprites
    //Distancia en caada sprite
    posx=x();
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
    //crea la roca
    if((posx<=6300)||((posx>=6700) && (posx<=7000))||((posx>=7600) && (posx<=7900))){
        if(f==false){
            f=true;
            tirar_roca();
            roca->var=1;

        }
        else if (roca->var==0){
            scene()->removeItem(roca);
            tirar_roca();
            roca->var=1;
        }

    }

}


void Aguila::tirar_roca(){
//Agregamos roca


      if(direccion==-1){
         roca= new Roca(pos().x()+ (direccion*7)+200);
         roca->setPos(this->pos().x()+ (direccion*7)+200,150);
         roca->direccion=direccion;
      }
      else{
          roca= new Roca(pos().x()+ (direccion*7));
          roca->setPos(this->pos().x()+ (direccion*7),150);
      }

      scene()->addItem(roca);

}
QRectF Aguila::boundingRect() const {

    return QRectF(0,0,122,150);
}

void Aguila::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,122, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Aguila::type() const
{
    return Type;
}
