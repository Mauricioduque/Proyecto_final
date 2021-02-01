/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase pina: alimento del segundo mundo, que al colisionar con
 el conejo, incrementa su puntaje.

 */

#include "pina.h"

//se carga la imagen
Pina::Pina(QGraphicsItem *parent): QGraphicsItem(parent)
{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/piña.png");
    posSprite=0;
}

//Se genera la margen del objeto
QRectF Pina::boundingRect() const
{
    return QRectF(0,0,39,41);
}

//Se dibuja el objeto en la escena a partir del sprite
void Pina ::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Pina::type() const
{
    return Type;
}

