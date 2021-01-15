#include "ppconejo.h"
#include <iostream>
#include <QDebug>

PPConejo::PPConejo(QGraphicsItem *parent) : QGraphicsItem(parent),m_StandingDirection(), mState(Standing){

    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":/conejo.png");
    mStandingPixmap = QPixmap(":/conejo.png");
    mJumpPixmap = QPixmap(":/conejo.png");
    standShootPixmap = QPixmap(":/conejo.png");
    mPixmap = mWalkPixmap;
}

PPConejo::~PPConejo(){

}

void PPConejo::stand(){

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void PPConejo::jump(){
    mState = Jumping;
}


void PPConejo::walk(){

    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;

}

void PPConejo::fall(){

    mState = Falling;
}

bool PPConejo::isFalling(){

    return mState == Falling;
}

int PPConejo::direction() const{

    return m_direction;
}

int PPConejo::standingDirection() const{

    return m_StandingDirection;
}

void PPConejo::nextFrame(){

    mCurrentFrame += 63;

    if (mCurrentFrame >= 503 ) {
        mCurrentFrame = 0;
    }
}

void PPConejo::set_m_direction(int mdirection)
{
    m_direction=mdirection;
}

QRectF PPConejo::boundingRect() const{

    return QRectF(0,0,63,73);
}

void PPConejo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,63, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void PPConejo::addDirection(int direction){

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction){
        if (-1 == m_direction) setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else setTransform(QTransform());
    }
}

void PPConejo::addStandingDirection(int standingDirection){

    m_StandingDirection = standingDirection;
}

bool PPConejo::isTouchingFoot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool PPConejo::isTouchingHead(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool PPConejo::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}
