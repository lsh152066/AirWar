#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QImage>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>
#include <QKeyEvent>
#include <QRect>
#include<qDebug>
#include <QSharedPointer>

#define  Frame              16    //帧率 1000/Frame
#define  Interval_EnF       1000  //敌人生成初始间隔
#define  EnFSpeed           2     //敌人移动速度
#define  Interval_MyB       500   //我方子弹生成间隔
#define  MyBSpeed           3     //我方子弹速度
#define  Interval_EnB       1000  //敌人子弹生成初始间隔
#define  EnBSpeed           6     //敌人子弹生成初始速度
#define  Boss_Life          10    //Boss初始生命值
#define  Prop_Model         4     //道具种类
#define  Max_MyLife         5     //我方最大生命值
#define  Max_MyB_Speed      5     //我方子弹最快速度
#define  Min_Myb_interval   20    //我方子弹最小发射间隔
#define  MyPress_Duration   10000  //护盾持续时间
#define  Max_Difficulty     330   //最大难度
#define  CBoss_Score        11   //生成boss分数

class configuration
{
public:
    configuration();

    QImage m_mainwight;
    QImage m_background;

    QImage m_Boom_1;
    QImage m_Boom_2;
    QImage m_Boom_3;
    QImage m_Boom_4;
    QImage m_Boom_5;
    QImage m_Boom_6;
    QImage m_Boom_7;
    QImage m_Clear;

    QImage m_EnBullet_1;
    QImage m_EnBullet_2;
    QImage m_EnBullet_3;
    QImage m_EnBullet_4;
    QImage m_EnBullet_5;
    QImage m_EnBullet_6;
    QImage m_EnBullet_7;

    QImage m_EnFlight_1;
    QImage m_EnFlight_2;
    QImage m_EnFlight_3;
    QImage m_EnFlight_4;
    QImage m_EnFlight_5;
    QImage m_EnFlight_6;
    QImage m_EnFlight_7;
    QImage m_Boss;

    QImage m_MyBullet;
    QImage m_MyB_Missile;

    QImage m_MyFlight;
    QImage m_lift;
    QImage m_Shield2;

    QImage m_Life_UP;
    QImage m_Bullet_UP;
    QImage m_Shield;
    QImage m_Missile;

};

#endif // CONFIGURATION_H
