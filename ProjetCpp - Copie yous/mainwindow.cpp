#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logement.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTextDocument>
#include <QDebug>
#include <QLabel>
#include <QChartView>
#include <QtCharts>
#include <QTextStream>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QGraphicsView>
#include <QTabWidget>
#include <QMovie>
#include <QRegExpValidator>
#include <QFile>
#include <QCoreApplication>
#include <QLineEdit>
#include "windows.h"
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QStateMachine>
#include <QPrinter>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_nom->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_ ]+"), this ));
    ui->la_adresse->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0-9_ ]+"), this ));
    ui->tab_logement->setModel(E.afficher());
    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    //maps
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");


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
    QString adresse=ui->la_adresse->text();
    ui->la_adresse->clear();
Logement E(id,nom,adresse);
bool test=E.ajouter();
QMessageBox msgBox;

if (test)
{
    msgBox.setText("ajout avec succes");
    ui->tab_logement->setModel(E.afficher());
}
else
    msgBox.setText("echec d'ajout");
msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{
    Logement E1;
    E1.setid(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getid());
    ui->le_id_supp->clear();
    QMessageBox msgBox;

    if (test)
    {
        msgBox.setText("suppression avec succes");
        ui->tab_logement->setModel(E.afficher());
    }
    else
        msgBox.setText("echec de suppression");
    msgBox.exec();
}
void MainWindow::on_pb_rech_clicked()
{
    Logement c;
       QString choix=ui->cb_rech->currentText();

       if (choix=="Id")
       {
           QString id= ui->le_rech->text();
           ui->tab_rech->setModel(c.rechercher(id));
       }
       if (choix=="Nom")
       {
           QString nom = ui->le_rech->text();
           ui->tab_rech->setModel(c.recherchernom(nom));
       }
       if (choix=="Adresse")
       {
           QString adresse = ui->le_rech->text();
           ui->tab_rech->setModel(c.rechercheradresse(adresse));
       }
       ui->le_rech->clear();
}
void MainWindow::on_pb_modifier_clicked()
{

        int id=ui->le_id1->text().toInt();
        QString nom=ui->le_nom1->text();
        QString adresse=ui->le_adresse1->text();

        QString res1 = QString::number(id);


        QSqlQuery quer;
        quer.prepare("update logement set ID='"+res1+"' ,NOM='"+nom+"',ADRESSE='"+adresse+"' WHERE NOM='"+nom+"'");
          if(quer.exec())
          {

              ui->tab_logement->setModel(E.afficher());
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
          }
          else
              QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                    QObject::tr("modification non effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);

}
void MainWindow::on_rb_a_clicked()
{Logement v;
    QString adresse="";


    if(ui->rb_a->isChecked())
        adresse="Ascendant";
    else if(ui->rb_d->isChecked())
        adresse="Descendant";

    if(ui->cb_tri->currentText() != "Choisir")
        ui->tab_logement->setModel(v.trie_log(adresse,ui->cb_tri->currentText()));

    else  ui->tab_logement->setModel(v.afficher());

}

void MainWindow::on_rb_d_clicked()
{Logement v;
    QString adresse="";


    if(ui->rb_d->isChecked())
        adresse="Descendant";
    else if(ui->rb_d->isChecked())
       adresse="Descendant";

    if(ui->cb_tri->currentText() != "Choisir")
        ui->tab_logement->setModel(v.trie_log(adresse,ui->cb_tri->currentText()));

    else  ui->tab_logement->setModel(v.afficher());

}

void MainWindow::on_pb_pdf_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tab_logement->model()->rowCount();
   const int columnCount = ui->tab_logement->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des Logements </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tab_logement->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tab_logement->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_logement->isColumnHidden(column)) {
     QString data = ui->tab_logement->model()->data(ui->tab_logement->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}

void MainWindow::on_tab_logement_activated(const QModelIndex &index)
{
    QString select=ui->tab_logement->model()->data(index).toString();
     QSqlQuery qry;

      qry.prepare("select * from logement where  NOM LIKE '"+select+"%'  ");
     if(qry.exec())
     {
      while(qry.next())
      {
       ui->le_id1->setText(qry.value(0).toString());
       ui->le_nom1->setText(qry.value(1).toString());
       ui->le_adresse1->setText(qry.value(2).toString());
      }

}
}
//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedaziz.benhaha@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
