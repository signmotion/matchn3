#include "../../../include/stdafx.h"
#include "../../../include/ge/background/Background.h"
#include "../../../include/ge/world/World.h"
#include "../../../include/ManagerEvent.h"


namespace matchn {


Background::Background(
    std::shared_ptr< World >  w,
    const std::string&        name
) :
    // ��� ������ ����� ������
    Incarnate( w, typelib::coord2Int_t::ZERO(), -1 ),
    mName( name )
{
    assert( !mName.empty()
        && "�� ������� �������� ����." );

    load( w, "background", name );
}




Background::~Background() {
}




void Background::draw( std::shared_ptr< World >  w ) const {
    // # ��� ���� ���������� ������ ���� �������.
    const uidEvent_t e = ManagerEvent::uid< WaitBackground >();
    drawSprite( w, e );
}




std::shared_ptr< Background >
Background::valueOf(
    std::shared_ptr< World >  w,
    const std::string&        name
) {
    return std::shared_ptr< Background >( new Background( w, name ) );
}


} // matchn
