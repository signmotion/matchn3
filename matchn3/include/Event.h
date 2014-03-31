#pragma once

#include "Incarnate.h"


namespace matchn {


/**
* ������� ��������.
*/
class Event {
public:
    /**
    * ������������ �������.
    */
    typedef int  timeMS_t;
    struct DataEvent {
        /**
        * ����� ������ �������, ��.
        */
        timeMS_t  start;

        /**
        * ������������ �������, ��.
        * # 0 ��� ������, ���� ������� �� ����� ������������.
        */
        timeMS_t  duration;

        /**
        * ����� ���������� �������, ��.
        */
        timeMS_t  stop;
    };



public:
    Event( std::shared_ptr< Incarnate >,  const protocolDataEvent_t& );

    virtual ~Event();

    virtual void operator()() = 0;


    /**
    * @return ������ � UID �������. ������������ ��� �������� ������������
    *         ��� ������ � �������.
    */
    virtual groupEvent_t group() const = 0;

    virtual uidEvent_t uid() const = 0;


    inline const std::shared_ptr< Incarnate >  element() const {
        assert( !mElement.expired()
            && "������� ���������." );
        return mElement.lock();
    }

    inline std::shared_ptr< Incarnate >  element() {
        assert( !mElement.expired()
            && "������� ���������." );
        return mElement.lock();
    }


    template< typename T >
    inline T data( const std::string& name, const T& def = T() ) const {
        return mRawData.at< T >( name, def );
    };


    inline DataEvent const&  data() const {
        return mData;
    }


    inline const std::shared_ptr< World >  world() const {
        return world();
    }

    inline std::shared_ptr< World >  world() {
        return element()->world();
    }


    /**
    * @return ������� ��������� �� ������ ������ �������.
    *         ����������� ������������ ������� � ������� �����.
    */
    inline bool actuality() const {
        const auto ct = ManagerEvent::time();
        return (ct < mData.stop);
    }


    /**
    * ������ ������� ������������.
    */
    inline void dropActuality() {
        mData.stop = mData.start;
    }


    /**
    * @return ������� ������� � �� �������� �� ���������� ����� �������.
    *         ������������� ����� ��� 0 - ������� �����������.
    */
    inline int deltatime() const {
        return (mData.stop - ManagerEvent::time());
    }


    /**
    * @return ������� � ���������  [ 0.0 (��������); 1.0 (���������) )
    *         �������� �� ���������� ����� �������.
    */
    inline float nepperDeltatime() const {
        assert( (mData.duration != 0)
            && "�������� ����������: ������������ ������� �� ����� ���� == 0." );
        const float u =
            1.0f -
            static_cast< float >( mData.stop - ManagerEvent::time() ) /
            static_cast< float >( mData.duration );
        return (u > 1.0f) ? 1.0f : (u < 0.0f) ? 0.0f : u;
    }


    /**
    * @return ���-���. ������� �� uid() � ���������� ��������� ��������.
    */
    inline size_t hash() const {
        size_t seed = boost::hash_value( uid() );
        const auto c = element()->logicCoord();
        boost::hash_combine( seed, c );
        return seed;
    }


protected:
    std::weak_ptr< Incarnate >  mElement;

    
    /**
    * ������������ �������.
    */
    const protocolDataEvent_t  mRawData;

    /**
    * ������������ �� mRawData � ����������� ������������.
    * ������������ ��� �������� �������� �� CPU.
    */
    DataEvent  mData;


    /**
    * ����� (��� �������� ������).
    */
    static const boost::posix_time::milliseconds  HALF_SECOND;
    static const boost::posix_time::milliseconds  SECOND;
    static const boost::posix_time::milliseconds  TWO_SECOND;
};




/**
* ������� "������� ���".
*/
class WaitEvent :
    public Event
{
protected:
    inline WaitEvent(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : Event( e, data ) {
    }

    inline ~WaitEvent() {
    }

    virtual inline groupEvent_t group() const { return "wait"; };
};




/**
* ������� "������� ������".
*/
class DropEvent :
    public Event
{
protected:
    inline DropEvent(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : Event( e, data ) {
    }

    inline ~DropEvent() {
    }

    virtual inline groupEvent_t group() const { return "drop"; };
};


} // matchn
