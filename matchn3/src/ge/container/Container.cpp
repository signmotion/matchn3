#include "../../../include/stdafx.h"
#include "../../../include/ge/container/Container.h"
#include "../../../include/ge/world/World.h"
#include "../../../include/ManagerEvent.h"


namespace matchn {


size_t Container::countAvailable_ = 0;




Container::Container(
    std::shared_ptr< World >     w,
    const uidContainer_t&        name,
    const typelib::coord2Int_t&  logicCoord
) :
    // ���������� �������� ����� ����
    Incarnate( w, logicCoord, 1 ),
    mName( name )
{
    assert( (mName != 0)
        && "�������� ���������� ������ ���� �������." );

    load( w, "container",  std::string( 1, name ) );
}




Container::~Container() {
}




void Container::draw( std::shared_ptr< World >  w ) const {
    // @todo ��� ������� ���������� ����� �������.
    const uidEvent_t e = ManagerEvent::uid< WaitContainer >();
    drawSprite( w, e );
}




std::shared_ptr< Container >
Container::valueOf(
    std::shared_ptr< World >     world,
    const uidContainer_t&        name,
    const typelib::coord2Int_t&  logicCoord
) {
    return std::unique_ptr< Container >( new Container( world, name, logicCoord ) );
}




typelib::size2Int_t
Container::needVisualSize() const {
    // ��������� ������ ���������� � ����� ���� N x M
    const auto vs = 
        typelib::size2_t( WINDOW_WIDTH, WINDOW_HEIGHT ) /
        static_cast< typelib::size2_t >( ELEMENT_SPRITE_SIZE ) /
        typelib::size2_t( world()->N, world()->M ) * 0.9;

    return static_cast< typelib::size2_t >( ELEMENT_SPRITE_SIZE ) * vs;
}




uidContainer_t
Container::nextRandom() {

    static boost::mt19937  gen;
    // # ��������� ������ ��� �������� �������: ��� ���� ���������, �������
    //   ������ ������. �������: -2.
    const size_t ne = countAvailable();
    assert( (ne >= 2)
        && "� ����� 'media/element' ������ ���� ������ ������ ��������." );
    static boost::uniform_int<>   uni( 'a', 'a' + ne - 2 );
    static boost::variate_generator< boost::mt19937&, boost::uniform_int<> >
        random( gen, uni );

    return static_cast< uidContainer_t >( random() );
}




size_t
Container::countAvailable() {
    if (countAvailable_ == 0) {
        std::set< std::string >  folder;
        typelib::file::listFolder( &folder, PATH_MEDIA + "/container" );
        countAvailable_ = folder.size();
        assert( (countAvailable_ > 0)
            && "� ����� 'media/container' �� ���������� �� ������ ��������." );
    }

    return countAvailable_;
}


} // matchn
