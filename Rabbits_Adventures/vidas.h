#ifndef VIDAS_H
#define VIDAS_H

#include <QGraphicsTextItem>
#include <QFont>
#include<QFontDatabase>


class vidas: public QGraphicsTextItem{
public:
    vidas(int vid,QGraphicsItem * parent=0);
    void decrementar();
    int getPuntaje();


private:
    int vida;
};
#endif // VIDAS_H
