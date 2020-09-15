#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

cv::VideoCapture cap;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::Mat model = cv::imread("data/dot.png", 1);
    createScaledShapeModel(model);

    m_scene = new QGraphicsScene();
    m_view = ui->graphicsView;

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_timer->start(33);

    cap.open(0);
    if(!cap.isOpened())
        QMessageBox::about(this, "error", "open camera failed!");
        return;
}

MainWindow::~MainWindow()
{
    ClearShapeModel(hv_ModelID);
    delete ui;
}

void MainWindow::on_timeout()
{
    cap >> m_frame;
    if(m_frame.empty())
    {
        return;
    }
    std::vector<cv::RotatedRect> rects = findScaledShapeModel(m_frame);
    for(int i=0; i<rects.size(); i++)
    {
        drawRotatedRect(rects[i], m_frame);
    }
    display(m_frame);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}

void MainWindow::createScaledShapeModel(cv::Mat model)
{
     HObject  ho_ImageReduced;

     model_width = model.cols;
     model_height = model.rows;
     ho_ImageReduced = HalconCV::matToHobject(model);
     CreateScaledShapeModel(ho_ImageReduced, 5, HTuple(-45).TupleRad(), HTuple(90).TupleRad(),
           "auto", 0.5, 1.5, "auto", "none", "ignore_global_polarity", 40, 10, &hv_ModelID);
}


void MainWindow::drawRotatedRect(cv::RotatedRect rect, cv::Mat src)
{
    cv::Point2f P[4];
    rect.points(P);

    for (int j = 0; j <= 3; j++)
    {
        cv::line(src, P[j], P[(j + 1) % 4], cv::Scalar(0,0,255),3);
    }
}

std::vector<cv::RotatedRect> MainWindow::findScaledShapeModel(cv::Mat src)
{
    HObject ho_ImageSearch;
    HTuple  hv_Row, hv_Column, hv_Angle, hv_Scale, hv_Score;
    HTuple  hv_I;

    std::vector<cv::RotatedRect> rects;

    ho_ImageSearch = HalconCV::matToHobject(src);
    FindScaledShapeModel(ho_ImageSearch, hv_ModelID, HTuple(-45).TupleRad(), HTuple(90).TupleRad(),
     0.8, 1.0, 0.5, 0, 0.5, "least_squares", 5, 0.8, &hv_Row, &hv_Column, &hv_Angle,&hv_Scale, &hv_Score);

    {
        HTuple end_val26 = (hv_Score.TupleLength())-1;
        HTuple step_val26 = 1;
        for (hv_I=0; hv_I.Continue(end_val26, step_val26); hv_I += step_val26)
        {
            double offset_x = hv_Column[hv_I];
            double offset_y = hv_Row[hv_I];
            double angle = hv_Angle[hv_I];
            double scale = hv_Scale[hv_I];

            cv::RotatedRect rect;
            rect.angle = angle * 57.29578;
            std::cout << angle << std::endl;
            rect.center = cv::Point(offset_x, offset_y);
            rect.size = cv::Size(model_width * scale, model_height * scale);

            rects.push_back(rect);

        }
    }

    return rects;
}

double fitMinSize(int &width, int &height, int dst_width, int dst_height, int &direction)
{
    double w = width, h = height;
    double a = dst_width / (double)dst_height;
    double b = width / (double)height;
    if(a > b)
    {
        height = dst_height;
        width = w * height / h;
        direction = 1;
        return h / (double)height;

    }else
    {
        width = dst_width;
        height = h * width / w;
        direction = -1;
        return w / (double)width;
    }
}

QImage matToQImage(cv::Mat src)
{
    if(src.channels() == 3)
    {
        cv::Mat temp;
        cv::cvtColor(src, temp, COLOR_BGR2RGB);
        QImage img = QImage((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        img.bits();
        return img;
    }else
    {
        QImage img((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),QImage::Format_Grayscale8);
        img.bits();
        return img;
    }
}

void MainWindow::display(Mat src)
{
    int width = src.cols, height = src.rows;
    int direction;
    fitMinSize(width, height, m_view->width(), m_view->height(), direction);
    cv::resize(src, src, cv::Size(width, height));
    QImage Qimg = matToQImage(src);
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(Qimg));

    if(direction > 0)
    {
        pixmapItem->setPos((m_view->width() - width) / 2, 0);
    }
    else
    {
        pixmapItem->setPos(0, (m_view->height() - height) / 2);
    }

    m_scene->clear();
    m_scene->setSceneRect(0,0,m_view->width(),m_view->height());
    m_scene->addItem(pixmapItem);
    m_view->setScene(m_scene);
    m_view->show();
}
