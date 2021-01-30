#ifndef INICIO_H
#define INICIO_H


#include <QPushButton>
#include <QLineEdit>
#include <string>
#include "mainwindow.h"
#include "primermundo.h"
#include "view.h"
#include "login.h"
using namespace std;


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
    string lectura_txt(string name);
    bool checkUser();

signals:
    void sceneChanged();


private slots:
     void multijugadorLogin();
     void unjugadorLogin();
     void newUser();

private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    bool usuario=false;
    string database;
    AnimatedGraphicsItem *background;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;
    Login *loginWindow;

    QPropertyAnimation *animation;
    QScrollBar *scroll;
    PrimerMundo *scene;
    QPushButton *multijugador;
    QPushButton *Unjugador;
    QPushButton *newUserButton;
    QLineEdit *labelusuario;
    QLineEdit *labelcontrasena;
    QLabel *userName;
    QLabel *password;
    QGraphicsView *view;
};
#endif // INICIO_H
