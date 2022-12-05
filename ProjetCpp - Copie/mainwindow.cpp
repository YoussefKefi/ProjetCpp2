#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voyageur.h"
#include "ui_login.h"
#include "login.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QString>
#include<QTextDocument>
#include <QDebug>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QChartView>
#include <QtCharts>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QTextDocument>
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QGraphicsView>
#include <QTabWidget>
#include <QLabel>
#include <QMovie>
#include<QMessageBox>
#include <QRegExpValidator>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include "windows.h"
#include <QTimer>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include<QMessageBox>
#include <QRegExpValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStateMachine>

#include <QPdfWriter>
#include "qrcodegen.hpp"
#include <QLabel>
#include <QMovie>
#include<QMessageBox>
#include <QRegExpValidator>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include "windows.h"
#include <QTimer>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QPainter>
#include <QPdfWriter>
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include<QMessageBox>
#include <QRegExpValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPdfWriter>
#include <QStackedWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
ui->tab_voyageur->setModel(E.afficher());
E.stat_id()->setParent(ui->stat_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    ui->le_id->clear();
    QString nom=ui->le_nom->text();
     ui->le_nom->clear();
    QString prenom=ui->le_prenom->text();
     ui->le_prenom->clear();
voyageur E(id,nom,prenom);
bool test=E.ajouter();
QMessageBox msgBox;

if (test)
{
    msgBox.setText("ajout avec succes");
    ui->tab_voyageur->setModel(E.afficher());
}
else
    msgBox.setText("echec d'ajout");
msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{
    voyageur E1;
    E1.setid(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getid());
    QMessageBox msgBox;

    if (test)
    {
        msgBox.setText("suppression avec succes");
        ui->tab_voyageur->setModel(E.afficher());
    }
    else
        msgBox.setText("echec de suppression");
    msgBox.exec();
}


void MainWindow::on_pb_rechercher_clicked()
{
        voyageur v;
        QString choix=ui->comboBox_rech->currentText();

                if (choix=="identifiant")
                {
                    QString identifiant= ui->rechercher->text();
                    ui->tab_voyageur->setModel(v.rechercheridentifiant(identifiant));
                }
                if (choix=="nom")
                {
                    QString nom= ui->rechercher->text();
                    ui->tab_voyageur->setModel(v.recherchernom(nom));
                }
                if (choix=="prenom")
                {
                    QString prenom= ui->rechercher->text();
                    ui->tab_voyageur->setModel(v.rechercherprenom(prenom));
                }


}


void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id->text().toInt();
     QString nom=ui->le_nom->text();
     QString prenom=ui->le_prenom->text();



       voyageur v(id,nom,prenom);
      bool test=v.modifier();
      QMessageBox msgBox;
      if(test)
      {
          msgBox.setText("modification avec succes.");
          ui->tab_voyageur->setModel(v.afficher());
          ui->le_id->clear();
          ui->le_nom->clear();
          ui->le_prenom->clear();

      }
      else
          msgBox.setText("Echec de modification");
      msgBox.exec();
    }


void MainWindow::on_radioButton_a_clicked()
{voyageur v;
    QString prenom="";


    if(ui->radioButton_a->isChecked())
        prenom="ASC";
    else if(ui->radioButton_d->isChecked())
       prenom="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_voyageur->setModel(v.trie_voy(prenom,ui->comboBox_trie->currentText()));

    else  ui->tab_voyageur->setModel(v.afficher());

}

void MainWindow::on_radioButton_d_clicked()
{voyageur v;
    QString prenom="";


    if(ui->radioButton_d->isChecked())
        prenom="DESC";
    else if(ui->radioButton_d->isChecked())
       prenom="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_voyageur->setModel(v.trie_voy(prenom,ui->comboBox_trie->currentText()));

    else  ui->tab_voyageur->setModel(v.afficher());

}


void MainWindow::on_tab_voyageur_activated(const QModelIndex &index)
{
    QString val=ui->tab_voyageur->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from ETUDIANT where id='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->le_nom->setText(qry.value(1).toString());
      ui->le_prenom->setText(qry.value(2).toString());
      ui->le_id->setText(qry.value(0).toString());


     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}




