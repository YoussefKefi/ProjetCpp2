#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include <QMessageBox>
#include<QSqlQueryModel>
#include <QtDebug>
#include<QSqlError>
#include <QTextDocument>
#include <QPrinter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QHttpMultiPart>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QEventLoop>

#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator( new QIntValidator(0,99999999, this));
    ui->le_telephone->setValidator( new QIntValidator(0,99999999, this));
    ui->tab_employe->setModel(E.afficher());
    //ui->setupUi(this);
    foreach(const QSerialPortInfo &serial_info,QSerialPortInfo::availablePorts() ){


                           qDebug()<<"PUERTO /"<<serial_info.portName();
                           qDebug()<<"cendr id /"<<serial_info.vendorIdentifier();
                           qDebug()<<"prouct id id /"<<serial_info.productIdentifier();

                       }

                       int ret=A.connect_arduino(); // lancer la connexion à arduino
                               switch(ret){
                               case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                                   break;
                               case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                                  break;
                               case(-1):qDebug() << "arduino is not available";
                               }
                                QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
                                //le slot update_label suite à la reception du signal readyRead (reception des données).

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{
 data=0;

while((A.getdata().size()<5))
{
    QString key;
data=A.read_from_arduino();

break;

}
if(!data.isEmpty())
{qDebug() << data;

//qDebug()<<data.toLongLong();
}
if(!data.isEmpty())
{

//qDebug()<<data.toLongLong();
qDebug()<<"poids:"<<A.chercherid(data);
if(A.chercherid(data)!=0)
{
  A.write_to_arduino("1");

}

else if(A.chercherid(data)==0)
{A.write_to_arduino("0");

}


}
 data=0;
}
void MainWindow::on_pb_ajouter_clicked()
{
    int Cin_employe=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    int num_telephone=ui->le_telephone->text().toInt();
    QString gestion;
    if (ui->radLogement->isChecked()) {gestion="Logement";}
    if (ui->radVoyageurs->isChecked()){gestion="Voyageur";}
    if (ui->radTransport->isChecked()){gestion="Transport";}
    if (ui->radEmployes->isChecked()) {gestion="Employes";}
    if (ui->radSponso->isChecked())   {gestion="Sponsor";}
    if (ui->radFinance->isChecked())  {gestion="Finance";}
    QString gender=ui->gender->text();
    Employes E(Cin_employe,nom,prenom,adresse,num_telephone,gestion,gender);
    clear();
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_employe ->setModel(E.afficher());
        msgBox.setText("ajout avec succes.");
        A.write_to_arduino("1");
    }

    else
        msgBox.setText("Echec d'ajout");
    A.write_to_arduino("0");
    msgBox.exec();

}


