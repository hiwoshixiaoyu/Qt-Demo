#ifndef DIALOGQSSBTN_H
#define DIALOGQSSBTN_H

#include <QDialog>

namespace Ui {
class DialogQssBtn;
}

class DialogQssBtn : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQssBtn(QWidget *parent = nullptr);
    ~DialogQssBtn();

     void loadStyleSheet(const QString &sheetName);
private slots:
     void on_reloadQss_clicked();

private:
    Ui::DialogQssBtn *ui;
};

#endif // DIALOGQSSBTN_H
