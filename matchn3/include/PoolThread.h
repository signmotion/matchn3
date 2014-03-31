#pragma once

#include <set>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>


namespace matchn {


template< size_t countThread >
class PoolThread;




/**
* Рабочий для выполнения задач в потоках.
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
* Пул потоков.
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
    * Добавляет новое задание в пул.
    *
    * @see unenqueue()
    */
    template< class F >
    void enqueue( uid_t, F );




    /**
    * Удаляет задание из списка пула.
    *
    * #! Метод должен использоваться исключительно внутри потоков
    *    непосредственно при их завершении.
    */
    void unenqueue( uid_t );




    inline std::set< uid_t > const&  uidSet() const {
        return mUIDSet;
    }




private:
    /**
    * Сохраняем рабочих, чтобы могли при необходимости присоединиться к ним.
    */
    typedef std::unique_ptr< boost::thread >  thread_ptr;
    std::vector< thread_ptr >  mWorkerSet;

    /**
    * Запоминаем добавленный поток.
    *
    * #! Поток сам должен позаботиться о вызове unenqueue().
    */
    std::set< uid_t >  mUIDSet;
 
    /**
    * Обёртка boost::asio.
    */
    boost::asio::io_service        mService;
    boost::asio::io_service::work  mWorking;

    boost::mutex  mtx;

    friend class workerThread_t;
};


} // matchn








#include "PoolThread.inl"
