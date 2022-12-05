#include "employe.h"

Employe::Employe()
{
CIN_employe=0;num_telephone=0;nom=" ";prenom=" ";adresse=" ";
}
Employe::Employe(int CIN_employe,int num_telephone,QString nom,QString prenom,QString adresse)
{this->CIN_employe=CIN_employe; this->num_telephone=num_telephone; this->nom=nom;this->prenom=prenom;this->adresse=adresse;}
int Employe::getCIN_employe(){return CIN_employe;}
int Employe::getnum_telephone(){return num_telephone;}
QString Employe::getnom(){return nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getadresse(){return adresse;}
void Employe::setCIN_employe(int CIN_employe){this->CIN_employe=CIN_employe;}
void Employe::setnum_telephone(int num_telephone){this->num_telephone=num_telephone;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
