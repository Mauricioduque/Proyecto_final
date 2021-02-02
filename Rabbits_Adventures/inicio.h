#ifndef INICIO_H
#define INICIO_H


#include <QPushButton>
#include <QLineEdit>
#include <string>
#include "mainwindow.h"
#include "primermundo.h"
#include "view.h"
#include "login.h"
#include "about.h"
#include "instructions.h"
using namespace std;

class View;
class PrimerMundo;

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
     void showAbout();
     void showinstruction();

private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    bool usuario=false;
    string database;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    Login *loginWindow;

    QScrollBar *scroll;
    PrimerMundo *scene;
    QPushButton *multijugador;
    QPushButton *Unjugador;
    QPushButton *newUserButton;
    QPushButton *aboutButton;
    QPushButton *instructionsButton;
    QLineEdit *labelusuario;
    QLineEdit *labelcontrasena;
    QLabel *userName;
    QLabel *password;
    QGraphicsView *view;
    about *aboutt;
    instructions *Instruction;
};
#endif // INICIO_H
