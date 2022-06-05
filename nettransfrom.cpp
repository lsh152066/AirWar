#include "nettransfrom.h"
NetTransfrom* NetTransfrom::net = nullptr;
NetTransfrom::NetTransfrom()
{
    connect(&m_recvSocket,&QUdpSocket::readyRead,this,&NetTransfrom::slotRecvData);
}

void NetTransfrom::write(char *data, int len)
{
//   // qDebug()<<"发送消息"<<data<<OtherIp<<OtherPort;
    m_sendSocket.writeDatagram(data,len,QHostAddress(OtherIp),OtherPort);
//    m_sendSocket.write(data,len);
}

void NetTransfrom::slotRecvData()
{
   // qDebug()<<"-----------------------";
   // qDebug()<<"收到数据";
    memset(m_biffer,0,2048);
    int len=m_recvSocket.bytesAvailable();
    m_recvSocket.readDatagram(m_biffer,m_recvSocket.bytesAvailable());

    emit recvData(m_biffer,len);

}

