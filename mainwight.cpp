#include "mainwight.h"
#include "ui_mainwight.h"

MainWight::MainWight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWight)
{
    ui->setupUi(this);
    resize(600,800);
    m_painter = new QPainter(this);
//    udpSocket = new QUdpSocket(this);

    ui->label->hide();
    ui->lineEdit->hide();
    ui->pushButton_Gamestart->hide();
    ui->pushButton_CreateRoom->hide();
    ui->pushButton_JoinRoom->hide();
    ui->pushButton_return->hide();

    connect(ui->pushButton_single,&QPushButton::clicked,this,&MainWight::pushButton_single_clicked);
    connect(ui->pushButton_double,&QPushButton::clicked,this,&MainWight::pushButton_double_clicked);
    connect(ui->pushButton_rank,&QPushButton::clicked,this,&MainWight::pushButton_rank_clicked);
    connect(ui->pushButton_CreateRoom,&QPushButton::clicked,this,&MainWight::on_pushButton_CreateRoom_clicked);
    connect(ui->pushButton_JoinRoom,&QPushButton::clicked,this,&MainWight::on_pushButton_JoinRoom_clicked);
    connect(ui->pushButton_Gamestart,&QPushButton::clicked,this,&MainWight::on_pushButton_start_clicked);
    connect(ui->pushButton_return,&QPushButton::clicked,this,&MainWight::on_pushButton_return_clicked);
    connect(&r,&rank::return_MainW,this,&MainWight::pushButton_return_clicked);
    connect(NetTransfrom::getInstance(),&NetTransfrom::recvData,this,&MainWight::dealmsg);

}

MainWight::~MainWight()
{
    delete ui;
}

void MainWight::paintEvent(QPaintEvent *event)
{
    m_painter->begin(this);
    m_painter->drawImage(0,0,P.m_mainwight);

    m_painter->end();

}



//单人模式
void MainWight::pushButton_single_clicked()
{
    wight *w=new wight();
    w->GameStart_single();
    this->hide();
    w->show();
    connect(w,&wight::return_MainW,this,&MainWight::GameOver);
}

//联机模式
void MainWight::pushButton_double_clicked()
{

    ui->pushButton_single->hide();
    ui->pushButton_double->hide();
    ui->pushButton_rank->hide();

    ui->label->show();
    ui->lineEdit->show();

//    ui->pushButton_start->show();
    ui->pushButton_CreateRoom->show();
    ui->pushButton_JoinRoom->show();
    ui->pushButton_return->show();
}

//排行榜
void MainWight::pushButton_rank_clicked()
{
    this->hide();
    r.show();
}


//返回主菜单
void MainWight::on_pushButton_return_clicked()
{
    ui->pushButton_single->show();
    ui->pushButton_double->show();
    ui->pushButton_rank->show();

    ui->label->hide();
    ui->lineEdit->hide();
    ui->pushButton_CreateRoom->hide();
    ui->pushButton_JoinRoom->hide();
    ui->pushButton_return->hide();
}

void MainWight::pushButton_return_clicked()
{
    this->show();
    r.hide();
}

void MainWight::GameOver(wight* w)
{
   //qDebug()<<"开始处理信号";
    w->hide();
    this->show();
    delete w;
   //qDebug()<<"释放完成";
}


