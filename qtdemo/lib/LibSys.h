#ifndef LIBSYS_H
#define LIBSYS_H
#include"common.h"
class LibSys
{
     DECLARE_SINGLETON(LibSys)
public:
    LibSys();
     virtual ~LibSys();

public:
    void dosomthing();
};

#endif // LIBSYS_H
