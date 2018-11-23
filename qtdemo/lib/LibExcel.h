#ifndef LIBEXCEL_H
#define LIBEXCEL_H
#include "common.h"

#include <QAxObject>

class LibExcel
{
    DECLARE_SINGLETON(LibExcel)
public:
    LibExcel();
    virtual ~LibExcel();


    QT_RESULT  importMember(QString strExcelPath,QList<DB_Member> &listMember,QString &strError);
    QT_RESULT  writeExcel();

private:
    QT_RESULT  excelCheckRowColumns(QAxObject * worksheet,int &iRows,int &iColumns,QString &strError);
    QT_RESULT  excelCheckColumnsName(QAxObject * worksheet,QString &strError);

};

#endif // LIBEXCEL_H
