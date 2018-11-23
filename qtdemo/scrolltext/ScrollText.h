#ifndef SCROLL_TEXT_H
#define SCROLL_TEXT_H


#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
class ScrollText : public QWidget
{
    Q_OBJECT

public:
    ScrollText(QWidget *parent = nullptr);
    ~ScrollText();

    // 设置文字内容
    void setCurrentText(QString text);

private:
    QLabel *m_TopLabel = nullptr;
    QLabel *m_CurrentLabel = nullptr;

    QPropertyAnimation *m_TopPropertyAnimation = nullptr;
    QPropertyAnimation *m_CurrentPropertyAnimation = nullptr;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif
