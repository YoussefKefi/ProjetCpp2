#include "transport.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QFile>

transport::transport()
{
    MATRICULE=0;
    MOYEN=" ";
    NBR_VOYAGEURS=0;
    DATE_S;
}
transport::transport(int MATRICULE,QString MOYEN, int NBR_VOYAGEURS, QDate DATE_S)
{
    this->MATRICULE=MATRICULE;
    this->MOYEN=MOYEN;
    this->NBR_VOYAGEURS=NBR_VOYAGEURS;
    this->DATE_S=DATE_S;
}
/**************************************/
int transport::getmatricule()
{
    return MATRICULE;
}
QString transport::getmoyen()
{
    return MOYEN;
}
int transport::getnbrvoyageurs()
{
    return NBR_VOYAGEURS;
}
QDate transport::getdate()
{
    return DATE_S;
}
/**************************************/
void transport::setmatricule(int MATRICULE)
{
    this->MATRICULE=MATRICULE;
}
void transport::setmoyen(QString MOYEN)
{
    this->MOYEN=MOYEN;
}
void transport::setnbrvoyageurs(int NBR_VOYAGEURS)
{
    this->NBR_VOYAGEURS=NBR_VOYAGEURS;
}
void transport::setdate(QDate DATE_S)
{
    this->DATE_S=DATE_S;
}
/**************************************/
bool transport::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(MATRICULE);
         query.prepare("INSERT INTO TRANSPORT(MATRICULE,MOYEN,NBR_VOYAGEURS,DATE_S)" "VALUES (:MATRICULE,:MOYEN,:NBR_VOYAGEURS,:DATE_S)");
         query.bindValue(":MATRICULE", MATRICULE);
         query.bindValue(":MOYEN", MOYEN);
         query.bindValue(":NBR_VOYAGEURS", NBR_VOYAGEURS);
         query.bindValue(":DATE_S", DATE_S);
    return query.exec();
}
bool transport::supprimer(int MATRICULE)
{
    QSqlQuery query;
         query.prepare("DELETE FROM TRANSPORT where MATRICULE= :MATRICULE");
         query.bindValue(0, MATRICULE);
    return query.exec();
}
bool transport::modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE TRANSPORT SET MOYEN=:MOYEN, NBR_VOYAGEURS=:NBR_VOYAGEURS, DATE_S=:DATE_S WHERE MATRICULE=:MATRICULE ");
        query.bindValue(":MATRICULE", MATRICULE);
        query.bindValue(":MOYEN", MOYEN);
        query.bindValue(":NBR_VOYAGEURS", NBR_VOYAGEURS);
        query.bindValue(":DATE_S", DATE_S);
    return query.exec();
}
/**************************************/
QSqlQueryModel* transport::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM TRANSPORT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("MOYEN"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR_VOYAGEURS"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_S"));
    return  model;
}
QSqlQueryModel* transport ::afficher_matricule()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT MATRICULE from TRANSPORT");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULE"));
    return model;
}
/**************************************/

QSqlQueryModel * transport::tri_matricule()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from TRANSPORT order by MATRICULE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("MOYEN"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR_VOYAGEURS"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_S"));
    return model;
}
QSqlQueryModel * transport::tri_moyen()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from TRANSPORT order by MOYEN");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("MOYEN"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESCRIPTION"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_S"));
    return model;
}
QSqlQueryModel * transport::tri_nbrvoyageur()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from TRANSPORT order by NBR_VOYAGEURS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MOYEN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR_VOYAGEURS"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_S"));
    return model;
}
/**************************************/
void transport::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void transport::chercheMat(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from TRANSPORT where regexp_like(MATRICULE,:MATRICULE);");
   query->bindValue(":MATRICULE",x);
   if(x==0)
   {
       query->prepare("select * from TRANSPORT;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void transport::chercheVoyageurs(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from TRANSPORT where regexp_like(NBR_VOYAGEURS,:NBR_VOYAGEURS);");
    query->bindValue(":NBR_VOYAGEURS",x);
    if(x==0)
    {
        query->prepare("select * from TRANSPORT;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}

