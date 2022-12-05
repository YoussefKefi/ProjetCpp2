#include "connection.h"

connection::connection()
{

}
bool connection::CreateConnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("ProjetA2_2");
    db.setUserName("Random1");
    db.setPassword("Random1");
    if (db.open())
        test=true;
    return  test;
}
void connection::FermerConnexion()
{
    db.close();
}
bool connection::OuvrirConnexion()
{
    if (db.open())
        return true ;
    else
        return false;
}
