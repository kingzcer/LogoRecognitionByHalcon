#ifndef FINDINFOLDER_H
#define FINDINFOLDER_H

#include <QThread>
#include <scaledshapemodel.h>

class FindInFolder: public QThread
{
    Q_OBJECT
public:
    FindInFolder();
    void run();
    void setFolder(QString folder);

private:
    QString m_folder;
    ScaledShapeModel *m_model;

signals:
    void progress(double p);
};

#endif // FINDINFOLDER_H
