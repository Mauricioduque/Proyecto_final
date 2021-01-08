#ifndef FONDO_H
#define FONDO_H


#include <QGraphicsPixmapItem>

class Fondo: public QGraphicsPixmapItem
{
public:
    explicit Fondo(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};
#endif // FONDO_H
