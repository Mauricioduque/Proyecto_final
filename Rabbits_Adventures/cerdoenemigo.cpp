/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Cerdo Enemigo: objeto del primer mundo, que se desplaza en determina seccion
 y se encuentra asociado a un timer, si el conejo colisiona con este puede perder una de sus vidas

 */

#include "cerdoenemigo.h"
#include "ppconejo.h"

// se carga la imagen y se inicia el timer asociado
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

//Variación del sprite que esta asociada al timer(SLOT) y verifica la colisión
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

//Margen de la imagen
QRectF CerdoEnemigo::boundingRect() const {

    return QRectF(0,0,122,150);
}

//Se dibuja el objeto en la escena a partir del sprite
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
