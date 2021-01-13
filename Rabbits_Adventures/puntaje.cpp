#include "puntaje.h"
#include <QFont>
#include<QFontDatabase>

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
