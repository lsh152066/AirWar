#ifndef MAINWIGHT_H
#define MAINWIGHT_H
#include "wight.h"
#include <QWidget>
#include "rank.h"
namespace Ui {
class MainWight;
}

class MainWight : public QWidget
{
    Q_OBJECT

public:
    explicit MainWight(QWidget *parent = nullptr);
    ~MainWight();

//    wight w;
    rank r;
    QTimer DeleteM;
    configuration P;

    QSqlQuery sql=QSqlQuery(single_sql::GetDb()->db);

    QPainter * m_painter = nullptr;
    void paintEvent(QPaintEvent *event) ;

    QString convert_to_ipv4_addr(QHostAddress &addr);

private slots:
    void pushButton_single_clicked();
    void pushButton_double_clicked();
    void pushButton_rank_clicked();

    void on_pushButton_CreateRoom_clicked();
    void on_pushButton_JoinRoom_clicked();

    void dealmsg(const char *data, int len);
    void pushButton_return_clicked();
    void GameOver(wight*);

    void on_pushButton_start_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::MainWight *ui;

//    QUdpSocket* udpSocket;
};

#endif // MAINWIGHT_H
