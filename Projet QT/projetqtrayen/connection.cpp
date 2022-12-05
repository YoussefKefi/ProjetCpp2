#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");//projet
db.setUserName("mohamed_rayen");//inserer nom de l'utilisateur mohamed_rayen
db.setPassword("mohamed_rayen");//inserer mot de passe de cet utilisateur mohamed_rayen

if (db.open())
test=true;





    return  test;
}
