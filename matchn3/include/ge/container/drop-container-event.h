#pragma once

#include "../../Event.h"


namespace matchn {


/**
* ��������� ������.
*
* @todo fine? �������� ����� Action[Element]. ������������� ������������.
*/
class DropContainer :
    public WaitEvent
{
public:
    inline DropContainer(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~DropContainer() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-container"; };


private:
    void changeVisualCoord();
    void changeLogicCoord();
};


} // matchn
