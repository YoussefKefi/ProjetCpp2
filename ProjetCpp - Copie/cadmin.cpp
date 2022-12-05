#include "cadmin.h"

#include <QDebug>

/*cadmin::cadmin()
{

}*/
cadmin::cadmin(QString nom,QString mot_de_passe)
{
this->nom=nom;
this->mot_de_passe=mot_de_passe;
}
int cadmin::authentification()
{int count=0;
    QSqlQuery query;
    //QString test_nom,test_mot_de_passe;
    query.prepare("select * from cadmin where  (nom=:nom) and (motdepasse=:mot_de_passe) ");
    query.bindValue(":nom",nom);
    query.bindValue(":mot_de_passe",mot_de_passe);
    query.exec();
    while(query.next())
    {
        count++;

    }
    return (count);
}

