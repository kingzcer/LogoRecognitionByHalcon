#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

cv::VideoCapture cap;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_view = ui->graphicsView;

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_timer->start(33);

    m_finder = new FindInFolder();
    connect(m_finder, SIGNAL(progress(double)), this, SLOT(progress(double)));

    cap.open(0);
    if(!cap.isOpened())
        QMessageBox::about(this, "error", "open camera failed!");
        return;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timeout()
{
    cap >> m_frame;
    if(m_frame.empty())
    {
        return;
    }
    display(m_frame);
}

void MainWindow::display(Mat src)
{
    int width = src.cols, height = src.rows;
    int direction;
    ImageProc::fitMinSize(width, height, m_view->width(), m_view->height(), direction);
    cv::resize(src, src, cv::Size(width, height));
    QImage Qimg = ImageProc::matToQImage(src);
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

void MainWindow::progress(double p)
{
    ui->statusBar->showMessage(QString::number(p) + "%");
}

void MainWindow::on_action_chooseFolder_triggered()
{
    QString folder = QFileDialog::getExistingDirectory(this, "choose Folder");
    m_finder->setFolder(folder);
    m_finder->start();

}
