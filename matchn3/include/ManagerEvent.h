#pragma once

#include "configure.h"
#include "struct.h"
#include "PoolThread.h"


namespace matchn {


class Event;


class ManagerEvent {
public:
    typedef PoolThread< COUNT_THREAD >  poolThread_t;


public:
    ManagerEvent();

    virtual ~ManagerEvent();


    void push( std::shared_ptr< Event > );


    /**
    * @return ������� �����, ��������� �� ������ �������, ��.
    */
    static int time();


    /**
    * @return ��������� �����, ��������� �� ������ �������.
    */
    static size_t random();


    /**
    * @return ������ � UID �������.
    */
    template< class T >
    static inline groupEvent_t group() {
        T e;
        return e.group();
    }


    template< class T >
    static inline uidEvent_t uid() {
        T  e( nullptr, protocolDataEvent_t() );
        return e.uid();
    }


private:
    poolThread_t  mPool;




public:
    /**
    * ��������� ���� ������.
    */
    boost::mutex  mtx;
};


} // matchn
