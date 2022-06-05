#include "wight.h"
#include "ui_wight.h"
//已完成
//boss生成 限制
//boss独特攻击
//生命值显示
//道具实现（增加新的类）
//  子弹强化
//  护盾产生
//增加无敌帧
//难度递增
//  敌人生成时间缩短
//  敌人子弹频率缩短
//代码优化
//  图片加载
//  死亡判定
//武器升级（跟踪导弹）
//设置最终boss
//设置通关条件
//增加主页面
//增加大招（空格清屏）

//待做
/*
 * 道具效果衰减
 * 数据库分数记录
 * 碰撞检测优化（图片太多过于繁复 待考虑）
 */

//bug
/*
子弹错位：边遍历容器边删除容器元素 导致跳过某元素
修改方向：
std::vector<int> vecInt({ 1, 3, 2, 1, 4, 1 });
   for (auto i = vecInt.begin(); i != vecInt.end();) {
       if (*i == 1) {
           vecInt.erase(i);
       }
       else {
           ++i;
       }
   }
*/

wight::wight(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::wight)
{
    ui->setupUi(this);

    resize(600,800);
    m_painter = new QPainter(this);

    connect(&m_timer,&QTimer::timeout,this,&wight::onGameTimeout);

    connect(&CEnF_timer,&QTimer::timeout,this,&wight::Create_Enemy_Flight);

    connect(&CMyB_timer,&QTimer::timeout,this,&wight::Create_MyBullet);

    connect(&CEnB_timer,&QTimer::timeout,this,&wight::Create_EnBullet);

    connect(&CBossB_timer,&QTimer::timeout,this,&wight::Create_BossBullet);

    connect(&Difficulty_Up_timer,&QTimer::timeout,this,&wight::Difficulty_updata);

    connect(&Prop_Duration_timer,&QTimer::timeout,this,&wight::Dis_Shield);

    connect(&CMyB_M_timer,&QTimer::timeout,this,&wight::Create_MyBullet_Missile);



    //解包
//    connect(&m_socket,&QUdpSocket::readyRead,this,&wight::slotRecvData);
    connect(NetTransfrom::getInstance(),&NetTransfrom::recvData,this,&wight::procPackage);
    connect(&SendPackage_timer,&QTimer::timeout,this,&wight::sendPackage);

//    connect(&MyFlight,&TeamFlight::sendFlightPackage,this,&wight::onRecvSendPackage);

}


wight::~wight()
{
    delete ui;
}

//游戏绘画
void wight::paintEvent(QPaintEvent *event)
{   
    m_painter->begin(this);
    draw_Background();

    draw_MyFlight();
    draw_OtherFlight();
    draw_MyBullet();
    draw_EnBullet();
    draw_EnFlight();
    draw_Prop();

    m_painter->end();
    update();

}

//更新
void wight::onGameTimeout()
{
    Background.Back_Move();
    EnF_Move();
    EnB_Move();
    MyB_Move();
    Prop_Move();
    USkills_Move();

    Collision_Detection();

    sendPackage();

    //    if(flag_GameOver==0)
    //        update();
}


//碰撞检测
void wight::Collision_Detection()
{
    Collision_MyF();
    Collision_Prop();
    Collision_EnF();
}


//敌方飞机生成
void wight::Create_Enemy_Flight()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    EnemyFlight EnFlight;
    EnFlight.EnFX=qrand() % 500;
    EnFlight.EnF_Model=qrand() % 6+1;
    EnFlight.EnF_Life=qrand()%3+1+MyFlight.Eliminate_Num/33;
    if(boss_num==0&&MyFlight.Eliminate_Num>1&&MyFlight.Eliminate_Num%10==0)//boss生成
    {
        boss_num++;
        EnFlight.EnF_Model=7;
        EnFlight.EnF_Life=Boss_Life+MyFlight.Eliminate_Num/10;
        EnFlight.EnF_Outline.setWidth(120);
        EnFlight.EnF_Outline.setHeight(100);
        if((Difficulty-200)>140)
            CBossB_timer.start(Difficulty-200);
        else
            CBossB_timer.start(90);
    }

    All_EnFlight.push_back(EnFlight);

//    for(auto i:All_EnFlight)
    //              // qDebug()<<i.EnFX<<i.EnFY;
}

