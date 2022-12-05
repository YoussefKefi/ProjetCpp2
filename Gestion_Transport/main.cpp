#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connection c;
    bool test=c.CreateConnexion();
    if(test)
    {
        c.CreateConnexion();
        QMessageBox::information(nullptr, QObject::tr("Database Is Open"),
                                 QObject::tr("Connected Successfully !\n"
                                             "Click Ok to exit."), QMessageBox::Ok);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Database Is Not Open"),
                              QObject::tr("Connection Failed.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);
    w.show();
    return a.exec();
}
