#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "transport.h"
#include "dialog_statistiques.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushAjouter_2_clicked();

    void on_pushModifier_2_clicked();

    void on_pushSupprimer_4_clicked();

    void on_pushTriMoyen_clicked();

    void on_psuhTriVoyageurs_clicked();

    void on_pushTriMatricule_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_lineRecherche_2_textChanged(const QString &arg1);

    void on_psuhBusStation_clicked();

    void on_pushAirport_clicked();

    void on_pushTrainStation_clicked();
    void on_pushPDF_clicked();

    void on_pushStat_clicked();

private:
    Ui::MainWindow *ui;
    transport T;
    Dialog_Statistiques *s;
};
#endif // MAINWINDOW_H
