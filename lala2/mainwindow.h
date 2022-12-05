#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
//#include <QPrinter>
#include <QMediaPlayer>
#include <QVideoWidget>
#include"Sponsoring.h"
#include <QModelIndex>

//#include <QChartView>

#include "camera.h"

#include "qchar.h"

//#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLegend>
/*
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



    void on_ajouter_2_clicked();

    void on_supprimer_3_clicked();

    void on_modif_clicked();

    void on_rech_textChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_actionplay_video_triggered();

    void on_actionstop_video_triggered();

    void on_camera_clicked();

    void on_statisticButton_clicked();

private:
    Ui::MainWindow *ui;
    Sponsoring s ;
    QMediaPlayer* player;
        QVideoWidget* vw;
        camera *c;
};

#endif // MAINWINDOW_H
