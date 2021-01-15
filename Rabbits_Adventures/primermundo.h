#ifndef PRIMERMUNDO_H
#define PRIMERMUNDO_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QList>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

#include "cerdoenemigo.h"
#include "fondo.h"
#include "jabalienemigo.h"
#include "lechuga.h"
#include "muros.h"
#include "murosnota.h"
#include "zanahoria.h"
#include "ppconejo.h"
#include "pina.h"
#include "aguila.h"
#include "roca.h"


class PrimerMundo :public QGraphicsScene
{

    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit PrimerMundo(QScrollBar *s,QObject *parent = nullptr);
    ~PrimerMundo();
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);
    void iniciarEscenaUno();
    void correrEscena(QTimerEvent *);

private:
    void checkTimer();


private slots:
    void jumpPersonaje();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void moverPersonaje();
    void fallPersonaje();
    bool manejoColisiones();
    void checkColisionMuros();
    QGraphicsItem *collidingPlatforms();


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void jumpFactorChanged(qreal);


private:
    int anchoEscena=6600;

    PPConejo *personaje;

    Fondo *background=0;
    Fondo *ground;
    Fondo *danger;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int velocidad=7;
    int desplazamientoMundo=0;

    QTimer timer;
    QTimer mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight=200;

    QGraphicsItem *m_platform;
    JabaliEnemigo *jabali1;
    CerdoEnemigo *cerdo1;
    CerdoEnemigo *cerdo2;
    CerdoEnemigo *cerdo3;
    CerdoEnemigo *cerdo4;
    CerdoEnemigo *cerdo5;
    CerdoEnemigo *cerdo6;
    CerdoEnemigo *cerdo7;

    Aguila *aguila;
    Aguila *aguila2;
    Aguila *aguila3;
    Roca *roca;


    QScrollBar *scroll;

    //complementos de la escena
    QList <Lechuga *> lechuga;
    QList <Pina *> pina;
    QList <Zanahoria *> zanahoria;
    QList <MurosNota*> ladrillosNota;
    QList <Muros*> muros;
    QList <JabaliEnemigo *> jabali;
    QList <CerdoEnemigo*> cerdo;
    bool falling;
    bool jumping;
};

#endif // PRIMERMUNDO_H