void MainWindow::on_pdf_clicked()
{
    QTableView tab_equipement;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->le_id->text();
         //Connection c;

         QSqlQuery qry;
         qry.prepare("select * from ETUDIANT where id='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         tab_equipement.setModel(Mod);
         //c.closeconnection();

         QString strStream;
         QTextStream out(&strStream);


         const QString strTitle ="Document";



         out <<  "<html>\n"
                               //"<img src=':/icons/icons/icone.png'/>"
                              "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              <<  QString("<title>%1</title>\n").arg(strTitle)
                              <<  "</head>\n"
                                  "<style> h3{"
                                  "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                  "}\n"
                                  "</style>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                             << QString("<h1 style=\" font-size: 40px; font-family: Century Gothic; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche Equipements")
                             <<"<br>";

                        QString id = tab_equipement.model()->data( tab_equipement.model()->index(0, 0)).toString().simplified();//bech lawej aala reference fel table bel colonne yemchi hotha pdf

                            qDebug()<<id;
                            out << QString("<h3>nom : %1</h3>").arg((!id.isEmpty()) ? id : QString("&nbsp;"));
                            QString libelle = tab_equipement.model()->data( tab_equipement.model()->index(0, 1)).toString().simplified();
                            out << QString("<h3>prenom : %1</h3>").arg((!libelle.isEmpty()) ? libelle : QString("&nbsp;"));
                            QString emplacement =  tab_equipement.model()->data( tab_equipement.model()->index(0, 2)).toString().simplified();
                            out << QString("<h3> id : %1</h3>").arg((!emplacement.isEmpty()) ? libelle : QString("&nbsp;"));
                            QString type =  tab_equipement.model()->data( tab_equipement.model()->index(0, 3)).toString().simplified();//out thotha fi fichier ailleurs
                            out << QString("<h3 bkcolor=0>type %1</h3>").arg((!type.isEmpty()) ? type : QString("&nbsp;"));



                            out<<
                              "</body>\n"
                              "</html>\n";

                                  QTextDocument *document = new QTextDocument();
                                                  document->setHtml(strStream);

                                                  QPrinter printer;
                                                  QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                                  if (dialog->exec() == QDialog::Accepted) {

                                                      document->print(&printer);
                                                  }

                                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                                  printer.setPaperSize(QPrinter::A2);
                                                  printer.setOutputFileName("/tmp/.pdf");
                                                  printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                                  delete document;
}
/*void login::on_identifi_clicked()
{
    cadmin ca(ui->lineEditnomnutilisateur->text(),ui->lineEdit_motdepasse->text());
        QString nomuitlisateur=ui->lineEditnomnutilisateur->text();
        QString motdepasse=ui->lineEdit_motdepasse->text();

        if(ca.authentification()==1)
        {


            QMessageBox::information(this,"identifier","nom d'utilisateur et mot de passe sont correct");
            //hide();
            gc  = new MainWindow(this);
            gc->show();

        }
        else if (ca.authentification()<1)
        {

            QMessageBox::information(this,"identifier","nom d'utilisateur et mot de passe ne sont pas correct");
        }
}*/


void MainWindow::on_pb_qrcode_clicked()
{
    using namespace qrcodegen;

          ///////////////// FETCH DATA FROM DATABASE ////////////////////////
          QTableView tab_voyageur;
          QSqlQueryModel * Mod=new  QSqlQueryModel();
          QString value=ui->le_id->text();


               QSqlQuery qry;




               qry.prepare("select * from ETUDIANT where ID ='"+value+"'");
               qry.exec();
               Mod->setQuery(qry);
               tab_voyageur.setModel(Mod);


              ///////////////// SAVING DATA ///////////
              QString ID = tab_voyageur.model()->data(tab_voyageur.model()->index(0, 0)).toString().simplified();
              QString nom= tab_voyageur.model()->data(tab_voyageur.model()->index(0, 1)).toString().simplified();
              QString prenom = tab_voyageur.model()->data(tab_voyageur.model()->index(0, 2)).toString().simplified();


          QString text = ""+ID+"\n"+nom+"\n"+prenom+"\n";
            // Create the QR Code object
            QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

            qint32 sz = qr.getSize();
            QImage im(sz,sz, QImage::Format_RGB32);
              QRgb black = qRgb( 191,112,105 );
              QRgb white = qRgb(255,255,255);
            for (int y = 0; y < sz; y++)
              for (int x = 0; x < sz; x++)
                im.setPixel(x,y,qr.getModule(x, y) ? black : white );//setpixelmap tafichilek qr code
            ui->qrcode->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}
void MainWindow::on_login_boutton_clicked()
{
    QString email = ui->email_login->text();
      QString mdp = ui->mdp_login->text();
      int test;
      test=E.login(email,mdp);
          if (test==0)
          {
              QMessageBox::critical(nullptr, QObject::tr("Echèc"),
                          QObject::tr("Mot de passe ou nom non valide.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

          }
          else
          {
  // ui->QStackedWidget->setCurrentIndex(0);
              QMessageBox::critical(nullptr, QObject::tr("valide"),
                          QObject::tr("Mot de passe ou nom  valide.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          }
}


