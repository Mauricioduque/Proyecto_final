#ifndef CERDOENEMIGO_H
#define CERDOENEMIGO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class CerdoEnemigo:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 8};
    CerdoEnemigo(QGraphicsItem *parent= nullptr);

    int getDireccion();
    void setDireccion(int inDireccion);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    void nextSprite();

private:
    QPixmap sprite;
    int posSprite;
    int direccion;
};

#endif // CERDOENEMIGO_H
