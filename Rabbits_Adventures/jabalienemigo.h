#ifndef JABALIENEMIGO_H
#define JABALIENEMIGO_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class JabaliEnemigo:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 9};
    JabaliEnemigo(QGraphicsItem *parent= nullptr);

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
};


#endif // JABALIENEMIGO_H
