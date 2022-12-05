#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "transport.h"
#include <QPdfWriter>
#include <QPainter>
#include <QIntValidator>
#include <QSettings>
#include <QDesktopServices>
#include "dialog_statistiques.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineMatricule->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineVoyageurs->setValidator(new QIntValidator(0, 9999, this));
    ui->tableView->setModel(T.afficher());
    ui->comboBox_2->setModel(T.afficher_matricule());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushAjouter_2_clicked()
{
    int MATRICULE=ui->lineMatricule->text().toInt();
    QString MOYEN;
    int NBR_VOYAGEURS=ui->lineVoyageurs->text().toInt();
    QDate DATE_S=ui->dateEdit->date();
    if (ui->radBus_2->isChecked())
        MOYEN="Bus";
    if (ui->radAvion_2->isChecked())
        MOYEN="Avion";
    if (ui->radTrain_2->isChecked())
        MOYEN="Train";
    transport T(MATRICULE,MOYEN,NBR_VOYAGEURS,DATE_S);
    bool test=T.ajouter();
    if(test)
    {
        ui->comboBox_2->setModel(T.afficher_matricule());
        ui->tableView->setModel(T.afficher());
    }
}

void MainWindow::on_pushModifier_2_clicked()
{
    int MATRICULE=ui->lineMatricule->text().toInt();
    QString MOYEN;
    int NBR_VOYAGEURS=ui->lineVoyageurs->text().toInt();
    QDate DATE_S=ui->dateEdit->date();
    if (ui->radBus_2->isChecked())
        MOYEN="Bus";
    if (ui->radAvion_2->isChecked())
        MOYEN="Avion";
    if (ui->radTrain_2->isChecked())
        MOYEN="Train";
    transport T(MATRICULE,MOYEN,NBR_VOYAGEURS,DATE_S);
    bool test=T.modifier();
    if(test)
    {
        ui->comboBox_2->setModel(T.afficher_matricule());
        ui->tableView->setModel(T.afficher());
    }
}

void MainWindow::on_pushSupprimer_4_clicked()
{
    transport T;
    T.setmatricule(ui->comboBox_2->currentText().toInt());
    bool test=T.supprimer(T.getmatricule());
    if(test)
    {
        ui->tableView->setModel(T.afficher());
        ui->comboBox_2->setModel(T.afficher_matricule());
    }
}

void MainWindow::on_pushTriMoyen_clicked()
{
    ui->tableView->setModel(T.tri_moyen());
}

void MainWindow::on_psuhTriVoyageurs_clicked()
{
    ui->tableView->setModel(T.tri_nbrvoyageur());
}

void MainWindow::on_pushTriMatricule_clicked()
{
    ui->tableView->setModel(T.tri_matricule());
}

void MainWindow::on_comboBox_2_currentIndexChanged(int)
{
    int matricule=ui->comboBox_2->currentText().toInt();
    QString matricule_1=QString::number(matricule);
    QSqlQuery query1,query2,query3,query4;
    query1.prepare("SELECT * FROM TRANSPORT where MATRICULE='"+matricule_1+"'");
    query2.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Bus' ");
    query3.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Avion' ");
    query4.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Train' ");
    if(query1.exec())
    {
        while (query1.next())
        {
            ui->lineMatricule->setText(query1.value(0).toString());
            if(query2.exec()){ while (query2.next()) { ui->radBus_2->setChecked(1);; }}
            if(query3.exec()){ while (query3.next()) { ui->radAvion_2->setChecked(1);; }}
            if(query4.exec()){ while (query4.next()) { ui->radTrain_2->setChecked(1);; }}
            ui->lineVoyageurs->setText(query1.value(2).toString());
            ui->dateEdit->setDate(query1.value(3).toDate());
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_lineRecherche_2_textChanged(const QString &arg1)
{
    transport T;
    QString text;

    if (ui->radMatricule->isChecked()==true)
    {
        T.clearTable(ui->tableView);
        T.chercheMat(ui->tableView,arg1);
    }
    if (ui->radVoyageur->isChecked()==true)
    {
        T.clearTable(ui->tableView);
        T.chercheVoyageurs(ui->tableView,arg1);
    }
}

void MainWindow::on_psuhBusStation_clicked()
{
    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/search/airport/@36.8204992,10.1370472,11.75z");
}

void MainWindow::on_pushAirport_clicked()
{
    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/search/bus+station/@36.8211534,10.1370467,11z/data=!3m1!4b1");
}

void MainWindow::on_pushTrainStation_clicked()
{
    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/search/train+station/@36.820768,10.1370471,11z/data=!3m1!4b1");
}

void MainWindow::on_pushPDF_clicked()
{
    QPdfWriter pdf("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Logo.png"));
    painter.drawText(3000,1500,"LISTE DES TRANSPORTS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Matricule");
    painter.drawText(2300,3300,"Moyen");
    painter.drawText(4300,3300,"N° Voyageurs");
    painter.drawText(6300,3300,"Date Sortie");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from TRANSPORT");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("D:/Studies/2A/Projet Desktop Application/Taches Projet Qt/GestionDesSponsors/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_pushStat_clicked()
{
    s = new Dialog_Statistiques();
    s->setWindowTitle("Statistiques");
    s->choix_pie();
    s->show();
}
