#ifndef BULLET_H
#define BULLET_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QObject>



class Bullet:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 8};
    Bullet(float x,float Velx,float ang,bool f,QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

    // variables y constantes para ecuación de mov circular:
    float  posy=135,posx;
    float  vx,v=0;
    float  w; //velocidad angular de la particula(rad/s);
    float  T=0.05;//periodo
    float H=135,g=10;
    float pi=3.1416;
    bool flag;

    float a,b,c;
    bool d;

public slots:
    void move();

signals:
    void estadoJuego(int);

private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;
};
#endif // BULLET_H
