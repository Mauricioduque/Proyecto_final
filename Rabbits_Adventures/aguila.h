#ifndef AGUILA_H
#define AGUILA_H


#include "roca.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsView>
#include <iostream>
#include <QObject>


class Aguila:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    int posx,posy;
    enum{ Type = UserType + 4};
    Aguila(int incio, int fin,QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    int cont=0;
    bool f=false;

signals:
    void estadoJuego(int);



public slots:
    void nextSprite();
    void tirar_roca();




private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;

    Roca *roca;


};


#endif // AGUILA_H
