#ifndef TITILEBAR_H
#define TITILEBAR_H

#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QWidget>

enum BtnType
{
     BTN_CLOSE,
     BTN_MAX,
     BTN_MIN,
};

class TitileBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitileBar(QWidget *parent = nullptr);
    virtual ~TitileBar();


private:
    //void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    // 加载样式文件;
    void loadStyleSheet(const QString &sheetName);


signals:
    void signalTitlebarBtn(BtnType type);

private slots:
    void sendSingalMax();
    void sendSingalMin();
    void sendSingalClose();
private:
    // 移动窗口的变量;
    bool m_isPressed;
    QPoint m_startMovePos;

    QPushButton *m_btnMax;
    QPushButton *m_btnMin;
    QPushButton *m_btnClose;
    QLabel *m_titleText;

};

#endif // TITILEBAR_H
