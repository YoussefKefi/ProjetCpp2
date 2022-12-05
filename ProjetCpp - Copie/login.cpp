#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

/*#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "cadmin.h"
#include <QMessageBox>
#include <QStateMachine>
#include <QDialog>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QEasingCurve curve,curve1;
    animation = new QPropertyAnimation(ui->identifi,"geometry");
    animationimg = new QPropertyAnimation(ui->widget,"geometry");
    animation->setDuration(1000);
    animationimg->setDuration(1000);
    animation->setStartValue(ui->identifi->geometry());
    animationimg->setStartValue(ui->widget->geometry());
    animation->setEndValue(QRect(300,310,131,31));
    animationimg->setEndValue(QRect(20,110,711,351));
    curve.setType(QEasingCurve::OutBounce);
    curve.setType(QEasingCurve::OutBounce);
    animation->setEasingCurve(curve);
    animationimg->setEasingCurve(curve1);
    animation->setLoopCount(3);
    animationimg->setLoopCount(1);
    animation->start();
    animationimg->start();
}

login::~login()
{
    delete ui;
}





void login::on_identifi_clicked()
{
    cadmin ca(ui->lineEditnomnutilisateur->text(),ui->lineEdit_motdepasse->text());
       /* QString nomuitlisateur=ui->lineEditnomnutilisateur->text();
        QString motdepasse=ui->lineEdit_motdepasse->text();*/

/*        {


            QMessageBox::information(this,"identifier","nom d'utilisateur et mot de passe sont correct");
            //hide();
            gc  = new MainWindow(this);
            gc->show();

        }
        else if (ca.authentification()<1)
        {

            QMessageBox::information(this,"identifier","nom d'utilisateur et mot de passe ne sont pas correct");
        }
}
*/
