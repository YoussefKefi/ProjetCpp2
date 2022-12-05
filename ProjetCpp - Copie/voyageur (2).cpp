#include "etudiant.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
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
         query.prepare("Delete from voyageur where ID=:id");
         query.bindValue(":id", res);
         return query.exec();


}
QSqlQueryModel* voyageur::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM voyageur");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));

    return model;
}
bool voyageur::modifier(int selected){

    QSqlQuery query;


    query.prepare(" UPDATE CRUD SET LINE= :line ,REEL= :reel ,COMBO= :combo,TEXT= :text ,V_DATE= :date "
                  ",TIME= :time where V_INT= :integer");
    query.bindValue(":integer", selected);
    query.bindValue(":id",id); //remplir la valeur d'une maniere securisÃ©e
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);

    return    query.exec();

}
