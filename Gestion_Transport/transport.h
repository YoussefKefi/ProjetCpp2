#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QTableView>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>

class transport
{
public:
    transport();
    transport(int,QString,int,QDate);
    int getmatricule();
    QString getmoyen();
    int getnbrvoyageurs();
    QDate getdate();

    void setmatricule(int);
    void setmoyen(QString);
    void setnbrvoyageurs(int);
    void setdate(QDate);


    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_matricule();
    QSqlQueryModel* tri_matricule();
    QSqlQueryModel* tri_nbrvoyageur();
    QSqlQueryModel* tri_moyen();

    void clearTable(QTableView * table);
    void chercheMat(QTableView *table, QString x);
    void chercheVoyageurs(QTableView *table, QString x);

private:
    int MATRICULE;
    QString MOYEN;
    int NBR_VOYAGEURS;
    QDate DATE_S;
};

#endif // TRANSPORT_H
