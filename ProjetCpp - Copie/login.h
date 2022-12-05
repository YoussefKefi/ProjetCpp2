#ifndef LOGIN_H
#define LOGIN_H
#include "voyageur.h"
#include <QPropertyAnimation>

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
private slots:


    void on_identifi_clicked();

    void on_lineEditnomnutilisateur_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::login *ui;
    QPropertyAnimation *animation,*animationimg;
    voyageur *e;
};

#endif // LOGIN_H

/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "voyageur.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include "mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:


    void on_identifi_clicked();

    void on_lineEditnomnutilisateur_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation,*animationimg;
    voyageur *e;
    Ui::login *ui;

};
#endif // MAINWINDOW_H*/
