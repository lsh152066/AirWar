#include "mybullet.h"

MyBullet::MyBullet()
{

    MyB_Outline.setWidth(20);
    MyB_Outline.setHeight(40);
    MyB_Outline.moveTo(MyBullet_X,MyBullet_Y);
}

void MyBullet::MyB_Move()
{
    MyBullet_Y-=MyBSpeed;
    if(MyB_Model==2)//导弹额外飞行速度
        MyBullet_Y-=1;
    MyB_Outline.moveTo(MyBullet_X,MyBullet_Y);
}
