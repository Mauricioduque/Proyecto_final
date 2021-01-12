#ifndef AGUILA_H
#define AGUILA_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class Aguila:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 4};
    Aguila(int incio, int fin,QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
public slots:
    void nextSprite();

private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;
};

#endif // AGUILA_H
