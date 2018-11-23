#ifndef COMMON_H
#define COMMON_H

#include <QtDebug>

//返回值成功和失败
enum QT_RESULT
{
    QT_SUCCESS,
    QT_FAIL,
};


//单例模式宏函数
#define DECLARE_SINGLETON( class_name )																	\
    public:																								\
    static class_name * instance()																		\
        { if ( 0 == _object ){ _object = new class_name; } return _object; }							\
    static void		  uninit_object()																	\
        { if ( 0 != _object ){ delete _object; _object = 0; } }											\
    static void		  init_object()																		\
        { uninit_object(); }																			\
    private:																							\
    static class_name * _object;																		\

#define IMPLEMENT_SINGLETON( class_name )																\
    class_name * class_name::_object = nullptr;



typedef   struct tagmember
{
    QString strName;
    QString strNote;
    QString strPic;
    int state;
    uint num;
    uint id;

   void  reset()
    {
        strName="";
        strNote="";
        strPic="";
        state = 0;
        num = -1;
        id = 1;
    }
}DB_Member;

#endif // COMMON_H
