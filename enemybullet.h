#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "configuration.h"

class EnemyBullet
{
public:
    EnemyBullet();
    void EnB_Move();
public:
    int EnBullet_X;
    int EnBullet_Y;

    int EnB_Speed=0;//额外速度

    int EnB_Model;
    QRect EnB_Outline;
};

#endif // ENEMYBULLET_H
