#ifndef CADMIN_H
#define CADMIN_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class cadmin
{
public:
    cadmin(){nom="";
             mot_de_passe="";};
    cadmin(QString,QString);
   int authentification();
private:
    QString nom;
    QString mot_de_passe;
};

#endif // CADMIN_H
