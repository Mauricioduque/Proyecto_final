#ifndef PINA_H
#define PINA_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>


class Pina : public QGraphicsItem
{

public:
    enum { Type = UserType + 5 };
    Pina(QGraphicsItem *parent = 0);
    ~Pina();
    void nextSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int posSprite;
    QPixmap sprite;

};
#endif // PINA_H