//Boss生成
void wight::Create_Boss()
{
    boss_num++;
    EnemyFlight EnFlight;
    EnFlight.EnFX=150;
    EnFlight.EnFY=-210;
    EnFlight.EnF_Model=8;
    EnFlight.EnF_Life=800;
    EnFlight.EnF_Outline.setWidth(280);
    EnFlight.EnF_Outline.setHeight(100);
    CBossB_timer.start(70);
    All_EnFlight.push_back(EnFlight);
}

//敌方飞机移动
void wight::EnF_Move()
{
    for(auto i=All_EnFlight.begin();i<All_EnFlight.end();i++)
    {
        i->EnF_Move();
        if(i->EnF_Model%3==0)
        {
            if(i->EnFX-MyFlight.MyFX>0)
                i->EnFX-=1;
            if(i->EnFX-MyFlight.MyFX<0)
                i->EnFX+=1;
        }
        if(i->EnFY>900)
        {
            All_EnFlight.erase(i);
            i--;
        }
    }
}

//敌方子弹生成
void wight::Create_EnBullet()
{

    for(auto i=All_EnFlight.begin();i<All_EnFlight.end();i++)
    {
        EnemyBullet EnemyB;
        if(i->EnF_Model<7)
        {
            EnemyB.EnBullet_X=i->EnFX+40;
            EnemyB.EnBullet_Y=i->EnFY+35;
            int temp=qrand()%2+1;
            if(temp==1)
                EnemyB.EnB_Model=1;
            if(temp==2)
                EnemyB.EnB_Model=3;
            Set_EnB_Outline(EnemyB,EnemyB.EnB_Model);
            All_EnBullet.push_back(EnemyB);
        }
    }
}

//Boss子弹生成
void wight::Create_BossBullet()
{
    for(auto i=All_EnFlight.begin();i<All_EnFlight.end();i++)
    {
        if(i->EnF_Model==7)//精英怪子弹生成
        {
            EnemyBullet EnemyB;
            for(int j=0;j<3;j++)
            {
                EnemyB.EnBullet_X=i->EnFX+40+j*20;
                EnemyB.EnBullet_Y=i->EnFY+50;

                EnemyB.EnB_Model=2;
                EnemyB.EnB_Speed=2;
                Set_EnB_Outline(EnemyB,EnemyB.EnB_Model);
                All_EnBullet.push_back(EnemyB);
            }
            for(int j=0;j<2;j++)
            {
                EnemyB.EnBullet_X=i->EnFX+60;
                EnemyB.EnBullet_Y=i->EnFY+50;

                EnemyB.EnB_Model=4+j;
                EnemyB.EnB_Speed=2;
                Set_EnB_Outline(EnemyB,EnemyB.EnB_Model);
                All_EnBullet.push_back(EnemyB);
            }
        }
        if(i->EnF_Model==8)//Boss子弹生成
        {
            EnemyBullet EnemyB;
            for(int j=0;j<3;j++)
            {
                EnemyB.EnBullet_X=i->EnFX+120+j*20;
                EnemyB.EnBullet_Y=i->EnFY+200;

                EnemyB.EnB_Model=2;
                EnemyB.EnB_Speed=2;
                Set_EnB_Outline(EnemyB,EnemyB.EnB_Model);
                All_EnBullet.push_back(EnemyB);
            }
            for(int j=0;j<2;j++)
            {
                EnemyB.EnBullet_X=i->EnFX+140;
                EnemyB.EnBullet_Y=i->EnFY+100;

                EnemyB.EnB_Model=4+j;
                EnemyB.EnB_Speed=2;
                Set_EnB_Outline(EnemyB,EnemyB.EnB_Model);
                All_EnBullet.push_back(EnemyB);
           }
        }
    }
}

//敌方所有子弹移动
void wight::EnB_Move()
{
    for(auto i=All_EnBullet.begin();i<All_EnBullet.end();)
    {
        i->EnBullet_Y+=i->EnB_Speed;
        i->EnB_Move();
        if(i->EnBullet_Y>800)
            All_EnBullet.erase(i);
        else
            i++;
    }
}

