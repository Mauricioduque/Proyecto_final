/*
 Proyecto: Rabbit's Adventures

 Creado por: Laura Isabel Vidal - Mauricio Duque

 Informática II
 Facultad de Ingeniería
 Departamento de Electrónica y Telecomunicaciones
 Universidad de Antioquia

 Clase conejo: personaje principal, que posee movimientos de caminar a la derecha,
 izquierda , estar quieto, saltar y caer ,cada uno asociado a un  estado.

 */


#include "ppconejo.h"
#include <iostream>
#include <QDebug>

// se carga la imagen asociada, a si es un jugador o multijugador
PPConejo::PPConejo(bool jugador, QGraphicsItem *parent) : QGraphicsItem(parent),m_StandingDirection(), mState(Standing){

    jugador_=jugador;
    setFlag(ItemClipsToShape);
    if(jugador_){
        mWalkPixmap = QPixmap(":/conejo.png");
        mStandingPixmap = QPixmap(":/conejo.png");
        mJumpPixmap = QPixmap(":/conejo.png");
        standShootPixmap = QPixmap(":/conejo.png");
        mPixmap = mWalkPixmap;
    }
    else{
        mWalkPixmap = QPixmap(":/personaje2.png");
        mStandingPixmap = QPixmap(":/personaje2.png");
        mJumpPixmap = QPixmap(":/personaje2.png");
        standShootPixmap = QPixmap(":/personaje2.png");
        mPixmap = mWalkPixmap;
    }
}

PPConejo::~PPConejo(){

}

//Para cuando el conejo está quieto
void PPConejo::stand(){

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

//Para cuando el conejo está saltando
void PPConejo::jump(){
    mState = Jumping;
}

//Para cuando el conejo está caminando
void PPConejo::walk(){

    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;

}

//Para cuando el conejo está cayendo
void PPConejo::fall(){

    mState = Falling;
}

bool PPConejo::isFalling(){

    return mState == Falling;
}

//retorna la direccion de conejo
int PPConejo::direction() const{

    return m_direction;
}

int PPConejo::standingDirection() const{

    return m_StandingDirection;
}

//Cambia el sprite del conejo
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

//Define la amrgen del objeto
QRectF PPConejo::boundingRect() const{

    return QRectF(0,0,63,73);
}

//Se dibuja el objeto en la escena a partir del sprite
void PPConejo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,63, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

// se cambia la direccín del conejo
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

//Verifica cuando el conejo está tocando con los pies un objeto
bool PPConejo::isTouchingFoot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

//Verifica cuando el conejo está tocando con la cabeza un objeto
bool PPConejo::isTouchingHead(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

//Verifica cuando el conejo está tocando alguna de las plataformas
bool PPConejo::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}
