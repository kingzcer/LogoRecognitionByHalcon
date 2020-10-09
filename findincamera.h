#ifndef FINDINCAMERA_H
#define FINDINCAMERA_H

#include <QThread>
class FindInCamera : public QThread
{
public:
    FindInCamera();
    void run();
};

#endif // FINDINCAMERA_H
