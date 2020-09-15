#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "halconcv.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QTimer>

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
    std::vector<cv::RotatedRect> findScaledShapeModel(cv::Mat src);
    void createScaledShapeModel(cv::Mat model);
    void drawRotatedRect(cv::RotatedRect rect, cv::Mat src);

    void display(cv::Mat src);

    void resizeEvent(QResizeEvent *event);
    cv::Mat m_frame;

private:
    Ui::MainWindow *ui;
    HTuple  hv_ModelID;
    int model_width;
    int model_height;

    QGraphicsView *m_view;
    QGraphicsScene *m_scene;

    QTimer *m_timer;

public slots:
    void on_timeout();
};

#endif // MAINWINDOW_H
