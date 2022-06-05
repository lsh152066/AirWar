#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include"single_sql.h"
#include "configuration.h"
namespace Ui {
class rank;
}

class rank : public QWidget
{
    Q_OBJECT

public:
    explicit rank(QWidget *parent = nullptr);
    ~rank();

    void pushButton_return_clicked();

    configuration P;
    QPainter * m_painter = nullptr;
    void paintEvent(QPaintEvent *event) ;



signals:
    void return_MainW();

private:
    Ui::rank *ui;
    QSqlDatabase db;
    QSqlTableModel *model ;

    QSqlQuery sql;
};

#endif // RANK_H
