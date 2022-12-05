#include "employes.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QObject>
#include <QIntValidator>
#include<QString>
#include <QFile>
#include <QTextDocument>
#include<QTextStream>
#include<QIODevice>
#include<QDate>
#include <QSystemTrayIcon>
#include <QChart>
#include <QtCharts>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>


Employes::Employes()
{
    Cin_employe=0;num_telephone=0;nom=" ";prenom=" ";adresse=" "; gestion=" ";gender=" ";
}

Employes::Employes(int Cin_employe,QString nom,QString prenom,QString adresse,int num_telephone, QString gestion,QString gender)
{this->Cin_employe=Cin_employe;this->num_telephone=num_telephone; this->nom=nom;this->prenom=prenom;this->adresse=adresse;this->gestion=gestion;this->gender=gender;}
int Employes::getCin_employe(){return Cin_employe;}
int Employes::getnum_telephone(){return num_telephone;}
QString Employes::getnom(){return nom;}
QString Employes::getprenom(){return prenom;}
QString Employes::getadresse(){return adresse;}
QString Employes::getgestion(){return gestion;}
QString Employes::getgender(){return gender;}
void Employes::setCin_employe(int Cin_employe){this->Cin_employe=Cin_employe;}
void Employes::setnum_telephone(int num_telephone){this->num_telephone=num_telephone;}
void Employes::setnom(QString nom){this->nom=nom;}
void Employes::setprenom(QString prenom){this->prenom=prenom;}
void Employes::setgestion(QString gestion){this->gestion=gestion;}
void Employes::setgender(QString gender){this->gender=gender;}
bool Employes::ajouter()
{
    QSqlQuery query;
    QString Cin_employe_string=QString::number(Cin_employe);
              query.prepare("INSERT INTO TABLEAU_EMPLOYE (CIN, Nom, Prenom, Adresse, Telephone, Gestion, Gender) "
                            "VALUES (:CIN, :NOM, :PRENOM, :ADRESSE, :TELEPHONE, :GESTION, :GENDER)");
              query.bindValue(0, Cin_employe_string);
              query.bindValue(1, nom);
              query.bindValue(2, prenom);
              query.bindValue(3, adresse);
              query.bindValue(4, num_telephone);
              query.bindValue(5, gestion);
              query.bindValue(6, gender);

   return query.exec();
}
QSqlQueryModel* Employes::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel;

          model->setQuery("SELECT* FROM TABLEAU_EMPLOYE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal,  QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal,  QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal,  QObject::tr("ADRESSE"));
          model->setHeaderData(4, Qt::Horizontal,  QObject::tr("TELEPHONE"));
          model->setHeaderData(5, Qt::Horizontal,  QObject::tr("GESTION"));
          model->setHeaderData(6, Qt::Horizontal,  QObject::tr("GENDER"));
    return model;
}
bool Employes::supprimer(int Cin_employe)
{

        QSqlQuery query;
          query.prepare("Delete from TABLEAU_EMPLOYE where CIN=:CIN");
           query.bindValue(0, Cin_employe);

             return query.exec();
    }


bool Employes::rech(int x){
    QSqlQuery query;
    query.prepare("select * from TABLEAU_EMPLOYE where CIN=:CIN;");
    query.bindValue(":CIN", x);
    return query.exec();
}

QSqlQueryModel* Employes::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from TAbLEAU_EMPLOYE where CIN='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
            model->setHeaderData(1, Qt::Horizontal,  QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal,  QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal,  QObject::tr("ADRESSE"));
            model->setHeaderData(4, Qt::Horizontal,  QObject::tr("TELEPHONE"));
            model->setHeaderData(5, Qt::Horizontal,  QObject::tr("GESTION"));
            return model;
    }

bool Employes::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select * from TABLEAU_EMPLOYE where NOM = :Nom;");
    query.bindValue(":NOM", x);
    return query.exec();}

QSqlQueryModel* Employes::recherchernom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from TABLEAU_EMPLOYEW where NOM='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
            model->setHeaderData(1, Qt::Horizontal,  QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal,  QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal,  QObject::tr("ADRESSE"));
            model->setHeaderData(4, Qt::Horizontal,  QObject::tr("TELEPHONE"));
            model->setHeaderData(5, Qt::Horizontal,  QObject::tr("GESTION"));
            return model;
    }

bool Employes::rechprenom(QString x){
    QSqlQuery query;
    query.prepare("select * from TABLEAU_EMPLOYE where PRENOM = :Prenom;");
    query.bindValue(":PRENOM", x);
    return query.exec();
}
QSqlQueryModel* Employes::rechercherprenom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from TABLEAU_EMPLOYE where PRENOM ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
            model->setHeaderData(1, Qt::Horizontal,  QObject::tr("NOM"));
            model->setHeaderData(2, Qt::Horizontal,  QObject::tr("PRENOM"));
            model->setHeaderData(3, Qt::Horizontal,  QObject::tr("ADRESSE"));
            model->setHeaderData(4, Qt::Horizontal,  QObject::tr("TELEPHONE"));
            model->setHeaderData(5, Qt::Horizontal,  QObject::tr("GESTION"));
            return model;
    }

QSqlQueryModel *Employes::Trier_em(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "CIN" && croissance == "ASC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by CIN ASC ");
    else if(critere == "CIN" && croissance == "DESC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by CIN DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by NOM DESC ");

    else if(critere == "Prenom" && croissance == "ASC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by PRENOM ASC ");
    else if(critere == "Prenom" && croissance == "DESC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by PRENOM DESC ");

    else if(critere == "Adresse" && croissance == "ASC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by ADRESSE ASC ");
    else if(critere == "Adresse" && croissance == "DESC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by ADRESSE DESC ");

    else if(critere == "Telephone" && croissance == "ASC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by TELEPHONE ASC ");
    else if(critere == "Telephone" && croissance == "DESC")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by TELEPHONE DESC ");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by PRENOM");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by PRENOM");

    else if(critere == "Telephone" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by TELEPHONE");
    else if(critere == "Telephone" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by TELEPHONE");

    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by ADRESSE");
    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by ADRESSE");

    else if(critere == "CIN" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by CIN");
    else if(critere == "CIN" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by CIN");

    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by NOM");
    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by NOM");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by Prenom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by Prenom");

    else if(critere == "Gestion" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by Gestion");
    else if(critere == "Gestion" && croissance == "")
        modal->setQuery("select * from TABLEAU_EMPLOYE order by Gestion");

    return  modal;
}
QChartView *Employes::stat_gender()
  {
      int m=0;
      int f=0;

      QSqlQuery query;
      query.prepare("select * from TABLEAU_EMPLOYE where GENDER='male'");
      query.exec();

      while(query.next())
          m++;

      query.prepare("select * from TABLEAU_EMPLOYE where GENDER='female'");
      query.exec();

      while(query.next())
          f++;


      qDebug() << m<< f ;

      QPieSeries *series = new QPieSeries();
          series->append("male", m);
          series->append("female", f);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#4C6293");
          slice->setLabel("male "+QString("%1%").arg(100*slice->percentage(),1,'f',1));
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#E4F0FF");
          slice2->setLabel("female "+QString("%1%").arg(100*slice2->percentage(),1,'f',1));


          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du GENDER");


          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->chart()->setAnimationOptions(QChart::AllAnimations);
          chartView->chart()->legend()->hide();
          chartView->resize(1000,500);
          return chartView;
}

