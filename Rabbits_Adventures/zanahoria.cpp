/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase Zanahoria: alimento del primer mundo, que al colisionar con
 el conejo, incrementa su puntaje.

 */

#include "zanahoria.h"

//en el constructor se carga la imagen
Zanahoria::Zanahoria(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/zanahoria.png");
    posSprite=0;
}

Zanahoria::~Zanahoria()
{

}

// se define la margen del objeto
QRectF Zanahoria::boundingRect() const
{
    return QRectF(0,0,45,60);
}

//Se dibuja el objeto en la escena a partir del sprite
void Zanahoria::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Zanahoria::type() const
{
    return Type;
}
