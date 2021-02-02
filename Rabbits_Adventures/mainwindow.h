#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
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
#include "view.h"


class Inicio;
class View;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow();
    void setSize();
    void createScene();
    Inicio *title;
    View *view;


};
#endif // MAINWINDOW_H