//我方子弹生成
void wight::Create_MyBullet()
{
    MyBullet Mybullet;

    Mybullet.MyBullet_X=MyFlight.MyFX+40;
    Mybullet.MyBullet_Y=MyFlight.MyFY;

    Mybullet.MyB_Model=1;
    Mybullet.MyB_Hurt=1;

    All_MyBullet.push_back(Mybullet);
}
//我方导弹生成
void wight::Create_MyBullet_Missile()
{
    if(MyFlight.MyB_Model_flag>0)
    {
        MyBullet Mybullet_Missile;
        Mybullet_Missile.MyB_Model=2;
        Mybullet_Missile.MyB_Hurt=5;
        Mybullet_Missile.MyBullet_X=MyFlight.MyFX;
        Mybullet_Missile.MyBullet_Y=MyFlight.MyFY;

        All_MyBullet.push_back(Mybullet_Missile);

        Mybullet_Missile.MyBullet_X=MyFlight.MyFX+80;

        All_MyBullet.push_back(Mybullet_Missile);
    }
}

//我方所有子弹移动
void wight::MyB_Move()
{
    for(auto i=All_MyBullet.begin();i<All_MyBullet.end();)
    {
        if(i->MyB_Model!=2)
            i->MyBullet_Y-=MyFlight.MyB_Speed;
        i->MyB_Move();
        if(i->MyB_Model==2)
        {
            if(!All_EnFlight.empty()&&All_EnFlight.front().EnFX-i->MyBullet_X+90<0)
                i->MyBullet_X-=2;
            if(!All_EnFlight.empty()&&All_EnFlight.front().EnFX-i->MyBullet_X+90>0)
                i->MyBullet_X+=2;
        }
        if(i->MyBullet_Y<-50)
            All_MyBullet.erase(i);
        else
            i++;
    }
}

//我方飞机移动
void wight::mouseMoveEvent(QMouseEvent *event)
{
    MyFlight.MyFX=event->x()-50;
    MyFlight.MyFY=event->y()-35;
    if(MyFlight.MyFX>550)
        MyFlight.MyFX=550;
    if(MyFlight.MyFX<-50)
        MyFlight.MyFX=-50;
    if(MyFlight.MyFY>750)
        MyFlight.MyFY=750;
    if(MyFlight.MyFY<100)
        MyFlight.MyFY=100;
    MyFlight.MyF_Outline.moveTo(MyFlight.MyFX,MyFlight.MyFY);
}


//道具生成
void wight::Create_Prop()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    Prop_num=qrand() %Prop_Model+1;
    Prop_num=4;
  // qDebug()<<"开始生成道具"<<Prop_num;
//    QTime startTime = QTime::currentTime() ;
    prop Prop;
//  // qDebug()<<startTime.msecsTo(QTime::currentTime())<<"end-----------------------";
    while(Prop_num--)
    {
        Prop.Prop_X=qrand() % 500;
        Prop.flag_prop_modle=qrand() % Prop_Model+1;
      // qDebug()<<"生成道具"<<Prop.flag_prop_modle;
        All_Prop.push_back(Prop);
    }
}

//道具移动
void wight::Prop_Move()
{
    for(auto i=All_Prop.begin();i<All_Prop.end();)
    {
        i->Prop_Move();
        if(i->Prop_Y>800)
            All_Prop.erase(i);
        else
            i++;
    }
}

//道具使用
void wight::keyPressEvent(QKeyEvent *event)
{
    //护盾
    if(event->key()==Qt::Key_F&&MyFlight.MyP_Num>0)
    {
        MyFlight.MyP_Num--;
        MyFlight.flag_UseP=1;

        //道具持续十秒
        Prop_Duration_timer.start(MyPress_Duration);
      // qDebug()<<"道具已使用";
    }
  // qDebug()<<"道具剩余:"<<MyFlight.MyP_Num;

    //大招
    if(event->key()==Qt::Key_Space&&MyFlight.USkills_Num>0)
    {
        USkills_Y=900;
        MyFlight.flag_USkills=1;
        if(!All_EnBullet.empty())
        {
            All_EnBullet.clear();
        }
        for(auto &i:All_EnFlight)
        {
            i.EnF_Life-=50;
        }
    }
}

void wight::USkills_Move()
{
    if(MyFlight.flag_USkills==1)//大招使用
    {
        USkills_Y-=30;
        if(USkills_Y<-600)
        {
            MyFlight.flag_USkills=0;
        }
    }
}


