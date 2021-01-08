#ifndef MUROSNOTA_H
#define MUROSNOTA_H


#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class MurosNota : public QGraphicsItem
{
public:
    enum{ Type = UserType + 11};
    MurosNota(int _longitud, QGraphicsItem *parent = nullptr);
    ~MurosNota();

    void nextSprite();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    QPixmap sprite;
    int posSprite;
    int longitud;
};
#endif // MUROSNOTA_H
