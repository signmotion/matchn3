namespace matchn {


template< size_t countThread >
inline void WorkerThread< countThread >::operator()() {
    mPool.mService.run();
}




template< size_t countThread >
inline PoolThread< countThread >::PoolThread() :
    mWorking( mService )
{
    // создаём нескольких рабочих в потоках
    for (size_t i = 0; i < countThread; ++i) {
        mWorkerSet.push_back( thread_ptr(
            new boost::thread( workerThread_t( *this ) )
        ) );
    }
}




template< size_t countThread >
inline PoolThread< countThread >::~PoolThread() {
    boost::mutex::scoped_lock  lock( mtx );
    mService.stop();
    for (auto itr = mWorkerSet.cbegin(); itr != mWorkerSet.cend(); ++itr) {
        ( *itr )->join();
    }
}




template< size_t countThread >
template< class F >
inline void PoolThread< countThread >::enqueue( uid_t uid,  F fn ) {
    boost::mutex::scoped_lock  lock( mtx );
    mUIDSet.insert( uid );
    mService.post( fn );
}




template< size_t countThread >
inline void PoolThread< countThread >::unenqueue( uid_t uid ) {
    boost::mutex::scoped_lock  lock( mtx );
    auto ftr = mUIDSet.find( uid );
    assert( (ftr != mUIDSet.end())
        && "Поток с заданным UID не найден." );
    mUIDSet.erase( ftr );
}


} // matchn