void MainWight::dealmsg(const char *data, int len)
{
    //接受信息
    qDebug()<<"接收到信息";
//    QHostAddress addr;
//    quint16 port;

//    char buff[1024];
//    qint64 r = udpSocket->readDatagram(buff, 1024, &addr, &port);
//    QString msg = QString::fromUtf8(data);
   // qDebug()<<"data:"<<data;
    //qDebug() <<"msg:"<< msg;
    //P1收到加入游戏的信息
    HeadPackage *head=(HeadPackage*)data;
    if(head->type==PackageType::start)
    {
        startPackage startP(PackageType::start,sizeof(startPackage));
        memcpy(&startP,data,len);
        if(startP.flag==1)
        {
            ui->pushButton_Gamestart->show();
        }

        //P2收到开始游戏的信息
        else if(startP.flag==2)
        {
            //P2初始化游戏
            qDebug()<<"P2开始加载游戏";
            wight *w=new wight();
            w->show();
            this->hide();
            w->MyFlight.Id=2;
            w->OtherFlight.clear();
            TeamFlight P1_Flight;
            P1_Flight.Id=1;
            w->OtherFlight.push_back(P1_Flight);
            w->SendPackage_timer.start(Frame);
            disconnect(NetTransfrom::getInstance(),&NetTransfrom::recvData,this,&MainWight::dealmsg);
            qDebug()<<"加载完成";
        }
    }
}

//创建房间
void MainWight::on_pushButton_CreateRoom_clicked()
{
    //主机绑定房间号为端口号
    int prot=ui->lineEdit->text().toUInt();
    int temp=qrand()%45000+1024;
    NetTransfrom::getInstance()->m_recvSocket.bind(prot);
   // qDebug()<<"主机接收端口号为："<<prot;

    //记录对方ip、端口号
//    NetTransfrom::getInstance()->OtherIp=OtherIp;
    NetTransfrom::getInstance()->OtherPort=ui->lineEdit->text().toUInt()+1;
   // qDebug()<<"主机记录副机的端口号为："<<NetTransfrom::getInstance()->OtherPort;

    //sendSocket绑定随机端口号
    while(temp==prot)
    {
       // qDebug()<<"主机随机端口号为："<<temp;
        temp=qrand()%45000+1024;
        NetTransfrom::getInstance()->m_sendSocket.bind(temp);
    }
   // qDebug()<<"主机发送端口号为："<<temp;
}

//加入房间
void MainWight::on_pushButton_JoinRoom_clicked()
{
    //绑定房间号+1为端口号
    int prot=ui->lineEdit->text().toUInt()+1;
    NetTransfrom::getInstance()->m_recvSocket.bind(prot);
   // qDebug()<<"副机接收端口号为："<<prot;

    //sendSocket绑定随机端口号
    int temp=qrand()%45000+1024;
    while(temp==prot)
    {
       // qDebug()<<"副机随机发送端口号为："<<temp;
        temp=qrand()%45000+1024;
        NetTransfrom::getInstance()->m_sendSocket.bind(temp);
    }
   // qDebug()<<"副机发送端口号为："<<temp;

    //记录对方ip、端口号
//    NetTransfrom::getInstance()->OtherIp=OtherIp;
    NetTransfrom::getInstance()->OtherPort=ui->lineEdit->text().toUInt();

   // qDebug()<<"发送消息";
    startPackage startP(PackageType::start,sizeof(startPackage));
    startP.flag=1;
    NetTransfrom::getInstance()->write((char*)(&startP),startP.len);

//    udpSocket->writeDatagram("join",QHostAddress("127.0.0.1"),ui->lineEdit->text().toUInt());

}

//开始游戏按键
void MainWight::on_pushButton_start_clicked()
{   
    //主机开始更新游戏
    wight *w=new wight();

    //给p2发送开始游戏的数据包
    startPackage startP(PackageType::start,sizeof(startPackage));
    startP.flag=2;
    NetTransfrom::getInstance()->write((char*)(&startP),startP.len);
//    udpSocket->writeDatagram("start",QHostAddress(w->OtherIp),w->OtherPort);

    w->show();
    w->GameStart_doubule();
    this->hide();
    connect(w,&wight::return_MainW,this,&MainWight::GameOver);

}

QString MainWight::convert_to_ipv4_addr(QHostAddress &addr)
{
    quint32  addr_origin = addr.toIPv4Address();
    QHostAddress addr_host = QHostAddress(addr_origin);
    QString  addr_str = addr_host.toString();
    return addr_str;
}


