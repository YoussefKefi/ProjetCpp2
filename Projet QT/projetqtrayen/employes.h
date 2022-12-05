#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QChart>
#include <QtCharts>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>

class Employes
{
public:
    Employes();
    Employes(int,QString,QString,QString,int,QString,QString);
       int getCin_employe();
       int getnum_telephone();
       QString getnom();
       QString getprenom();
       QString getadresse();
       QString getgestion();
       QString getgender();
       void setCin_employe(int);
       void setnum_telephone(int);
       void setnom(QString);
       void setprenom(QString);
       void setadresse(QString);
       void setgestion(QString);
       void setgender(QString);
       bool ajouter();
       QSqlQueryModel* afficher();
       bool supprimer(int);
       bool rech(int);
       QSqlQueryModel* rechercher(QString);
       bool rechnom(QString);
        QSqlQueryModel* recherchernom(QString);
        bool rechprenom(QString);
       QSqlQueryModel* rechercherprenom(QString);
       bool absences(int);
        QSqlQueryModel* absencess(QString);
        QSqlQueryModel *Trier_em(QString croissance,QString critere);
        QChartView *stat_gender();




private:
    int Cin_employe,num_telephone;
    QString nom, prenom,adresse,gestion,gender;
};

#endif // EMPLOYES_H
