#include "scaledshapemodel.h"

ScaledShapeModel::ScaledShapeModel()
{

}


void ScaledShapeModel::createScaledShapeModel(cv::Mat model)
{
     HObject  ho_ImageReduced;
     m_width = model.cols;
     m_height = model.rows;
     ho_ImageReduced = HalconCV::matToHobject(model);
     CreateScaledShapeModel(ho_ImageReduced, 5, HTuple(-45).TupleRad(), HTuple(90).TupleRad(),
           "auto", 0.5, 1.5, "auto", "none", "ignore_global_polarity", 40, 10, &hv_ModelID);
}

std::vector<cv::RotatedRect> ScaledShapeModel::findScaledShapeModel(cv::Mat src)
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
            rect.size = cv::Size(m_width * scale, m_height * scale);

            rects.push_back(rect);
        }
    }

    return rects;
}