void wight::Dis_Shield()
{
    MyFlight.flag_UseP=0;
    Prop_Duration_timer.stop();
}


//难度更新
void wight::Difficulty_updata()
{
    if(Difficulty>Max_Difficulty)
    {
        Difficulty=Interval_EnB-MyFlight.Eliminate_Num;
        CEnB_timer.stop();
        CEnB_timer.start(Difficulty);
        CEnF_timer.stop();
        CEnF_timer.start(Difficulty);
    }
    else
    {
        CEnB_timer.stop();
        CEnB_timer.start(Max_Difficulty);
        Difficulty_Up_timer.stop();
    }
  // qDebug()<<"难度更新"<<Difficulty;
}


//敌机碰撞检测
void wight::Collision_EnF()
{
    if(!All_EnFlight.empty()&&!All_MyBullet.empty())
    {
        for(auto j=All_MyBullet.begin();flag_GameOver==0&&j<All_MyBullet.end();j++)
        {
            for(auto i=All_EnFlight.begin();flag_GameOver==0&&i<All_EnFlight.end()&&!All_EnFlight.empty();i++)
            {
                //造成伤害
                if(i->EnF_Outline.intersects(j->MyB_Outline))
                {
                    All_MyBullet.erase(j);
                    i->EnF_Life-=j->MyB_Hurt;
                }
                //死亡
                if(i->EnF_Life<=0)
                {
                    if(i->EnF_Model==7)
                    {
                        boss_num--;
                        CBossB_timer.stop();
                        MyFlight.Eliminate_Num+=9;
                        Create_Prop();
                    }
                    if(i->EnF_Model==8)
                    {
                        MyFlight.Eliminate_Num+=1000;
                        m_timer.stop();
                        GameOver();
                        break;
                    }
                    All_EnFlight.erase(i);
                    i--;
                    MyFlight.Eliminate_Num++;
                }
                if(MyFlight.Eliminate_Num>CBoss_Score)//boss战斗
                {
                    CEnF_timer.stop();
                    CEnB_timer.stop();
                    if(boss_num==0)
                        Create_Boss();
                }
            }
        }
    }
}

//我方碰撞检测
void wight::Collision_MyF()
{
    if(!All_EnBullet.empty())
    {
        for(auto i=All_EnBullet.begin();i<All_EnBullet.end();)
        {
            if(i->EnB_Outline.intersects(MyFlight.MyF_Outline))
            {
                All_EnBullet.erase(i);
//              // qDebug()<<"收到伤害";
                if(MyFlight.MyF_Life>1&&MyFlight.flag_UseP==0)
                {

                    MyFlight.MyF_Life--;
                    //扣血后3秒无敌
                    MyFlight.flag_UseP=1;
                    Prop_Duration_timer.start(3000);
                }
                if(MyFlight.MyF_Life<=0)
                {
                    m_timer.stop();
                    GameOver();
                }
            }
            else
                i++;
        }
    }
    if(!All_EnFlight.empty())
    {
        for(auto i=All_EnFlight.begin();i<All_EnFlight.end();)
        {
            if(i->EnF_Outline.intersects(MyFlight.MyF_Outline))
            {
                All_EnFlight.erase(i);
//              // qDebug()<<"收到伤害";
                if(MyFlight.MyF_Life>1&&MyFlight.flag_UseP==0)
                {
                    MyFlight.MyF_Life--;
                    //扣血后3秒无敌
                    MyFlight.flag_UseP=1;
                    Prop_Duration_timer.start(3000);

                }
//                m_timer.stop();
//                QMessageBox::information(this,"提示","游戏结束");
            }
            else
                i++;
        }
    }
}

