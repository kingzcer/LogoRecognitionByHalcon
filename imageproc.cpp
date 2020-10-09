#include "imageproc.h"

ImageProc::ImageProc()
{

}

QImage ImageProc::matToQImage(cv::Mat src)
{
    if(src.channels() == 3)
    {
        cv::Mat temp;
        cv::cvtColor(src, temp, cv::COLOR_BGR2RGB);
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


double ImageProc::fitMinSize(int &width, int &height, int dst_width, int dst_height, int &direction)
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
