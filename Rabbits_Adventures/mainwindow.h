#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>
#include <QSpacerItem>
#include <QSpinBox>
#include <QSplashScreen>
#include <QStatusBar>
#include <QStyle>
#include "inicio.h"
#include "about.h"
#include "view.h"
#include "instructions.h"

class Inicio;
class View;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
    void setSize();
    void createScene();


public slots:
    void showAbout();
    void showinstruction();

private:
    void createActions();
    void createMenus();

    enum { maxState = 10 };
    Inicio *title;
    View *view;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QMenu *helpMenu;
    QMenu *instruction;

    QAction *aboutAction;
    QAction *InstructionAction;
    about *aboutt;
    instructions *Instruction;

};
#endif // MAINWINDOW_H
