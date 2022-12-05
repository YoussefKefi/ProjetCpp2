#include "dialog_statistiques.h"
#include "ui_dialog_statistiques.h"

Dialog_Statistiques::Dialog_Statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Statistiques)
{
    ui->setupUi(this);
}

Dialog_Statistiques::~Dialog_Statistiques()
{
    delete ui;
}
void Dialog_Statistiques::choix_pie()
{
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM TRANSPORT");
    q1.exec();
    q2.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Bus'");
    q2.exec();
    q3.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Avion'");
    q3.exec();
    q4.prepare("SELECT * FROM TRANSPORT WHERE MOYEN='Train' ");
    q4.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("Bus",c1);
    series->append("Avion",c2);
    series->append("Train",c3);
    // Create the chart widget
    QChart *chart = new QChart();
    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();
    // Used to display the chart
    chartView = new QChartView(chart,ui->label);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);
    chartView->show();
}
