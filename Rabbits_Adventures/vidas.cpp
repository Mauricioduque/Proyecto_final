/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase vidas: muestra en pantalla las vidas asocidas al personaje y las decrementa
 en tiempo de ejecución

 */

#include "vidas.h"


vidas::vidas(int vid,QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    vida=vid;
    // dibujar el texto
    int id = QFontDatabase::addApplicationFont(":/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);

    setPlainText(QString("") + QString::number(vida));
    setDefaultTextColor(Qt::white);
    setFont(QFont("CoinCount2",40));

}

void vidas::decrementar(){
    vida--;
    setPlainText(QString("") + QString::number(vida));

}

int vidas::getPuntaje(){
    return vida;
}

