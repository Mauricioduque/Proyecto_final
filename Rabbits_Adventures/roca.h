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
    Roca(QGraphicsItem *parent= nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    // variables y constantes para ecuación de caida libre:
    float posy,posx,v;
    float H=150; // altura inicial
    float g=10; //aceleración gravitatoria
    float T=0.05;//tiempo


public slots:
    void move();
private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;
    QTimer *timer2;
};


#endif // ROCA_H


