#include "enemyflight.h"

EnemyFlight::EnemyFlight()
{

    EnF_Outline.setWidth(100);
    EnF_Outline.setHeight(70);
    EnF_Outline.moveTo(EnFX,EnFY);

}

void EnemyFlight::EnF_Move()
{
    EnFY+=EnFSpeed;
    if(EnF_Model==7)//精英怪
    {
        if(EnFX>550)
            flag=1;
        if(EnFX<20)
            flag=0;
        if(flag==0)
            EnFX+=EnFSpeed;
        if(flag==1)
            EnFX-=EnFSpeed;
        EnFY=0;
    }
    if(EnF_Model==8)//Boss
    {
        if(EnFY>10)
            EnFY=10;
    }
    EnF_Outline.moveTo(EnFX,EnFY);
}

