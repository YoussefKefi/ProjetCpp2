#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sponsoring.h"
#include <QMessageBox>

#include <QValidator>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QIntValidator>
#include <QTextStream>
#include <QFileDialog>
//#include <QPrinter>
#include <QTextDocument>


/*
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLegend>


#include <QChart>
#include <QtCharts>
#include <QGraphicsView>
#include <QChart>
#include <QtCharts>
#include <QMessageBox>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>
*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->id->setValidator( new QIntValidator(0, 999999999, this));
     ui->tab_sponsoring->setModel(s.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_2_clicked()
{
       int id=ui->id->text().toInt();
       QString nom=ui->nom->text();
       QString domaine=ui->domaine->text();
       int duree=ui->duree->text().toInt();
       int budget=ui->budget->text().toInt();
       Sponsoring s(id,nom,domaine,duree,budget);
       bool test=s.ajouter();
       QMessageBox msgBox;

            if(test)
            {
                ui->tab_sponsoring->setModel(s.afficher());
                 msgBox.setText("ajout avec succes.");
            }

          else
              msgBox.setText("Echec d'ajout");
              msgBox.exec();
}


void MainWindow::on_supprimer_3_clicked()
{
    Sponsoring s1;
       s1.setid(ui->id_2->text().toInt());
       bool test=s1.supprimer(s1.getid());
       QMessageBox msgBox;
       if(test)
       {
           ui->tab_sponsoring->setModel(s.afficher());
           msgBox.setText("Suppression avec succes.");
       }
       else
           msgBox.setText("Echec de suppression");
       msgBox.exec();
}

void MainWindow::on_modif_clicked()
{
    int id=ui->id->text().toInt();
    QString nom=ui->nom->text();
    QString domaine=ui->domaine->text();
    int duree=ui->duree->text().toInt();
    int budget=ui->budget->text().toInt();
    QString res1 = QString::number(id);
    QString res2 = QString::number(duree);
    QString res3 = QString::number(budget);
    QSqlQuery quer;
     quer.prepare("update SPONSORING set id='"+res1+"' ,nom='"+nom+"', domaine='"+domaine+"', duree='"+res2+"' , budget='"+res3+"' where nom='"+nom+"'");
     if(quer.exec())
              {

                  ui->tab_sponsoring->setModel(s.afficher());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("modification effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
              }
              else
                  QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                        QObject::tr("modification non effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
}







void MainWindow::on_rech_textChanged(const QString &arg1)
{
    QString search=arg1;
           ui->tab_sponsoring->setModel(s.Rechercher(search));
}







////////////////////////////////////////////////////////////////////////

void MainWindow::on_comboBox_activated(const QString &arg1)
{

    Sponsoring s;
        QString nom="";

        if(ui->radioButton->isChecked())
            nom="ASC";
        else if(ui->radioButton_2->isChecked())
            nom="DESC";

        if(arg1 != "Choisir")
            ui->tab_sponsoring->setModel(s.Trier(nom,arg1));

        else  ui->tab_sponsoring->setModel(s.afficher());

}





void MainWindow::on_radioButton_clicked()
{
    Sponsoring s;
        QString nom="";


        if(ui->radioButton->isChecked())
            nom="ASC";
        else if(ui->radioButton_2->isChecked())
            nom="DESC";

        if(ui->comboBox->currentText() != "Choisir")
            ui->tab_sponsoring->setModel(s.Trier(nom,ui->comboBox->currentText()));

        else  ui->tab_sponsoring->setModel(s.afficher());


   }






void MainWindow::on_radioButton_2_clicked()
{

   Sponsoring s;
       QString nom="";

       if(ui->radioButton->isChecked())
           nom="ASC";
       else if(ui->radioButton_2->isChecked())
           nom="DESC";

       if(ui->comboBox->currentText() != "Choisir")
           ui->tab_sponsoring->setModel(s.Trier(nom,ui->comboBox->currentText()));


       else  ui->tab_sponsoring->setModel(s.afficher());



}




//////////////////////////////////////////////////////////////////////


void MainWindow::on_actionplay_video_triggered()
{
    player= new QMediaPlayer;
        vw=new QVideoWidget;

        auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


        player->setVideoOutput(vw);
        player->setMedia(QUrl::fromLocalFile(filename));
        vw->setGeometry(100,100,300,400);
        vw->show();
        player->play();
}

void MainWindow::on_actionstop_video_triggered()
{
    player->stop();
       vw->close();
}

void MainWindow::on_camera_clicked()
{
    c= new camera();
       c->show();
}
/*
void MainWindow::on_statisticButton_clicked()
{
    Sponsoring s;
        QChartView * chartView=new QChartView(s.statistic());
        chartView ->setParent(ui->statisticFrame);
        chartView->setFixedSize(ui->statisticFrame->size());
        ui->stackedWidget->setCurrentIndex(10);
}
*/
