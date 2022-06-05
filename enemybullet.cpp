#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{


}

void EnemyBullet::EnB_Move()
{
    EnBullet_Y+=EnBSpeed;//子弹初始速度
    if(EnB_Model==4)
        EnBullet_X-=EnBSpeed;
    if(EnB_Model==5)
        EnBullet_X+=EnBSpeed;
    EnB_Outline.moveTo(EnBullet_X,EnBullet_Y);

}

