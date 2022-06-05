#ifndef PROP_H
#define PROP_H
#include "configuration.h"

class prop
{
public:
    prop();
    void Prop_Move();

public:

    int Prop_X;
    int Prop_Y = -150;



    int flag_prop_move=0;
    int flag_prop_modle;
    QRect Prop_Outline;
};

#endif // PROP_H
