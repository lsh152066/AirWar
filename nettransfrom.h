#ifndef NETTRANSFROM_H
#define NETTRANSFROM_H
#include<QUdpSocket>

class NetTransfrom:public QObject
{
    Q_OBJECT
public:
    static NetTransfrom* getInstance(){
        if(net==NULL)
            net=new NetTransfrom();
        return net;
    }

    void write(char * data,int len);

private slots:
    void slotRecvData();

signals:
    void recvData(char* data,int len);
private:
    NetTransfrom();
    static NetTransfrom* net;

public:
    QUdpSocket m_recvSocket;
    QUdpSocket m_sendSocket;
    char m_biffer[2048];
    QString OtherIp="127.0.0.1";
    quint16 OtherPort=0;
};

#endif // NETTRANSFROM_H
