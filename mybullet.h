#ifndef MYBULLET_H
#define MYBULLET_H
#include "configuration.h"
#include "myflight.h"
class MyBullet
{
public:
    MyBullet();
    void MyB_Move();
public:
    int MyBullet_X;
    int MyBullet_Y;
    int MyB_Model;
    int MyB_Hurt;
    QRect MyB_Outline;
};

#endif // MYBULLET_H