//道具碰撞检测
void wight::Collision_Prop()
{
    if(!All_Prop.empty())
    {
        for(auto i=All_Prop.begin();i<All_Prop.end();i++)
        {
            if(i->Prop_Outline.intersects(MyFlight.MyF_Outline))
            {
                if(i->flag_prop_modle==1&&MyFlight.MyF_Life<=Max_MyLife)//加血
                {
                  // qDebug()<<"生命增加";
                    MyFlight.MyF_Life++;
                }
                if(i->flag_prop_modle==2)//加攻速
                {
                  // qDebug()<<"子弹升级";
                    interval_MyB=interval_MyB-140;
                    if(interval_MyB>=Min_Myb_interval)
                        CMyB_timer.start(interval_MyB);
                    if(MyFlight.MyB_Speed<=Max_MyB_Speed)
                        MyFlight.MyB_Speed+=2;
                }
                if(i->flag_prop_modle==3)
                {
                  // qDebug()<<"道具加一";
                    MyFlight.MyP_Num++;
                }
                if(i->flag_prop_modle==4)
                {
                    CMyB_M_timer.stop();
                  // qDebug()<<"获取导弹";
                    MyFlight.MyB_Model_flag++;
                    CMyB_M_timer.start(1000-MyFlight.MyB_Model_flag*100);
                    if(MyFlight.MyB_Model_flag>5)
                    {
                        CMyB_M_timer.stop();
                        CMyB_M_timer.start(500);
                    }
                }
                All_Prop.erase(i);
            }
        }
    }
}


////碰撞检测精细化
//bool wight::isRectTransparency(const QRect &rect, const QImage &img)
//{
//    //目前只需要判断矩形框在img相对位置的左上，左下，右上，右下四个点的透明度
//    //如果每个像素点都判断，计算量很大
//   return img.pixelColor(rect.topLeft()).alpha() >0
//            || img.pixelColor(rect.topRight()).alpha() >0
//            || img.pixelColor(rect.bottomLeft()).alpha() >0
//            || img.pixelColor(rect.bottomRight()).alpha() >0;
//}

//bool wight::isPixelCrash(const QRect &r1, const QImage &img1, const QRect &r2, const QImage &img2)
//{
//    //矩形框是否相交
//    if(!r1.intersects(r2))
//        return false;
//    //获取相交的区域
//    QRect collRect = r1.intersected(r2);

//    //判断img 对相交区域是否存在像素相交
//    //求出相交矩形框对图片的相对位置
//    QRect img1Rect = QRect(collRect.x() - r1.x(),collRect.y() - r1.y(),
//                           collRect.width(),collRect.height());
//    QRect img2Rect = QRect(collRect.x() - r2.x(),collRect.y() - r2.y(),
//                           collRect.width(),collRect.height());
//    return isRectTransparency(img1Rect,img1)&&isRectTransparency(img2Rect,img2);
//}


//背景绘制
void wight::draw_Background()
{
    m_painter->drawImage(0,Background.m_currentY-800,P.m_background);
    m_painter->drawImage(0,Background.m_currentY,P.m_background);
   // qDebug()<<"绘画地图Y:"<<Background.m_currentY;

    QRectF rect(0, 200, 100, 55);
    m_painter->drawRect(rect);
    QFont font = m_painter->font();
    font.setPixelSize(20);
    m_painter->setFont(font);
    m_painter->drawText(rect, Qt::AlignHCenter, "技能(F):"+QString::number(MyFlight.MyP_Num)
                                                +"\n分数:"+QString::number(MyFlight.Eliminate_Num));

    //生命值显示
    for(int i=0;i<MyFlight.MyF_Life;i++)
    {
        m_painter->drawImage(i*30,10,P.m_lift);
    }
}

//我方战机绘制
void wight::draw_MyFlight()
{
    m_painter->drawImage(MyFlight.MyFX,MyFlight.MyFY,P.m_MyFlight);
}

void wight::draw_OtherFlight()
{
    if(!OtherFlight.empty())
        for(auto i=OtherFlight.begin();i<OtherFlight.end();i++)
            m_painter->drawImage(i->MyFX,i->MyFY,P.m_MyFlight);

}


//我方子弹绘制
void wight::draw_MyBullet()
{
    for(auto i:All_MyBullet)
        switch (i.MyB_Model)
        {
            case 1:
                m_painter->drawImage(i.MyBullet_X,i.MyBullet_Y,P.m_MyBullet);
                break;
            case 2:
                m_painter->drawImage(i.MyBullet_X,i.MyBullet_Y,P.m_MyB_Missile);
                break;
        }


}

//敌方战机绘制
void wight::draw_EnFlight()
{
    for(auto i:All_EnFlight)
    {
        switch (i.EnF_Model)
        {
            case 1:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_1);
                break;
            case 2:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_2);
                break;
            case 3:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_3);
                break;
            case 4:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_4);
                break;
            case 5:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_5);
                break;
            case 6:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_6);
                break;
            case 7:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_EnFlight_7);
                break;
            case 8:
                m_painter->drawImage(i.EnFX,i.EnFY,P.m_Boss);
                break;
         }
    }
