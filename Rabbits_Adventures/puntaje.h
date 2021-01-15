#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QFont>
#include<QFontDatabase>

#include <QGraphicsTextItem>

class puntaje: public QGraphicsTextItem{
public:
    puntaje(QGraphicsItem * parent=0);
    void incrementar();
    int getPuntaje();


private:
    int contador;
};
#endif // PUNTAJE_H
