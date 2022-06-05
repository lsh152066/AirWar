#ifndef ENEMYFLIGHT_H
#define ENEMYFLIGHT_H
#include "configuration.h"
#include "enemybullet.h"

class EnemyFlight
{
public:
    EnemyFlight();

    void EnF_Move();


public:
    //敌方飞机
    int flag=0;
    int EnFX;
    int EnFY = -150;
    int EnF_Model;
    int EnF_Life=1;
    QRect EnF_Outline;

};

#endif // ENEMYFLIGHT_H
