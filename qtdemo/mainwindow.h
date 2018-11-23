#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DialogSqlite.h"

#include <QMainWindow>

#include <titlebar/titilebar.h>
#include <lib/LibAudio.h>
#include<lib/LibSql.h>
#include <scrolltext/ScrollText.h>
#include <qssbtn/dialogqssbtn.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initTitleBar();
    void initScrollText();



private slots:
   void  dealTitleBarBtn(BtnType type);

   void on_playSound_clicked();
   void on_playmusic_clicked();
   void on_pause_clicked();
   void on_continue_2_clicked();
   void on_stop_clicked();

   void on_sqlitedlg_clicked();

   void on_createdb_clicked();

   void on_btnscroll_clicked();



   void on_qssBtn_clicked();

private:
    Ui::MainWindow *ui;
    TitileBar *m_titlsebar;
    DialogSqlite *m_dlgSqlite;
    ScrollText *m_scrollText;
    DialogQssBtn *m_dlgQssBtn;
};

#endif // MAINWINDOW_H