void MainWindow::on_pb_supprimer_clicked()
{
    Employes E1;
    E1.setCin_employe(ui->le_cin_supp->text().toInt());

    bool test=E1.supprimer(E1.getCin_employe());
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_employe->setModel(E.afficher());
        msgBox.setText("Suppression avec succes.");
    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    QString val=ui->tab_employe->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from TABLEAU_EMPLOYE where CIN='"+val+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_cin->setText(qry.value(0).toString());
            ui->le_nom->setText(qry.value(1).toString());
            ui->le_prenom->setText(qry.value(2).toString());
            ui->le_adresse->setText(qry.value(3).toString());
            ui->le_telephone->setText(qry.value(4).toString());
            ui->gender->setText(qry.value(6).toString());


        }
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void MainWindow::on_pb_modifier_clicked()
{
    QString Cin_employe=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
     int num_telephone=ui->le_telephone->text().toInt();
    //QString res1 = QString::number(Cin_employe);
    QString gestion;
    if (ui->radLogement->isChecked()) {gestion="Logement";}
    if (ui->radVoyageurs->isChecked()){gestion="Voyageur";}
    if (ui->radTransport->isChecked()){gestion="Transport";}
    if (ui->radEmployes->isChecked()) {gestion="Employes";}
    if (ui->radSponso->isChecked())   {gestion="Sponsor";}
    if (ui->radFinance->isChecked())  {gestion="Finance";}
    QString gender=ui->gender->text();
    QString res = QString::number(num_telephone);
    QSqlQuery quer;
    quer.prepare("update TABLEAU_EMPLOYE set nom='"+nom+"' , PRENOM='"+prenom+"', ADRESSE='"+adresse+"', TELEPHONE='"+res+"', GESTION='"+gestion+"',GENDER='"+gender+"' where CIN='"+Cin_employe+"'");
    if(quer.exec())
    {

        ui->tab_employe->setModel(E.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué \n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                              QObject::tr("modification non effectué \n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pb_rechercher_clicked()
{
    Employes E;
    QString choix=ui->comboBox_rech->currentText();

    if (choix=="CIN")
    {
        QString Cin_employe= ui->lineEdit_rech->text();
        ui->table_rechercher->setModel(E.rechercher(Cin_employe));
    }
    if (choix=="NOM")
    {
        QString nom = ui->lineEdit_rech->text();
        ui->table_rechercher->setModel(E.recherchernom(nom));
    }
    if (choix=="PRENOM")
    {
        QString prenom = ui->lineEdit_rech->text();
        ui->table_rechercher->setModel(E.rechercherprenom(prenom));
    }
}




void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Employes E;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(arg1 != "Choisir")
        ui->tab_employe->setModel(E.Trier_em(type,arg1));

    else  ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_radioButton_clicked()
{
    Employes E;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
        ui->tab_employe->setModel(E.Trier_em(type,ui->comboBox->currentText()));

    else  ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_radioButton_2_clicked()
{
    Employes E;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
        ui->tab_employe->setModel(E.Trier_em(type,ui->comboBox->currentText()));

    else  ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/PDFEmploye.pdf");

       QPainter painter(&pdf);

       int i = 4000;
       painter.setPen(Qt::red);
       painter.setFont(QFont("Arial", 30));
       painter.drawPixmap(QRect(200,200,2000,2000),QPixmap("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/logo.png")); //"C:/Users/PMS-BLA-5-Chloe/Desktop/resources/logo.png"
       painter.drawText(3000,1500,"LISTE DES EMPLOYES");
       painter.setPen(Qt::black);
       painter.setFont(QFont("Arial", 50));
       painter.drawRect(2700,200,7300,2600);
       painter.drawRect(0,3000,9600,500);
       painter.setFont(QFont("Arial", 9));
       painter.drawText(300,3300,"CIN");
       painter.drawText(2300,3300,"NOM");
       painter.drawText(4300,3300,"PRENOM");
       painter.drawText(6300,3300,"ADRESSE");
       painter.drawText(8000,3300,"TELEPHONE");
       QSqlQuery query;
       query.prepare("select * from TABLEAU_EMPLOYE");
       query.exec();
       while (query.next())
       {
           painter.drawText(300,i,query.value(0).toString());
           painter.drawText(2300,i,query.value(1).toString());
           painter.drawText(4300,i,query.value(2).toString());
           painter.drawText(6300,i,query.value(3).toString());
           painter.drawText(8000,i,query.value(4).toString());
           i = i +500;
       }

       int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
       if (reponse == QMessageBox::Yes)
       {
           QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/PDFEmploye.pdf"));

           painter.end();
       }
       if (reponse == QMessageBox::No)
       {
           painter.end();
       }

   }


void MainWindow::clear()
{
    ui->le_cin->clear();
    ui->le_nom->clear();
    ui->le_prenom->clear();
    ui->le_adresse->clear();
    ui->le_telephone->clear();
    ui->gender->clear();

}


void MainWindow::postrequest(QString smsmsg,QString phonenumber)
{

    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl( QString("https://api.orange.com/smsmessaging/v1/outbound/tel%3A%2B322804/requests") ) );

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



    req.setRawHeader("Authorization", "Bearer igVk1vQQZQD8a3ngQsG8svBgd6D4"); //aocjZcUXHzvAmMRPgfT0XF7m2PNU
    QJsonObject msg;
    msg["message"] = smsmsg;
    QJsonObject obj;
    obj["address"] = "tel:+216"+phonenumber;
    obj["senderAddress"] = "tel:+322804";
    obj["outboundSMSTextMessage"] = msg;
    QJsonObject body;
    body["outboundSMSMessageRequest"] = obj;
    QJsonDocument doc(body);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = mgr.post(req,data);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<reply->readAll();
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString() << reply->error();
        delete reply;
    }
}

void MainWindow::on_PushEnvoyerSMS_clicked()
{
    QString numtel=ui->LineSMSNum->text();
    QString msg=ui->textEdit->toPlainText();
    postrequest(msg,numtel);
}
void MainWindow::on_pushPlay_clicked()
{
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);

    if (ui->radLogement->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/Logement.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->radVoyageurs->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/Voyageur.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->radTransport->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/Transport.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->radEmployes->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/employes.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->radSponso->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/Sponso.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    if (ui->radFinance->isChecked())
    {
        player->setMedia(QUrl::fromLocalFile("C:/Users/AHINFO/Desktop/Projet QT/projetqtrayen/Finance.mp4"));
        player->setVideoOutput(ui->VideoInterface);
    }
    vw->show();
    player->play();
}
void MainWindow::on_pushStop_clicked()
{
    player->stop();
    vw->close();
}

void MainWindow::on_stat_clicked()
{
    QChartView *chartView = E.stat_gender();
    chartView->show();
}


