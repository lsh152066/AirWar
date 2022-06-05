#ifndef WIGHT_H
#define WIGHT_H

#include <QWidget>
#include <QLineEdit>
#include <QInputDialog>
#include <QSqlQuery>
#include "configuration.h"
#include "background.h"
#include "myflight.h"
#include "mybullet.h"
#include "enemyflight.h"
#include "enemybullet.h"
#include "prop.h"
#include "single_sql.h"
#include "NetDef.h"
#include "nettransfrom.h"
QT_BEGIN_NAMESPACE
namespace Ui { class wight; }
QT_END_NAMESPACE

class wight : public QWidget
{
    Q_OBJECT

public:
    wight(QWidget *parent = nullptr);
    ~wight();

    void paintEvent(QPaintEvent *event) ;
    void draw_Background();
    void draw_MyFlight();
    void draw_OtherFlight();
    void draw_MyBullet();
    void draw_EnFlight();
    void draw_EnBullet();
    void draw_Prop();
    void mouseMoveEvent(QMouseEvent *event);

    void Create_MyBullet();
    void Create_MyBullet_Missile();
    void MyB_Move();

    void Create_Enemy_Flight();
    void Create_Boss();
    void EnF_Move();

    void Create_EnBullet();
    void Create_BossBullet();
    void EnB_Move();
    void Set_EnB_Outline(EnemyBullet&,int);

    void Create_Prop();
    void Prop_Move();
    void keyPressEvent(QKeyEvent *event);
    void Dis_Shield();
    void USkills_Move();

    void Difficulty_updata();

    //碰撞检测
    void Collision_Detection();
    void Collision_EnF();
    void Collision_MyF();
    void Collision_Prop();
//碰撞检测精细化
//    bool isRectTransparency(const QRect& rect,const QImage& img);
//    bool isPixelCrash(const QRect& r1,const QImage& img1,const QRect& r2,const QImage& img2);


    void GameStart_single();
    void GameStart_doubule();
    void GameOver();


private slots:
    void onGameTimeout();

signals:
    void return_MainW(wight*);
    void sendGameUpdatePackage(std::shared_ptr<gameupdatePackage> package);

public:
    Ui::wight *ui;
    QPainter * m_painter = nullptr;

    QSqlQuery sql=QSqlQuery(single_sql::GetDb()->db);

    Background Background;
    QTimer m_timer;
    QTimer Difficulty_Up_timer;
    int Difficulty=Interval_EnB;
    configuration P;
    int USkills_Y=900;
    int flag_GameOver=0;
    QTimer SendPackage_timer;


    TeamFlight MyFlight;
    QVector<TeamFlight>OtherFlight;
    int interval_MyB=Interval_MyB;
    QTimer CMyB_timer;
    QTimer CMyB_M_timer;
    QVector<MyBullet>All_MyBullet;

    QVector<EnemyFlight>All_EnFlight;
    QTimer CEnF_timer;
    QTimer CBossB_timer;

    QVector<EnemyBullet>All_EnBullet;
    QTimer CEnB_timer;
    int boss_num=0;

    QVector<prop>All_Prop;
    int Prop_num;
    QTimer Prop_Duration_timer;


private:
    void procPackage(const char* data,int len);
    void procStartPackage(const char* data,int len);
    void procFlightPackage(const char* data,int len);
    void procUpdatePackage(const char* data,int len);
    void sendPackage();


};
#endif // WIGHT_H
