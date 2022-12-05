#include "voyageur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QChartView>
#include <QtCharts>
voyageur::voyageur()
{
id=0; nom=" "; prenom=" ";
}


voyageur::voyageur(int id,QString nom,QString prenom)
{this->id=id;
 this->nom=nom;
 this->prenom=prenom;
}

int voyageur::getid(){return id;}
QString voyageur::getnom(){return nom;}
QString voyageur::getprenom(){return prenom;}


void voyageur::setid(int id){this->id=id;}
void voyageur::setnom(QString nom){this->nom=nom;}
void voyageur::setprenom(QString prenom){this->prenom=prenom;}


bool voyageur::ajouter()
{
   QString id_string= QString::number(id);
   QSqlQuery query;
        query.prepare("INSERT INTO ETUDIANT (ID, NOM, PRENOM) "
                      "VALUES (:id, :forename, :surname)");
        query.bindValue(":id", id_string);
        query.bindValue(":forename", nom);
        query.bindValue(":surname", prenom);
        return query.exec();
}
bool voyageur::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
         query.prepare("Delete from ETUDIANT where ID=:id");
         query.bindValue(":id", res);
         return query.exec();


}
QSqlQueryModel* voyageur::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM ETUDIANT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));

    return model;
}
bool voyageur::modifier()
{
QSqlQuery query;
QString identifiant_string=QString::number(id);
query.prepare("UPDATE Etudiant SET ID='"+identifiant_string+"',nom='"+nom+"',prenom='"+prenom+"'");
query.bindValue(0,id);
query.bindValue( 1,nom);
query.bindValue( 2,prenom);
return query.exec();
}

bool voyageur::rechidentifiant(QString x){
    QSqlQuery query;
    query.prepare("select * from ETUDIANT where id= :id;");
    query.bindValue(":type", x);
    return query.exec();
}
QSqlQueryModel* voyageur::rechercheridentifiant(QString a)
    {//rechercher fi table

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Etudiant where id ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
            return model;
}

bool voyageur::rechprenom(QString x){
    QSqlQuery query;
    query.prepare("select * from ETUDIANT where prenom = :prenom;");
    query.bindValue(":libelle", x);
    return query.exec();}

QSqlQueryModel* voyageur::rechercherprenom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Etudiant where prenom='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));


            return model;
    }
bool voyageur::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select * from ETUDIANT where nom= :nom;");
    query.bindValue(":nom", x);
    return query.exec();
}
QSqlQueryModel* voyageur::recherchernom(QString a)
    {//rechercher fi table

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from ETUDIANT where nom ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));

            return model;
    }
QSqlQueryModel *voyageur::trie_voy(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();
//on a 3 critere ref type libelle ainsi deux croissance as des
    //selon le critere  qui va etre chercher dans le tableau ainsi la croissance on va avoir une trie ass ou des
    if(critere == "id" && croissance == "ASC")
        modal->setQuery("select * from ETUDIANT order by id ASC ");
    else if(critere == "id" && croissance == "DESC")
        modal->setQuery("select * from ETUDIANT order by id DESC ");

    else if(critere == "nom" && croissance == "ASC")
        modal->setQuery("select * from  order by  ETUDIANT ASC ");//trie du libelle ass et des
    else if(critere == "nom" && croissance == "DESC")
        modal->setQuery("select * from ETUDIANT order by nom DESC ");

    else if(critere == "prenom" && croissance == "ASC")
        modal->setQuery("select * from  ETUDIANT order by prenom ASC ");
    else if(critere == "type" && croissance == "DESC")
        modal->setQuery("select * from  ETUDIANT equi order by prenom DESC ");

    return  modal;
}

QChartView *voyageur::stat_id()
{
        int id1=0;
              int id2=0;


              QSqlQuery query;
              query.prepare("select * from ETUDIANT where ((id>=0)and(id<=999))");
              query.exec();

              while(query.next())
                  id1++;

              query.prepare("select * from ETUDUANT where ((id>=999)and(id<=9999999))");
              query.exec();

              while(query.next())
                  id2++;



              qDebug() << id1<< id2  ;

              QPieSeries *series = new QPieSeries();
                  series->append("0-999 caractere", id1);
                  series->append("999-9999999 caractere", id2);
                  QPieSlice *slice = series->slices().at(0);
                  slice->setExploded(true);
                  slice->setColor("#FFFF00");
                  QPieSlice *slice2 = series->slices().at(1);
                  slice2->setColor("#4360f0");



                  QChart *chart = new QChart();
                  chart->addSeries(series);
                  chart->setTitle("Statistique des id");

                  series->setLabelsVisible();

                  QChartView *chartView = new QChartView(chart);
                  chartView->setRenderHint(QPainter::Antialiasing);
        chartView->chart()->setAnimationOptions(QChart::AllAnimations);
         chartView->chart()->legend()->hide();
                          return chartView;

}

int voyageur::login(QString email, QString mdp)
{
     int row_count = 0;
    QSqlQuery query;
    query.prepare("SELECT * FROM CADMIN where NOM= ? and MOTDEPASSE= ? ");
    query.addBindValue(email);
    query.addBindValue(mdp);
 query.exec();
 while(query.next())
 {
     row_count++;
 }
qDebug() << "Number of Rows: " << row_count;
return row_count;
}
