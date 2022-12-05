#include "logement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QChartView>
#include <QtCharts>
Logement::Logement()
{
id=0; nom=" "; adresse=" ";
}


Logement::Logement(int id,QString nom,QString adresse)
{this->id=id;
 this->nom=nom;
 this->adresse=adresse;
}

int Logement::getid(){return id;}
QString Logement::getnom(){return nom;}
QString Logement::getadresse(){return adresse;}


void Logement::setid(int id){this->id=id;}
void Logement::setnom(QString nom){this->nom=nom;}
void Logement::setadresse(QString adresse){this->adresse=adresse;}


bool Logement::ajouter()
{
   QString id_string= QString::number(id);
   QSqlQuery query;
        query.prepare("INSERT INTO LOGEMENT (ID, NOM, ADRESSE) "
                      "VALUES (:id, :forename, :surname)");
        query.bindValue(":id", id_string);
        query.bindValue(":forename", nom);
        query.bindValue(":surname", adresse);
        return query.exec();
}
bool Logement::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

         query.prepare("Delete from logement where ID=:id");

         query.bindValue(":id", res);
         return query.exec();


}
bool Logement::rech(int x){
    QSqlQuery query;
    query.prepare("select * from logement where id=:id;");
    query.bindValue(":id", x);
    return query.exec();
}

QSqlQueryModel* Logement::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from logement where id='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));

            return model;
    }

bool Logement::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select * from logement where nom = :nom;");
    query.bindValue(":nom", x);
    return query.exec();}

QSqlQueryModel* Logement::recherchernom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from logement where nom='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));

            return model;
    }
bool Logement::rechadresse(QString x){
    QSqlQuery query;
    query.prepare("select * from logement where adresse = :adresse;");
    query.bindValue(":adresse", x);
    return query.exec();
}
QSqlQueryModel* Logement::rechercheradresse(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from logement where adresse ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));

            return model;
    }

QSqlQueryModel* Logement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM logement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr(".     Identifiant     ."));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr(".     Nom     ."));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr(".     Adresse     ."));

    return model;
}

/*bool Logement::modifier()
{
QSqlQuery query;
QString identifiant_string=QString::number(id);
query.prepare("UPDATE logement SET ID='"+identifiant_string+"',nom='"+nom+"',adresse='"+adresse+"'");
query.bindValue( 0,id);
query.bindValue( 1,nom);
query.bindValue( 2,adresse);
return query.exec();
}*/

QSqlQueryModel *Logement::trie_log(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "id" && croissance == "Ascendant")
        modal->setQuery("select * from logement order by id Ascendant ");
    else if(critere == "id" && croissance == "Descendant")
        modal->setQuery("select * from logement order by id Descendant ");

    else if(critere == "nom" && croissance == "Ascendant")
        modal->setQuery("select * from logement order by nom Ascendant ");
    else if(critere == "nom" && croissance == "Descendant")
        modal->setQuery("select * from logement order by nom Descendant ");

    else if(critere == "adresse" && croissance == "Ascendant")
        modal->setQuery("select * from  logement order by adresse Ascendant ");
    else if(critere == "adresse" && croissance == "Descendant")
        modal->setQuery("select * from  logement  order by adresse Descendant ");

    return  modal;
}

/*QChartView *Logement::stat_type()

  {

      int t1=0;

      int t2=0;

      int t3=0;



      QSqlQuery query;

      query.prepare("select * from logement where ID='id'");

      query.exec();



      while(query.next())

          t1++;



      query.prepare("select * from employe where nom='nom'");

      query.exec();



      while(query.next())

          t2++;



      query.prepare("select * from employe where adresse='adresse'");

      query.exec();



      while(query.next())

          t3++;



      qDebug() << t1<< t2 << t3;



      QPieSeries *series = new QPieSeries();

          series->append("Caissier", t1);

          series->append("Menage", t2);

          series->append("Assistant technique", t3);



          QPieSlice *slice = series->slices().at(0);

          slice->setExploded(true);

          slice->setColor("pink");

          QPieSlice *slice2 = series->slices().at(1);

          slice2->setColor("turquoise");

          QPieSlice *slice3 = series->slices().at(2);

          slice3->setColor("salmon");



          QChart *chart = new QChart();

          chart->addSeries(series);

          chart->setTitle("Statistique du post");



          series->setLabelsVisible();



          QChartView *chartView = new QChartView(chart);

          chartView->setRenderHint(QPainter::Antialiasing);

           chartView->chart()->setAnimationOptions(QChart::AllAnimations);

           chartView->chart()->legend()->hide();

          return chartView;



  }*/
