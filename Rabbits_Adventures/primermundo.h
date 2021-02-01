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
#include "muros.h"
#include "murosnota.h"
#include "zanahoria.h"
#include "ppconejo.h"
#include "pina.h"
#include "puntaje.h"
#include "vidas.h"
#include "aguila.h"
#include "roca.h"
#include "flag.h"
#include "gameover.h"
#include "fuego.h"
#include "bullet.h"
#include "zanahdorada.h"
#include "triunfo.h"


class PrimerMundo :public QGraphicsScene
{

    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit PrimerMundo(bool configurar,QScrollBar *s,QObject *parent = nullptr);
    ~PrimerMundo();
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);
    void iniciarEscenaUno();
    void iniciarEscenaDos();
    void reiniciarEscenaUno();
    void reiniciarEscenaDos();
    void Borrarmundo1();


private:
    void checkTimer();


private slots:
    void jumpPersonaje();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void moverPersonaje();
    void fallPersonaje();
    bool manejoColisiones();
    void checkColisionMuros();
    void checkColisionFuegos();
    void checkColZanahoria();
    void checkColPina();
    void Estado(int n);
    QGraphicsItem *collidingPlatforms();


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void jumpFactorChanged(qreal);


private:
    int anchoEscena=6600;
    int direction;
    bool reinicio=false;
    bool quieto=false;
    bool Jugador=true;
    bool configurar_=true;

    PPConejo *personaje;

    Fondo *background=0;
    Fondo *ground;
    Fondo *danger;
    Fondo *LogoPuntaje;
    Fondo *LogoVida;
    Fondo *cazador1;
    Fondo *cazador2;
    Bullet *bala1;
    Bullet *bala2;

    puntaje *Puntaje;
    vidas *vidas_;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int velocidad=7;
    int desplazamientoMundo=0;
    int Vida=0;

    QTimer *timer;
    QTimer *mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight=200;

    Aguila *aguila;
    Aguila *aguila2;
    Aguila *aguila3;
    Roca *roca;
    Flag *flag;
    ZanahDorada *zanahoriaDorada;

    QGraphicsItem *m_platform;
    JabaliEnemigo *jabali1;
    JabaliEnemigo *jabali2;
    JabaliEnemigo *jabali3;
    JabaliEnemigo *jabali4;
    JabaliEnemigo *jabali5;
    JabaliEnemigo *jabali6;
    JabaliEnemigo *jabali7;
    JabaliEnemigo *jabali8;
    CerdoEnemigo *cerdo1;
    CerdoEnemigo *cerdo2;
    CerdoEnemigo *cerdo3;
    CerdoEnemigo *cerdo4;
    CerdoEnemigo *cerdo5;
    CerdoEnemigo *cerdo6;
    CerdoEnemigo *cerdo7;
    Fuego *fuego;
    Fuego *fuego1;
    Fuego *fuego2;
    Fuego *fuego3;
    Fuego *fuego4;

    QScrollBar *scroll;
    GameOver *gameOverWindow;
    Triunfo *ganar;
    QGraphicsView *view;



    //complementos de la escena
    QList <Pina *> pina;
    QList <Zanahoria *> zanahoria;
    QList <MurosNota*> ladrillosNota;
    QList <Muros*> muro;
    QList <JabaliEnemigo *> jabali;
    QList <CerdoEnemigo*> cerdo;
    QList<Zanahoria *> eliminarZanahoria(QList<Zanahoria *>zanahoria,int pos);
    QList<Pina *> eliminarPina(QList<Pina *>pina,int pos);

};

#endif // PRIMERMUNDO_H
