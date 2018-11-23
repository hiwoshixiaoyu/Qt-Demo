#include "LibSql.h"

#include <QCoreApplication>
#include <QDir>
#include <QtDebug>
#include <QAxObject>

IMPLEMENT_SINGLETON(LibSql)
LibSql::LibSql()
{
    m_sql_query =NULL;
    m_strAppPath = QCoreApplication::applicationDirPath();
    m_strDBPFolder = QCoreApplication::applicationDirPath()+DBFOLDER_NAME;
    m_strDBPath = m_strDBPFolder+DB_NAME;
}

LibSql::~LibSql()
{

}




QT_RESULT LibSql::initDB()
{
    if(m_database.isOpen())
    {
        return QT_FAIL;
    }

    //加载驱动
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir(m_strDBPFolder);
    if(!dir.exists())
    {
        //没有文件夹,创建文件夹
        dir.mkdir(m_strDBPFolder);
    }

    //设置DB参数
   m_database.setDatabaseName(m_strDBPath);
   m_database.setUserName("root");
   m_database.setPassword("123456");
   m_sql_query = new QSqlQuery(m_database);

    //打开DB
   if (!m_database.open())
   {
       qDebug() << "Error: Failed to connect database." << m_database.lastError();
       return QT_FAIL;
   }
   else
   {
       qDebug() << "Succeed to connect database." ;
   }

   createTable();
   return QT_SUCCESS;
}



QT_RESULT LibSql::createTable(TableKind enkind)
{
     m_database.transaction();
     m_sql_query->prepare(SQL_CREATE_DATA);
    qDebug()<<SQL_CREATE_DATA;
    if(!m_sql_query->exec())
    {
        qDebug() << "Error: Fail to create table." << m_sql_query->lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
    m_database.commit();
    return QT_SUCCESS;
}

bool LibSql::IsTableExist(QString strTable)
{
    if(!m_sql_query->exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(strTable)))
    {
            qDebug() << "IsTableExist,Error" << m_sql_query->lastError();
    }

    if(m_sql_query->next())
    {
        if(m_sql_query->value(0).toInt()==0)
        {
          // 表不存在
             qDebug() << "have no"+strTable;
             return false;

        }
        //表存在
         qDebug() << "have"+strTable;
         return true;
    }

    qDebug() << "IsTableExist error";
    return false;
}


QT_RESULT LibSql::insert(DB_Member stMember)
{
    m_database.transaction();
    QString temp =QString("INSERT INTO member(name,note,pic,state,num) values('%1','%2','%3',%4,%5)")
                            .arg(stMember.strName)
                            .arg(stMember.strNote)
                            .arg(stMember.strPic)
                            .arg(stMember.state)
                            .arg(stMember.num);


    if(!m_sql_query->exec(temp))
    {
        qDebug() << "insert,Error" << m_sql_query->lastError();
        return QT_FAIL;
    }

    m_database.commit();    //提交
    return QT_SUCCESS;
}
QT_RESULT LibSql::insert(QList<DB_Member> &listMember)
{
    m_database.transaction();

    QList<DB_Member>::iterator iter;
    for (iter = listMember.begin(); iter!= listMember.end(); ++iter) {

        QString temp =QString("INSERT INTO member(name,note,pic,state,num) values('%1','%2','%3',%4,%5)")
                                .arg((*iter).strName)
                                .arg((*iter).strNote)
                                .arg((*iter).strPic)
                                .arg((*iter).state)
                                .arg((*iter).num);


        if(!m_sql_query->exec(temp))
        {
            qDebug() << "insert,Error" << m_sql_query->lastError();
            return QT_FAIL;
        }

    }

    m_database.commit();    //提交
    return QT_SUCCESS;
}

// 删除表格
//"drop table student"
QT_RESULT LibSql::deleteRow(uint id)
{
    // 7;

    QString temp =QString("DELETE FROM COMPANY WHERE ID =%1").arg(id);
    if(!m_sql_query->exec(temp))
    {
        qDebug() << "insert,Error" << m_sql_query->lastError();
        return QT_FAIL;
    }

     return QT_SUCCESS;
}

//""
QT_RESULT LibSql::updtateRow(uint id, DB_Member stMember)
{

    if(!m_sql_query->exec( QString("update student set %1 = %2 where id = %3").arg(id).arg(id).arg(id)))
    {
        qDebug()<<m_sql_query->lastError();
    }


      return QT_SUCCESS;
}

QT_RESULT LibSql::selectAll(QList<DB_Member> &listMember)
{

       if(!m_sql_query->exec("select * from student"))
       {
           qDebug()<<m_sql_query->lastError();
       }
       else
       {
           while(m_sql_query->next())
           {
               int id = m_sql_query->value(0).toInt();
               QString name = m_sql_query->value(1).toString();
               int age = m_sql_query->value(2).toInt();
               qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
           }
       }

      return QT_SUCCESS;
}
