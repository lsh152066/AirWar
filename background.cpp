#include "background.h"

Background::Background()
{

}

void Background::Back_Move()
{
    m_currentY += m_BSpeed;
    if(m_currentY>=800)
        m_currentY = 0;
}
