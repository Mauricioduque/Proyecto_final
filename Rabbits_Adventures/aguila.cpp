/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Aguila: enemigo final  del primer mundo, encargado de lanzar piedras
 en caida libre a medida que vuela (cambiando su sprite, asociado a un timer)

 */

#include "aguila.h"
#include "roca.h"

//Costructor donde se carga la imagen y se inicia el timer asociado
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

}

//Variación del sprite que esta asociada al timer(SLOT)
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
    if((posx<=6300)||((posx>=6700) && (posx<=7150))||((posx>=7400) && (posx<=7800))){
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

        if(roca->colis==true){
            emit estadoJuego(1);
            roca->colis=false;
        }
    }
}

//Se agrega la roca a la escena
void Aguila::tirar_roca()
{

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

//Margen del objeto
QRectF Aguila::boundingRect() const {

    return QRectF(0,0,122,150);
}

//Se dibuja el objeto en la escena a partir del sprite
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
