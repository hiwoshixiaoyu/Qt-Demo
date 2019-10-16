#ifndef LibSql_H
#define LibSql_H

#include "common.h"

#include <QAxObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>


enum TableKind
{
    table1_Data,
    table2_Price,
};





#define DB_NAME "data.db"
#define DBFOLDER_NAME "/db/"




#define QSL_CREATEDB  'CREATE TABLE \"aaa\" (\"id\" integer NOT NULL PRIMARY KEY AUTOINCREMENT,\"name\" blob,\"remark\" blob,\"pic\" blob,\"state\" integer);'


#define SQL_CREATE_DATA "CREATE TABLE 'member' ('id' integer NOT NULL PRIMARY KEY AUTOINCREMENT,\
                                    'name' blob(30) NOT NULL,\
                                    'note' blob(30),\
                                    'pic' blob,\
                                    'state' integer,\
                                    'num' integer);"




#define SQL_PRIZE_DATA  "DROP TABLE IF EXISTS 'prize';\
                        CREATE TABLE 'prize' (  \
                                  'id' integer NOT NULL PRIMARY KEY AUTOINCREMENT,\
                                  'prize_name' blob,\
                                  'number' integer,\
                                  'pici' integer,\
                                  'prize' blob,\
                                  'pic' blob,\
                                  'duplicate' blob,\
                                  'rule' text);"


class LibSql
{
    DECLARE_SINGLETON(LibSql)
public:
    LibSql();
    virtual  ~LibSql();


    QT_RESULT  initDB();
    QT_RESULT  insert(DB_Member stMember);
    QT_RESULT  insert(QList<DB_Member> &listMember);

    QT_RESULT  deleteRow(uint id);
    QT_RESULT  updtateRow(uint id,DB_Member stMember);
    QT_RESULT  selectAll(QList<DB_Member> &listMember);

private:
    QT_RESULT createTable(TableKind enkind = table1_Data);
    bool      IsTableExist(QString table);


    //app Path
    QString m_strAppPath;
    //DB folder
    QString m_strDBPFolder;
    //DB path
    QString m_strDBPath;
    QSqlDatabase m_database;
    QSqlQuery *m_sql_query;
};


#endif // LibSql_H
