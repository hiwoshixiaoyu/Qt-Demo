#include "LibExcel.h"



IMPLEMENT_SINGLETON(LibExcel)
LibExcel::LibExcel()
{

}

LibExcel::~LibExcel()
{

}



QT_RESULT LibExcel::excelCheckRowColumns(QAxObject *worksheet, int &iRows, int &iColumns, QString &strError)
{

    //—————————获取该sheet的数据范围（可以理解为有数据的矩形区域）————
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");

     //———————————————————获取行数———————————————
    QAxObject * rows = usedrange->querySubObject("Rows");
    iRows = rows->property("Count").toInt();
    qDebug() << QString("行数为: %1").arg(QString::number(iRows));

     //————————————获取列数—————————
    QAxObject * columns = usedrange->querySubObject("Columns");
    iColumns = columns->property("Count").toInt();
    qDebug() << QString("列数为: %1").arg(QString::number(iColumns));


    if( (iRows <1) || (iColumns <1))
    {
       strError ="行数列数不足";
       return QT_FAIL;
    }


    //————————数据的起始行———
    int iStartRow = rows->property("Row").toInt();
    qDebug() << QString("起始行为: %1").arg(QString::number(iStartRow));
    //————————数据的起始列————————————
    int iColumn = columns->property("Column").toInt();
    qDebug() << QString("起始列为: %1").arg(QString::number(iColumn));

    if( iStartRow!= 1 || iColumn!=1)
    {
       strError ="起始行，请用第一行。起始列，请用第一列";
       return QT_FAIL;
    }
    return QT_SUCCESS;
}

QT_RESULT LibExcel::excelCheckColumnsName(QAxObject *worksheet, QString &strError)
{
    //——————————————读出数据—————————————
    //获取第i行第j列的数据
    //假如是第6行，第6列 对应表中F列6行，即F6
    QAxObject *range1 = worksheet->querySubObject("Range(QString)", "A1");//B1
    QString strRow6Col6 = "";
    strRow6Col6 = range1->property("Value").toString();
    qDebug() << "第1行，第1列的数据为：" + strRow6Col6;

    return QT_SUCCESS;
}





QT_RESULT LibExcel::importMember(QString strExcelPath,QList<DB_Member> &listMember,QString &strError)
{
     QAxObject *excel = new QAxObject("Excel.Application");    //本例中，excel设定为Excel文件的操作对象
     excel->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见，false表示为不可见
     QAxObject *workbooks = excel->querySubObject("WorkBooks");;
     QAxObject *workbook = NULL;  //Excel操作对象

   //————————————————按文件路径打开文件————————————————————
   workbook = workbooks->querySubObject("Open(QString&)", strExcelPath);
   if(NULL== workbook)
   {
      strError ="无法打开目录";
      return QT_FAIL;
   }

   // 获取打开的excel文件中所有的工作sheet
   QAxObject * worksheets = workbook->querySubObject("WorkSheets");

   int iWorkSheet = worksheets->property("Count").toInt();
   qDebug() << QString("Excel文件中表的个数: %1").arg(QString::number(iWorkSheet)).toStdString().c_str();
    if(iWorkSheet<1)
    {
        strError ="sheet错误";
       return QT_FAIL;
    }

   //获取第一个表
   QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);


   int iRows;
   int columns;

    if(QT_FAIL== excelCheckRowColumns(worksheet,iRows,columns,strError))
    {
        return QT_FAIL;
    }

   if(QT_FAIL== excelCheckColumnsName(worksheet,strError))
   {
       return QT_FAIL;
   }


   //数据存入结构体

   DB_Member member;

   QAxObject *rangeTemp=NULL;
   for(int row = 2;row<iRows+1;row++)
    {
        member.reset();
        rangeTemp= worksheet->querySubObject("Range(QString)", QString("A%1").arg(row));//B1
        member.id= rangeTemp->property("Value").toInt();
        if(member.id!= (row - 1))
        {
            strError = "序号错误";
            return QT_FAIL;
        }
        rangeTemp = worksheet->querySubObject("Range(QString)", QString("B%1").arg(row));
        member.strName= rangeTemp->property("Value").toString();
        listMember.push_back(member);
   }



   workbook->dynamicCall("Close()");
   excel->dynamicCall("Quit()");
   if (excel)
   {
      delete excel;
      excel = NULL;
   }
   return QT_SUCCESS;
}

QT_RESULT LibExcel::writeExcel()
{   
    return QT_SUCCESS;
}
