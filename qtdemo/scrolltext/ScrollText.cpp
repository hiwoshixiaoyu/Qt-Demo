#include "ScrollText.h"
#include <QResizeEvent>

ScrollText::ScrollText(QWidget *parent)
    :QWidget(parent)
{
    m_TopLabel = new QLabel(this);
    m_CurrentLabel = new QLabel(this);
    m_TopLabel->hide();
    m_CurrentLabel->hide();

    m_TopPropertyAnimation = new QPropertyAnimation(this);
    m_TopPropertyAnimation->setTargetObject(m_TopLabel);
    m_TopPropertyAnimation->setPropertyName("geometry");
    m_TopPropertyAnimation->setDuration(700);

    m_CurrentPropertyAnimation = new QPropertyAnimation(this);
    m_CurrentPropertyAnimation->setTargetObject(m_CurrentLabel);
    m_CurrentPropertyAnimation->setPropertyName("geometry");
    m_CurrentPropertyAnimation->setDuration(700);
}

ScrollText::~ScrollText()
{

}

void ScrollText::setCurrentText(QString text)
{
    m_TopLabel->setText(text);
    if (m_CurrentLabel->text().isEmpty())
    {
        m_CurrentLabel->setGeometry(0, 0, this->width(), this->height());
        m_TopLabel->setText(text);
        m_CurrentLabel->setText(text);
        if (m_CurrentLabel->isHidden())
            m_CurrentLabel->show();
    }
    else
    {
        QString string = m_CurrentLabel->text();
        m_TopLabel->setText(string);
        m_CurrentLabel->setText(text);

        if (m_CurrentLabel->isHidden())
            m_CurrentLabel->show();
        if (m_TopLabel->isHidden())
            m_TopLabel->show();

        m_TopPropertyAnimation->stop();
        m_CurrentPropertyAnimation->stop();
        m_TopPropertyAnimation->start();
        m_CurrentPropertyAnimation->start();
    }
}

void ScrollText::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();

    m_TopPropertyAnimation->setStartValue(QRect(0, 0, width, height));
    m_TopPropertyAnimation->setEndValue(QRect(0, -height, width, height));

    m_CurrentPropertyAnimation->setStartValue(QRect(0, height * 2, width, height));
    m_CurrentPropertyAnimation->setEndValue(QRect(0, 0, width, height));

    return QWidget::resizeEvent(event);
}
