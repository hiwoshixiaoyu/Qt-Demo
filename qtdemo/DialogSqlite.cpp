#include "dialogsqlite.h"
#include "ui_dialogsqlite.h"
#include <QFileDialog>
#include <qDebug>
DialogSqlite::DialogSqlite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSqlite)
{
    ui->setupUi(this);

        model = new QStandardItemModel();
        model->setColumnCount(7);
        model->setHeaderData(0, Qt::Horizontal, QString("选中"));
        model->setHeaderData(1, Qt::Horizontal, QString("序号"));
        model->setHeaderData(2, Qt::Horizontal, QString("抽奖名单"));
        model->setHeaderData(3, Qt::Horizontal, QString("备注"));
        model->setHeaderData(4, Qt::Horizontal, QString("照片"));
        model->setHeaderData(5, Qt::Horizontal, QString("状态"));
        model->setHeaderData(6, Qt::Horizontal, QString("区分编号"));

        //verticalHeaderVisible

        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->setModel(model);


        //fuck了 需要在这之后设置
        ui->tableView->setColumnWidth(0,30);
        ui->tableView->setColumnWidth(1,40);
        ui->tableView->setColumnWidth(2,40);
        ui->tableView->setColumnWidth(3,40);
        ui->tableView->setColumnWidth(4,40);
        ui->tableView->setColumnWidth(5,40);
        ui->tableView->setColumnWidth(6,40);

        init();

        setStyleSheet("QTableView::item{selection-background-color:rgb(255,0,0)}");

        //解决点击 x 不析构的问题
        setAttribute(Qt::WA_DeleteOnClose);
}

DialogSqlite::~DialogSqlite()
{
    delete ui;
}



void DialogSqlite::init()
{
    for(int i = 0; i < 10; ++i)
    {
        model->setItem(i, 1, new QStandardItem(QString::number(i+1,10)));
        model->setItem(i, 2, new QStandardItem("张三"));
        model->setItem(i, 3, new QStandardItem("工程部"));
        model->setItem(i, 4, new QStandardItem("pic/photo1"));

        QStandardItem *item6 = new QStandardItem("已中奖");
        item6->setForeground(QBrush(QColor(255, 0, 0)));
        model->setItem(i, 6,item6);

        QStandardItem *item = new QStandardItem();
        item->setCheckable(true);
        item->setSelectable(false);
        item->setCheckState(Qt::Unchecked);
        model->setItem(i, 0, item);
    }

}

void DialogSqlite::on_tableView_clicked(const QModelIndex &index)
{

    qDebug()<<index.column()<<endl;
    qDebug()<<index.row()<<endl;
    qDebug()<<index.column()<<endl;

   // model->removeRow(index.row());


   // model->setData(model->index(1,1),"helloworld");
    //model->removeRow(index.row());
    Qt::CheckState isCheck = model->item(index.row(),0)->checkState();
    qDebug()<<isCheck<<endl;


    //删除所有行
    //model->removeRows(0,model->rowCount());
}


void DialogSqlite::on_pushButton_clicked()
{

   QString file_name = QFileDialog::getOpenFileName(NULL,"导入名单","../",tr("*.excel *.xlsx"));
   qDebug()<<file_name<<endl;

   model->item(1,1)->setText("hello world");
}
