#ifndef SCALEDSHAPEMODEL_H
#define SCALEDSHAPEMODEL_H
#include "halconcv.h"

class ScaledShapeModel
{
public:
    ScaledShapeModel();

    std::vector<cv::RotatedRect> findScaledShapeModel(cv::Mat src);
    void createScaledShapeModel(cv::Mat model);

private:
    HTuple  hv_ModelID;
    int m_width;
    int m_height;
};

#endif // SCALEDSHAPEMODEL_H
