#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"employes.h"
#include <QModelIndex>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <arduino.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();
    void update_label();


    void on_pb_modifier_clicked();
    void on_tab_employe_activated(const QModelIndex &index);

    void on_pb_rechercher_clicked();


    void on_comboBox_activated(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushPlay_clicked();

    void on_pushStop_clicked();

    void on_PDF_clicked();
    void clear();  
    void on_PushEnvoyerSMS_clicked();void postrequest(QString smsmsg,QString phonenumber);

    void on_stat_clicked();

    void on_pushButton_clicked();
    
private:
    Ui::MainWindow *ui;
    Employes E;
    QMediaPlayer* player;
    QVideoWidget* vw;
    Arduino A;
    QByteArray data;
};

#endif // MAINWINDOW_H
