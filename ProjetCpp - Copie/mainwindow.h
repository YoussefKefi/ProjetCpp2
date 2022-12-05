#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "logement.h"
#include <QMainWindow>
#include "smtp.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

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

    void on_pb_rech_clicked();

    void on_pb_modifier_clicked();

    void on_rb_a_clicked();

    void on_rb_d_clicked();

    void on_pb_pdf_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();

    void on_tab_logement_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Logement E;
    QStringList files;
};

#endif // MAINWINDOW_H
