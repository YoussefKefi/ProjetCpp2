#ifndef LOGEMENT_H
#define LOGEMENT_H
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

class Logement
{
public:
    Logement();
    Logement(int,QString,QString);
    int getid();
    QString getnom();
    QString getadresse();
    void setid(int);
    void setnom(QString);
    void setadresse(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int);
    bool rech(int);
    QSqlQueryModel* rechercher(QString);
    bool rechnom(QString);
    QSqlQueryModel* recherchernom(QString);
    bool rechadresse(QString);
    QSqlQueryModel* rechercheradresse(QString);
    bool modifier();
    QSqlQueryModel *trie_log(QString croissance,QString critere);

private:
    int id;
    QString nom, adresse;

};

#endif // LOGEMENT_H
