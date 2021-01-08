#ifndef JABALIENEMIGO_H
#define JABALIENEMIGO_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class JabaliEnemigo:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 9};
    JabaliEnemigo(QGraphicsItem *parent= nullptr);

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


#endif // JABALIENEMIGO_H
