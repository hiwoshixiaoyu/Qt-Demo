#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

#include <qssbtn/dialogqssbtn.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //FramelessWindowHint      去掉边框
    //WindowMinimizeButtonHint 禁用最大化按钮
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    initTitleBar();
    initScrollText();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTitleBar()
{
    m_titlsebar = new TitileBar(this);
    m_titlsebar->move(0,0);
    connect(m_titlsebar,SIGNAL(signalTitlebarBtn(BtnType)),this,SLOT(dealTitleBarBtn(BtnType)));
}



//Qt全屏显示函数            showFullScreen()
//Qt最大化显示函数         showMaximized()
//Qt最小化显示函数         showMinimized()
//Qt固定尺寸显示函数      resize(x,y)
//Qt设置最大尺寸函数      setMaximumSize(w,h)
//Qt设置最小尺寸函数       setMinimumSize(w,h)
void MainWindow::dealTitleBarBtn(BtnType type)
{
    switch (type) {
    case BTN_CLOSE:
        QApplication::quit();
          break;
    case BTN_MAX:
        showFullScreen();
          break;
    case BTN_MIN:
         showMinimized();
          break;
    default:
        break;
    }
}



void MainWindow::on_playSound_clicked()
{
    LibAudio::instance()->playSound(":/resource/sound.wav");
}




void MainWindow::on_playmusic_clicked()
{
    LibAudio::instance()->playMusic("E:/music.mp3",false);
}

void MainWindow::on_pause_clicked()
{
    LibAudio::instance()->pauseMusic();
}

void MainWindow::on_continue_2_clicked()
{
    LibAudio::instance()->continueMusic();
}

void MainWindow::on_stop_clicked()
{
    LibAudio::instance()->stopMusic();
}


void MainWindow::on_sqlitedlg_clicked()
{
    m_dlgSqlite = new DialogSqlite;
    //这样就无法操作后面的对话框了
    m_dlgSqlite->exec();
}

void MainWindow::on_createdb_clicked()
{
    LibSql::instance()->initDB();
}


void MainWindow::initScrollText()
{
    m_scrollText = new ScrollText(this);
    m_scrollText->move(130,50);
    m_scrollText->setCurrentText("我是一段滚动的文字");
}

void MainWindow::on_btnscroll_clicked()
{
    m_scrollText->setCurrentText("我是一段滚动的文字");
}



void MainWindow::on_qssBtn_clicked()
{
    this->hide();
    m_dlgQssBtn = new DialogQssBtn;
    //这样就无法操作后面的对话框了
    m_dlgQssBtn->exec();
}
