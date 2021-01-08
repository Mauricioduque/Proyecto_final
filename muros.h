#ifndef MUROS_H
#define MUROS_H

#include <QGraphicsItem>
#include <QPixmap>

class Muros : public QGraphicsItem
{
public:
    Muros(QGraphicsItem *parent = 0);
    void nextSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int posSprite=0;
    QPixmap sprite;
};
#endif // MUROS_H
