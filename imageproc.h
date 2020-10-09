#ifndef IMAGEPROC_H
#define IMAGEPROC_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "qimage.h"

class ImageProc
{
public:
    ImageProc();
    static QImage matToQImage(cv::Mat src);
    static double fitMinSize(int &width, int &height, int dst_width, int dst_height, int &direction);
};

#endif
