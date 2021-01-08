#include "fondo.h"

Fondo::Fondo (const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
}

QPainterPath Fondo::shape() const
{
    return QPainterPath();
}
