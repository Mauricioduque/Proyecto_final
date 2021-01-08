#ifndef INICIO_H
#define INICIO_H

#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"
#include "primermundo.h"
#include "view.h"


class View;
class PrimerMundo;
class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class Inicio: public QGraphicsScene{
    Q_OBJECT
public:
    Inicio(View *view, QWidget *parent = 0);

signals:
    void sceneChanged();


private slots:
     void developerLogin();
private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    AnimatedGraphicsItem *background;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;

    QPropertyAnimation *animation;
    QScrollBar *scroll;
    PrimerMundo *scene;
    QPushButton *developerButton;
    QGraphicsView *view;
};
#endif // INICIO_H
