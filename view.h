#ifndef VIEW_H
#define VIEW_H


#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QPushButton>
class View : public QGraphicsView{
    Q_OBJECT
signals:
    void sceneChanged();

public:
    View();
    void sceneSet(QGraphicsScene *);
    QPushButton *submit;
    QLabel *uLabel;
};

#endif // VIEW_H
