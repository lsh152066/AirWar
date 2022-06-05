#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "configuration.h"

class Background
{
public:
    Background();

public slots:
    void Back_Move();

public:
    int m_currentY = 0;
    int m_BSpeed = 3;

};

#endif // BACKGROUND_H
