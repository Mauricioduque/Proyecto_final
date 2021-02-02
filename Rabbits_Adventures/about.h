
#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QSpacerItem>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

public slots:
    void on_ok_clicked();

private:
    Ui::about *ui;

};



#endif // ABOUT_H


