#pragma once

#include <set>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>


namespace matchn {


template< size_t countThread >
class PoolThread;




/**
* ������� ��� ���������� ����� � �������.
*/
template< size_t countThread >
class WorkerThread {
public:
    typedef PoolThread< countThread >  poolThread_t;




public:
    inline WorkerThread( poolThread_t& pool ) : mPool( pool ) { }




    void operator()();




private:
    poolThread_t&  mPool;
};








/**
* ��� �������.
*/
template< size_t countThread >
class PoolThread {
public:
    typedef size_t  uid_t;

    typedef WorkerThread< countThread >  workerThread_t;




public:
    PoolThread();




    ~PoolThread();




    /**
    * ��������� ����� ������� � ���.
    *
    * @see unenqueue()
    */
    template< class F >
    void enqueue( uid_t, F );




    /**
    * ������� ������� �� ������ ����.
    *
    * #! ����� ������ �������������� ������������� ������ �������
    *    ��������������� ��� �� ����������.
    */
    void unenqueue( uid_t );




    inline std::set< uid_t > const&  uidSet() const {
        return mUIDSet;
    }




private:
    /**
    * ��������� �������, ����� ����� ��� ������������� �������������� � ���.
    */
    typedef std::unique_ptr< boost::thread >  thread_ptr;
    std::vector< thread_ptr >  mWorkerSet;

    /**
    * ���������� ����������� �����.
    *
    * #! ����� ��� ������ ������������ � ������ unenqueue().
    */
    std::set< uid_t >  mUIDSet;
 
    /**
    * ������ boost::asio.
    */
    boost::asio::io_service        mService;
    boost::asio::io_service::work  mWorking;

    boost::mutex  mtx;

    friend class workerThread_t;
};


} // matchn








#include "PoolThread.inl"
