#ifndef ZANAHORIA_H
#define ZANAHORIA_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>


class Zanahoria : public QGraphicsItem
{

public:
    enum { Type = UserType + 3 };
    Zanahoria(QGraphicsItem *parent = 0);
    ~Zanahoria();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int posSprite;
    QPixmap sprite;

};

#endif // ZANAHORIA_H
