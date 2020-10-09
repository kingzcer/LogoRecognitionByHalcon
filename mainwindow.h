#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "halconcv.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QTimer>
#include <imageproc.h>
#include <findinfolder.h>

namespace Ui {
class MainWindow;
}

using namespace cv;
using namespace HalconCpp;
using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void display(cv::Mat src);
    cv::Mat m_frame;

private:
    Ui::MainWindow *ui;
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;

    QTimer *m_timer;
    FindInFolder *m_finder;

public slots:
    void on_timeout();
    void progress(double p);
private slots:
    void on_action_chooseFolder_triggered();
};

#endif // MAINWINDOW_H
