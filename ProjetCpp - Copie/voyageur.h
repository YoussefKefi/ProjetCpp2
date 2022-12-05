#ifndef VOYAGEUR_H
#define VOYAGEUR_H
#include <QString>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>
#include <QtCharts>
class voyageur
{
public:
    voyageur();
    voyageur(int,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int);
    bool modifier();
      QSqlQueryModel*rechercheridentifiant(QString a);
        bool rechidentifiant(QString x);
       QSqlQueryModel*recherchernom(QString a);
       bool rechnom(QString x);
       QSqlQueryModel*rechercherprenom(QString a);
       bool rechprenom(QString x);
       QSqlQueryModel *trie_voy(QString croissance,QString critere);
       QChartView *stat_id();
int login(QString email, QString mdp);


private:
    int id;
    QString nom, prenom;



};

#endif // VOYAGEUR_H







