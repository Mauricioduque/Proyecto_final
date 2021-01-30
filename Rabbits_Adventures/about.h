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

private:
    Ui::about *ui;
    QVBoxLayout * mainVBox;

    QLabel * schoolInfo, * classInfo,*info, * groupMember1,
           * groupMember2, * logoLbl, * spacerLabel;

    QPixmap * logo, * spacerBar;

};



#endif // ABOUT_H
