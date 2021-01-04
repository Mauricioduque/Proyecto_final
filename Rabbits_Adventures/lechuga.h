#ifndef LECHUGA_H
#define LECHUGA_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>


class Lechuga : public QGraphicsItem
{

public:
    enum { Type = UserType + 4 };
    Lechuga(QGraphicsItem *parent = 0);
    ~Lechuga();
    void nextSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int posSprite;
    QPixmap sprite;

};


#endif // LECHUGA_H