//    if(!All_EnFlight.empty())
//    {
//        //qDebug()<<"开始绘画敌机";
//        for(auto i=All_EnFlight.begin();i<All_EnFlight.end();i++)
//        {
//            switch (i->EnF_Model)
//            {
//            case 1:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_1);
//                break;
//            case 2:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_2);
//                break;
//            case 3:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_3);
//                break;
//            case 4:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_4);
//                break;
//            case 5:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_5);
//                break;
//            case 6:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_6);
//                break;
//            case 7:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_EnFlight_7);
//                break;
//            case 8:
//                m_painter->drawImage(i->EnFX,i->EnFY,P.m_Boss);
//                break;
//            }
//        }
//    }
}

//敌方子弹绘制
void wight::draw_EnBullet()
{
    for(auto i:All_EnBullet)
    {
        switch (i.EnB_Model)
        {
            case 1:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_1);
                break;
            case 2:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_2);
                break;
            case 3:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_3);
                break;
            case 4:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_4);
                break;
            case 5:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_5);
                break;
            case 6:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_6);
                break;
            case 7:
                m_painter->drawImage(i.EnBullet_X,i.EnBullet_Y,P.m_EnBullet_7);
                break;
        }
    }
}

//道具绘制
void wight::draw_Prop()
{

    for(auto i:All_Prop)
    {
        switch (i.flag_prop_modle)
        {
            case 1://增加生命
                m_painter->drawImage(i.Prop_X,i.Prop_Y,P.m_Life_UP);
                break;
            case 2://子弹加速
                m_painter->drawImage(i.Prop_X,i.Prop_Y,P.m_Bullet_UP);
                break;
            case 3://护盾
                m_painter->drawImage(i.Prop_X,i.Prop_Y,P.m_Shield);
                break;
            case 4://飞弹
                m_painter->drawImage(i.Prop_X,i.Prop_Y,P.m_Missile);
                break;
        }
    }

    if(MyFlight.flag_UseP==1)//护盾使用
    {
        m_painter->drawImage(MyFlight.MyFX-5,MyFlight.MyFY-20,P.m_Shield2);
    }
    if(MyFlight.flag_USkills==1)//大招使用
        m_painter->drawImage(0,USkills_Y,P.m_Clear);
}


void wight::Set_EnB_Outline(EnemyBullet& EnB,int EnB_Model)
{
    switch(EnB_Model)
    {
        case 1:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_1.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_1.height());
            break;
        }
        case 2:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_2.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_2.height());
            break;
        }
        case 3:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_3.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_3.height());
            break;
        }
        case 4:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_4.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_4.height());
            break;
        }
        case 5:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_5.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_5.height());
            break;
        }
        case 6:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_6.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_6.height());
            break;
        }
        case 7:
        {
            EnB.EnB_Outline.setWidth(P.m_EnBullet_7.width());
            EnB.EnB_Outline.setHeight(P.m_EnBullet_7.height());
            break;
        }
    }
}

void wight::GameStart_single()
{
    Difficulty=Interval_EnB;
    m_timer.start(Frame);
    CMyB_timer.start(Interval_MyB);
    CEnF_timer.start(Interval_EnF);
    CEnB_timer.start(Interval_EnB);
    Difficulty_Up_timer.start(10000);//十秒更新一次难度
}

void wight::GameStart_doubule()
{
    Difficulty=Interval_EnB;
    m_timer.start(Frame);
    CMyB_timer.start(Interval_MyB);
    CEnF_timer.start(Interval_EnF);
    CEnB_timer.start(Interval_EnB);
    Difficulty_Up_timer.start(10000);//十秒更新一次难度
//    SendPackage_timer.start(Frame);//发送游戏数据频率

    OtherFlight.clear();
    TeamFlight P2_Flight;
    P2_Flight.Id=2;
    OtherFlight.push_back(P2_Flight);

    //主机才会处理发送游戏更新数据包的信号
//    connect(&MyFlight,&TeamFlight::sendFlightPackage,this,&wight::onRecvSendPackage);
//    connect(this,&wight::sendGameUpdatePackage,this,&wight::Send_GameUpdatePackage);
}



