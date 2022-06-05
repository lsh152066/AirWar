#include "configuration.h"
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QImage>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>
#include <QKeyEvent>
configuration::configuration()
{
    m_mainwight.load(":/new/Background/Air/res/Background/img_bg_level_2.jpg");
    m_mainwight = m_mainwight.scaled(600,800,Qt::IgnoreAspectRatio);

    //地图
    m_background.load(":/new/Background/Air/res/Background/img_bg_level_1.jpg");
    m_background = m_background.scaled(600,800,Qt::IgnoreAspectRatio);

    m_Boom_1.load(":/new/Boom/Air/res/Boom/bomb-1.png");
    m_Boom_2.load(":/new/Boom/Air/res/Boom/bomb-2.png");
    m_Boom_3.load(":/new/Boom/Air/res/Boom/bomb-3.png");
    m_Boom_4.load(":/new/Boom/Air/res/Boom/bomb-4.png");
    m_Boom_5.load(":/new/Boom/Air/res/Boom/bomb-5.png");
    m_Boom_6.load(":/new/Boom/Air/res/Boom/bomb-6.png");
    m_Boom_7.load(":/new/Boom/Air/res/Boom/bomb-7.png");
    m_Clear.load(":/new/Boom/Air/res/Boom/clear.png");
    m_Clear = m_Clear.scaled(600,600,Qt::IgnoreAspectRatio);

    //敌人子弹
    m_EnBullet_1.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_1.png");
    m_EnBullet_1=m_EnBullet_1.scaled(20,30,Qt::IgnoreAspectRatio);
    m_EnBullet_2.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_2.png");
    m_EnBullet_2=m_EnBullet_2.scaled(20,70,Qt::IgnoreAspectRatio);
    m_EnBullet_3.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_3.png");
    m_EnBullet_3=m_EnBullet_3.scaled(20,40,Qt::IgnoreAspectRatio);
    m_EnBullet_4.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_4.png");
    m_EnBullet_4=m_EnBullet_4.scaled(20,30,Qt::IgnoreAspectRatio);
    m_EnBullet_5.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_5.png");
    m_EnBullet_5=m_EnBullet_5.scaled(20,30,Qt::IgnoreAspectRatio);
    m_EnBullet_6.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_6.png");
    m_EnBullet_6=m_EnBullet_6.scaled(20,56,Qt::IgnoreAspectRatio);
    m_EnBullet_7.load(":/new/EnemyBullet/Air/res/EnemyBullet/bullet_7.png");
    m_EnBullet_7=m_EnBullet_7.scaled(20,70,Qt::IgnoreAspectRatio);

    //敌人飞机
    m_EnFlight_1.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_1.png");
    m_EnFlight_1=m_EnFlight_1.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_2.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_2.png");
    m_EnFlight_2=m_EnFlight_2.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_3.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_3.png");
    m_EnFlight_3=m_EnFlight_3.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_4.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_4.png");
    m_EnFlight_4=m_EnFlight_4.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_5.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_5.png");
    m_EnFlight_5=m_EnFlight_5.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_6.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_6.png");
    m_EnFlight_6=m_EnFlight_6.scaled(100,70,Qt::IgnoreAspectRatio);
    m_EnFlight_7.load(":/new/EnemyFlight/Air/res/EnemyFlight/img-plane_7.png");
    m_EnFlight_7=m_EnFlight_7.scaled(150,100,Qt::IgnoreAspectRatio);
    m_Boss.load(":/new/EnemyFlight/Air/res/EnemyFlight/boss.png");
    m_Boss=m_Boss.scaled(300,220,Qt::IgnoreAspectRatio);

    //我方子弹
    m_MyBullet.load(":/new/MyBullet/Air/res/MyBullet/bullet_11.png");
    m_MyBullet=m_MyBullet.scaled(20,40,Qt::IgnoreAspectRatio);
    m_MyB_Missile.load(":/new/MyBullet/Air/res/MyBullet/bullet_8.png");
    m_MyB_Missile=m_MyB_Missile.scaled(20,60,Qt::IgnoreAspectRatio);

    //我方飞机
    m_MyFlight.load(":/new/MyFlight/Air/res/MyFlight/hero.png");
    m_MyFlight=m_MyFlight.scaled(100,70,Qt::IgnoreAspectRatio);
    m_lift.load(":/new/MyFlight/Air/res/MyFlight/life.png");
    m_lift=m_lift.scaled(30,30,Qt::IgnoreAspectRatio);
    m_Shield2.load(":/new/prop/Air/res/prop/shield.png");
    m_Shield2=m_Shield2.scaled(110,110,Qt::IgnoreAspectRatio);

    //道具
    m_Life_UP.load(":/new/prop/Air/res/prop/life_UP.png");
    m_Life_UP=m_Life_UP.scaled(50,50,Qt::IgnoreAspectRatio);
    m_Bullet_UP.load(":/new/prop/Air/res/prop/bullet_UP.png");
    m_Bullet_UP=m_Bullet_UP.scaled(50,50,Qt::IgnoreAspectRatio);
    m_Shield.load(":/new/prop/Air/res/prop/shield.png");
    m_Shield=m_Shield.scaled(50,50,Qt::IgnoreAspectRatio);
    m_Missile.load(":/new/prop/Air/res/prop/feidan.png");
    m_Missile=m_Missile.scaled(20,70,Qt::IgnoreAspectRatio);
}
