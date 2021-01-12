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
    Roca(int incio, int fin,QGraphicsItem *parent= nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
   // void move();
private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;
};


#endif // ROCA_H


