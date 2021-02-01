/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase puntaje: muestra en pantalla el puntaje que lleva el personaje y lo incrementa en
 tiempo de ejecución

 */

#include "puntaje.h"

puntaje::puntaje(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    contador=0;

    // dibujar el texto
    int id = QFontDatabase::addApplicationFont(":/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(contador));
    setDefaultTextColor(Qt::white);
    setFont(QFont("CoinCount2",40));
}

void puntaje::incrementar(){
    contador++;
    setPlainText(QString("") + QString::number(contador * 10));

}

int puntaje::getPuntaje(){
    return contador;
}