void wight::GameOver()
{

    m_timer.stop();
    CMyB_M_timer.stop();
    CEnF_timer.stop();
    CMyB_timer.stop();
    CEnB_timer.stop();
    Difficulty_Up_timer.stop();

    flag_GameOver=1;

    QString dlgTitle="游戏结束";
    QString txtLabel=QString("得分:%1").arg(MyFlight.Eliminate_Num);
    QString defaultInput="请输入用户名";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
    //QLineEdit::EchoMode echoMode=QLineEdit::Password;//密码输入
    bool ok=false;
    QString text = QInputDialog::getText(this, dlgTitle,txtLabel, echoMode,defaultInput, &ok);
    if (ok && !text.isEmpty())
    {
        //qDebug() << "开始插入";
        QString str=QString("insert into rank values('%1',%2)").arg(text).arg(MyFlight.Eliminate_Num);
        sql.exec(str);
       // qDebug()<<"开始完成";
//        this->hide();
        emit return_MainW(this);
    }
}


void wight::procPackage(const char *data, int len)
{
    qDebug()<<"游戏界面收到数据包";
    if(len<sizeof(HeadPackage))
        return;
    HeadPackage *head=(HeadPackage*)data;
    qDebug()<<"开始分拣";
    switch (head->type) {
        case PackageType::start:
            procStartPackage(data,len);
            break;
        case PackageType::flight:
            procFlightPackage(data,len);
            break;
        case PackageType::update:
            procUpdatePackage(data,len);
            break;
        default:
            break;
    }
    qDebug()<<"处理完成";
}

void wight::procStartPackage(const char *data, int len)
{
    if(len<sizeof(startPackage))
        return;
    startPackage start(PackageType::start,sizeof(startPackage));
    memcpy(&start,data,len);
    //初始化的东西
    //startgame(start.id)

}

void wight::procFlightPackage(const char *data, int len)
{
    qDebug()<<"收到一个飞机包";
    if(len<sizeof(flightPackage))
        return;
    flightPackage flight(PackageType::flight,sizeof(flightPackage));
    memcpy(&flight,data,len);

    if(OtherFlight.empty())
        qDebug()<<"容器为空";
   // qDebug()<<OtherFlight.back().Id;
    for(auto i=OtherFlight.begin();i<OtherFlight.end();i++)
    {
        qDebug()<<"MyFlightID:"<<MyFlight.Id;
        qDebug()<<"Other:"<<i->Id;
        qDebug()<<"包的id:"<<flight.id;
        if(i->Id==flight.id)
        {
            i->MyFX=flight.x;
            i->MyFY=flight.y;
        }
    }
}

void wight::procUpdatePackage(const char *data, int len)
{
    qDebug()<<"收到一个更新包";
    if(len<sizeof(gameupdatePackage))
        return;
    qDebug()<<"是正确的包";
    gameupdatePackage update(PackageType::update,sizeof(gameupdatePackage));
    memcpy(&update,data,len);
    qDebug()<<"拷贝成功";
    Background.m_currentY=update.Background_Y;
    qDebug()<<"赋值成功";
    qDebug()<<"地图Y"<<Background.m_currentY;
}

void wight::sendPackage()
{
    flightPackage stateP(PackageType::flight,sizeof(flightPackage));
    stateP.id=MyFlight.Id;
    stateP.x=MyFlight.MyFX;
    stateP.y=MyFlight.MyFY;
//        stateP->life=MyFlight.MyF_Life;
//        stateP->MyB_Speed=MyFlight.MyB_Speed;
//        stateP->MyP_Num=MyFlight.MyP_Num;
//        stateP->flag_UseP=MyFlight.flag_UseP;
    NetTransfrom::getInstance()->write((char*)(&stateP),stateP.len);
    if(MyFlight.Id==1)//等于主机   发送信息包
    {
        //游戏进程的各种
//       // qDebug()<<"发送游戏更新包";
        gameupdatePackage gameP(PackageType::update,sizeof(gameupdatePackage));
        gameP.Background_Y=Background.m_currentY;
        NetTransfrom::getInstance()->write((char*)(&gameP),gameP.len);
    }
}



