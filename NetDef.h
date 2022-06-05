#ifndef NETDEF_H
#define NETDEF_H
#pragma pack(1)

#include<QUdpSocket>
#include <QSharedPointer>
#include "mybullet.h"
#include "enemyflight.h"
#include "enemybullet.h"
#include "prop.h"

enum class PackageType:int
{
    start=1,
    flight=2,
    update=3
    //包的类型
};

struct HeadPackage{
    PackageType type;
    int len;

    HeadPackage(PackageType ty,int len)
    {
        type=ty;
        this->len=len;
    }

    HeadPackage(){};
};


//开始游戏的信号
struct startPackage:public HeadPackage
{
    int flag;

    startPackage(PackageType ty,int len)
        :HeadPackage(ty,len)
    {

    }
};

struct flightPackage:public HeadPackage
{
    int id;
    int x,y;
//    int life;
//    int MyB_Speed;
//    int MyP_Num;
//    int flag_UseP;
//    int USkills_Num;//大招
//    int flag_USkills=0;


    flightPackage(PackageType ty,int len)
        :HeadPackage(ty,len)
    {

    }
    flightPackage()=default;
};

struct gameupdatePackage:public HeadPackage
{

    int Background_Y;

//    QVector<MyBullet>All_MyBullet;
//    QVector<EnemyFlight>All_EnFlight;
//    QVector<EnemyBullet>All_EnBullet;
//    QVector<prop>All_Prop;


    gameupdatePackage(PackageType ty,int len)
        :HeadPackage(ty,len)
    {

    }
};





#endif // NETDEF_H

