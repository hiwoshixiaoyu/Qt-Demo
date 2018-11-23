#include "dialogqssbtn.h"
#include "ui_dialogqssbtn.h"

#include <QFile>

DialogQssBtn::DialogQssBtn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogQssBtn)
{
    ui->setupUi(this);
    loadStyleSheet(":/resource/style.qss");
}

DialogQssBtn::~DialogQssBtn()
{
    delete ui;
}


void DialogQssBtn::loadStyleSheet(const QString &sheetName)
{
    QFile file(sheetName);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
     file.close();
}

void DialogQssBtn::on_reloadQss_clicked()
{
    //动态加载请用绝对路径
    QFile file("E:/style.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
    file.close();
}
