#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "voyageur.h"
#include <QMainWindow>

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
    void on_pb_rechercher_clicked();

    //void on_pb_modifier_clicked();

    void on_pb_modifier_clicked();

    void on_radioButton_a_clicked();

    void on_radioButton_d_clicked();

void on_tab_voyageur_activated(const QModelIndex &index);


    void on_pdf_clicked();

    void on_pb_qrcode_clicked();

    void on_login_boutton_clicked();

private:
    Ui::MainWindow *ui;
    voyageur E;
};

#endif // MAINWINDOW_H
