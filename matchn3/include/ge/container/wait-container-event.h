#pragma once

#include "../../Event.h"


namespace matchn {


/**
* ����������� ���������.
*/
class WaitContainer :
    public WaitEvent
{
public:
    inline WaitContainer(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~WaitContainer() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-container"; };


private:
    /**
    * ���������, ���� �� ��� ���� ����������� ��������� �����.
    */
    void verifyPlaceAbove();
};


} // matchn
