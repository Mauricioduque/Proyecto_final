#ifndef ROCA_H
#define ROCA_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>


class Roca: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 7};
    Roca(float x,QGraphicsItem *parent= nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    // variables y constantes para ecuación de caida libre:
    float posy=150,posx,v=0;
    float H=150; // altura inicial
    float g=28; //aceleración gravitatoria
    float T=0.05;//periodo
    int var=0;
    float Vx=70; //velocidad del aguila
    int direccion=1;
    bool colis=false;

public slots:
    void move();
private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;

    int inicioPos;
    int finPos;
    QTimer *timer2;
};


#endif // ROCA_H
