#ifndef PPCONEJO_H
#define PPCONEJO_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTransform>

class PPConejo : public QGraphicsItem
{
public:
     PPConejo(bool jugador,QGraphicsItem *parent = 0);
     ~PPConejo();
    int direction() const;
    int standingDirection() const;
    void addStandingDirection(int standingDirection);
    void addDirection(int direction);
    void nextFrame();
    void set_m_direction(int mdirection);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    void stand();
    void jump();
    void standShoot();
    void walk();
    void fall();
    bool isFalling();

private:
    enum State {
         Standing = 0,
         StandShoot,
         Walking,
         Jumping,
         Falling
    };

    int m_direction=0;
    int mCurrentFrame=0;
    int m_StandingDirection;
    bool jugador_;
    State mState;
    QPixmap mPixmap;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;

};

#endif // PPCONEJO_H
