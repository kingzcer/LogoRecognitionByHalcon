#ifndef HALCONCV_H
#define HALCONCV_H

#include <opencv2/opencv.hpp>
#include <HalconCpp.h>
#include <Halcon.h>

using namespace cv;
using namespace HalconCpp;
using namespace std;

class HalconCV
{
public:
    HalconCV();
    static Mat HobjectToMat(HObject Hobj);
    static HObject matToHobject(Mat& image);
};

#endif // HALCONCV_H
