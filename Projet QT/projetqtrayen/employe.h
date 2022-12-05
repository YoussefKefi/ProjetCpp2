#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>

class Employe
{
public:
    Employe();
    Employe(int,int,QString,QString,QString);
    int getCIN_employe();
     int getnum_telephone();
     QString getnom();
     QString getprenom();
     QString getadresse();
     void setCIN_employe(int);
     void setnum_telephone(int);
     void setnom(QString);
     void setprenom(QString);
     void setadresse(QString);


private:
    int CIN_employe,num_telephone;
       QString nom, prenom,adresse;
};

#endif // EMPLOYE_H
