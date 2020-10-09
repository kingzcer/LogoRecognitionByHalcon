#include "findinfolder.h"
#include <QDir>
#include <QFileInfoList>
#include <iostream>

FindInFolder::FindInFolder()
{
    m_model = new ScaledShapeModel();
    cv::Mat src = cv::imread("data/yyzz.png", 1);

    m_model->createScaledShapeModel(src);
}

void FindInFolder::run()
{
    QDir dir(m_folder);
    if(!dir.exists())
    {
        return;
    }

    QString path = "E:\\Projects\\LogoRecognitionByHalcon\\data\\yyzz";
    QDir save_dir(path);
    if(!save_dir.exists())
    {
        std::cout << "create new dir" << std::endl;
        save_dir.mkdir(path);
    }

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files);
    double p;
    int total_num = fileInfoList.size();

    for(int i=0; i<fileInfoList.size(); i++)
    {
        QFileInfo info = fileInfoList.at(i);
        std::cout << info.absoluteFilePath().toStdString() <<std::endl;
        cv::Mat src = cv::imread(info.absoluteFilePath().toStdString(), 1);
        if(src.empty())
        {
            continue;
        }

        std::vector<cv::RotatedRect> rects = m_model->findScaledShapeModel(src);
        if(rects.size() > 0)
        {
            QString result_path = path;
            result_path.append("\\");
            result_path.append(info.baseName());
            result_path.append(".jpg");
            cv::imwrite(result_path.toStdString(), src);
        }
        p = i / (double)total_num;
        //std::cout << p << std::endl;
        progress(p);
    }
}

void FindInFolder::setFolder(QString folder)
{
    m_folder = folder;
}
