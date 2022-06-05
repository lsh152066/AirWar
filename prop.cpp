#include "prop.h"

prop::prop()
{
    Prop_Outline.setWidth(50);
    Prop_Outline.setHeight(50);
    Prop_Outline.moveTo(Prop_X,Prop_Y);
}

void prop::Prop_Move()
{
    if(Prop_X>550)
        flag_prop_move=1;
    if(Prop_X<20)
        flag_prop_move=0;
    if(flag_prop_move==0)
        Prop_X+=2;
    if(flag_prop_move==1)
        Prop_X-=2;
    Prop_Y+=2;
    Prop_Outline.moveTo(Prop_X,Prop_Y);
}
