#ifndef ETUDIANT_H
#define ETUDIANT_H
#include <QString>
#include <QSqlQueryModel>

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
     bool modifier(int);
private:
    int id;
    QString nom, prenom;

};

#endif // ETUDIANT_H
