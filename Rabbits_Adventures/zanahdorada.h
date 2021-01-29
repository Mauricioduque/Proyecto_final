#ifndef ZANAHDORADA_H
#define ZANAHDORADA_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class ZanahDorada:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 12};
    ZanahDorada(QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void colision();
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

#endif // ZANAHDORADA_H
