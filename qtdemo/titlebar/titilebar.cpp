#include "titilebar.h"

#include <QMouseEvent>
#include <QPushButton>
#include <QSizePolicy>

TitileBar::TitileBar(QWidget *parent) : QWidget(parent)
{
    setObjectName("bg");

    //如果不加这个属性，填充颜色会不好用
    setAutoFillBackground(true);
    QPalette palette;
    //填充颜色
    palette.setColor(QPalette::Background, QColor(150,150,150,100));
    //添加自己的图片
    //palette.setBrush(QPalette::Background,QBrush(QPixmap(":/1.png")));
    setPalette(palette);

    //设置大小
    setFixedSize(800,50);


    m_btnMax =new QPushButton(this);
    m_btnMax->setText("最大化");
    m_btnMin =new QPushButton(this);
    m_btnMin->setText("最小化");
    m_btnClose =new QPushButton(this);
    m_btnClose->setText("关闭");

    m_btnMax->move(500,20);
    m_btnMin->move(600,20);
    m_btnClose->move(700,20);

    m_titleText = new QLabel(this);
    m_titleText->setText("Qt demo 大全");

    connect(m_btnMax,SIGNAL(clicked()),SLOT(sendSingalMax()));
    connect(m_btnMin,SIGNAL(clicked()),SLOT(sendSingalMin()));
    connect(m_btnClose,SIGNAL(clicked()),SLOT(sendSingalClose()));
    //添加qss样式
   // loadStyleSheet("maintitle");

}

TitileBar::~TitileBar()
{

}

//双击最大化没有实现
//void TitileBar::mouseDoubleClickEvent(QMouseEvent *event)
//{
//
//}


void TitileBar::mousePressEvent(QMouseEvent *event)
{
    m_isPressed=true;
    m_startMovePos = event->globalPos();
}

void TitileBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
}

void TitileBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed=false;
}


void TitileBar::loadStyleSheet(const QString &sheetName)
{
   // QString styleSheet="QWidget#bg{background-image: url(:/1.png);}";
    //this->setStyleSheet(styleSheet);
    QFile file(":/"+sheetName+".qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void TitileBar::sendSingalMax()
{
    emit signalTitlebarBtn(BTN_MAX);
}

void TitileBar::sendSingalMin()
{
    emit signalTitlebarBtn(BTN_MIN);
}

void TitileBar::sendSingalClose()
{
    emit signalTitlebarBtn(BTN_CLOSE);
}

