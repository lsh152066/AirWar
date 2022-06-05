#include "rank.h"
#include "ui_rank.h"

rank::rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rank)
{
    ui->setupUi(this);
    m_painter = new QPainter(this);
    db=single_sql::GetDb()->db;
    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    connect(ui->pushButton_return,&QPushButton::clicked,this,&rank::pushButton_return_clicked);


    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可修改
    model->setTable("rank");
    model->setSort(1,Qt::DescendingOrder);//降序
    model->select();
    ui->tableView->setModel(model);
}

rank::~rank()
{
    delete ui;
}

void rank::paintEvent(QPaintEvent *event)
{
    m_painter->begin(this);
    m_painter->drawImage(0,0,P.m_mainwight);

    m_painter->end();
}

void rank::pushButton_return_clicked()
{
    emit return_MainW();
    model->setSort(1,Qt::DescendingOrder);
    model->select();
    ui->tableView->setModel(model);
}


