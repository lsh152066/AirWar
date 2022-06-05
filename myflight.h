#ifndef MYFLIGHT_H
#define MYFLIGHT_H
#include "configuration.h"
#include "NetDef.h"
#include <QObject>

class TeamFlight
{
public:
    TeamFlight();

public:
    int Id=1;

    int MyFX=300;
    int MyFY=400;
    int MyF_Life=3;
    QRect MyF_Outline;

    int MyB_Speed=0;     //我方子弹速度
    int MyB_Model_flag=1;

    int MyP_Num=1;
    int flag_UseP=0;

    int USkills_Num=1;//大招
    int flag_USkills=0;

    int Eliminate_Num=0; //杀敌数

};

#endif // MYFLIGHT_H
