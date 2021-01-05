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

#include "cerdoenemigo.h"
#include "fondo.h"
#include "jabalienemigo.h"
#include "lechuga.h"
#include "muros.h"
#include "murosnota.h"
#include "zanahoria.h"
#include "ppconejo.h"


class PrimerMundo :public QGraphicsScene
{

    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit PrimerMundo(QObject *parent = nullptr);
    ~PrimerMundo();
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);
    void iniciarEscenaUno();

private:
    void agregarEntradaHorizontal(int entrada);
    void checkTimer();


private slots:
    void correrEscena();
    void jumpPersonaje();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void moverPersonaje();
    void actualizar();
    void nextSprite();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void finalizarNivelUno();
    void jumpFactorChanged(qreal);
    void repetirNivel();

private:
    int anchoEscena;

    PPConejo *personaje;

    bool salto;


    Fondo *background;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int velocidad;

    QTimer *timer;
    QTimer *timerEscena;
    QTimer *timerSprite;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight;

    QGraphicsItem *mandoImagen;

    //complementos de la escena
    QList <Lechuga *> lechuga;
    QList <Zanahoria *> zanahoria;
    QList <MurosNota*> ladrillosNota;
    QList <Muros*> muros;
    QList <JabaliEnemigo *> jabali;
    QList <CerdoEnemigo*> cerdo;
};

#endif // PRIMERMUNDO_H
