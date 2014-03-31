#include "../include/stdafx.h"
#include "../include/VIncarnate.h"
#include "../include/ge/world/World.h"
#include "../include/ManagerSprite.h"


namespace matchn {


std::unique_ptr< ManagerSprite >  VIncarnate::mManagerSprite(
    new ManagerSprite()
);




VIncarnate::VIncarnate(
    const typelib::coord2Int_t&  vc,
    int  order
) :
    mCoord( vc ),
    mRotation( 0 ),
    mAlpha( 1.0f ),
    mOrder( order ),
    mSprite( new sprite_t() )
{
}




VIncarnate::~VIncarnate() {
}




CL_Sprite*
VIncarnate::sprite( const uidEvent_t& e ) const {
    auto ftr = mSprite->find( e );
    if (ftr != mSprite->end()) {
        return ftr->second.get();
    }

    // ������ ��� ����� ������� �� ������, ����� ����� �� ���������
    static const uidEvent_t eDef = "default";
    ftr = mSprite->find( eDef );
    assert( (ftr != mSprite->end())
        && "������ �� ������." );
    return ftr->second.get();
}




void
VIncarnate::drawSprite(
    std::shared_ptr< World >  w,
    const uidEvent_t&  e
) const {
    auto s = sprite( e );
    assert( s
        && "������ ��� ��������� ������� �� ������." );

    auto gc = w->visual()->get_gc();
    s->set_angle( CL_Angle( visualRotation< float >(), cl_degrees ) );
    s->set_alpha( visualAlpha() );
    s->draw( gc, visualCoord().x, visualCoord().y );
    //Console::instance() << visualCoord() << std::endl;
    s->update();
}




void
VIncarnate::addSprite( std::shared_ptr< World > w,  const std::string&  path ) {
#ifdef _DEBUG
    std::cout << "\n��������� '" << path << "'\n";
#endif

    // �������� ������ ��� �������
    // # ������ ������� ������������� �� ������ �������.
    std::set< std::string >  event;
    // ��������� ������� �� �����
    // # � ����� default ����� ������ �� ���������.
    typelib::file::listFolder( &event, path );
    assert( !event.empty()
        && "��� ������� �� ������� �� ������ �������."
           " ���������� ����� �� ����� ���� ������." );
    assert( (event.find( "default" ) != event.cend())
        && "�� ������ ������ ��� ������� 'default'."
           " ����� ���������� �������� ��� ������������ �������." );

    // �������� ������� �� ������� �� �����
    for (auto etr = event.cbegin(); etr != event.cend(); ++etr) {
        const uidEvent_t& e = *etr;
        // @todo fine ��������� ������������ UID �������.
        if ( boost::starts_with( e, "-" ) ) {
            // �����, ������������ �� '-', ����������
            continue;
        }

#ifdef _DEBUG
        std::cout << "\n�������������� ������ ��� ������� '" << e << "'\n";
#endif

        // ������ ��� ����������� ������
        CL_SpriteDescription ds;
        std::set< std::string >  frame;
        std::string pathEvent = path + "/" + e;
        typelib::file::listFile( &frame, pathEvent, "png" );
        typelib::file::listFile( &frame, pathEvent, "jpg" );
        assert( !frame.empty()
            && "��� ������� �� ������� �� ������ ������. "
               " ���������� ����� �� ����� ���� ������." );
        for (auto ftr = frame.cbegin(); ftr != frame.cend(); ++ftr) {
            const std::string& f = *ftr;
            const std::string pathFrame = pathEvent + "/" + f;
            const auto image = mManagerSprite->frame( pathFrame );
            ds.add_frame( *image );
        }

        // ��� ���. ����� ��� ������� 'e'
        std::unique_ptr< CL_Sprite >  sprite(
            new CL_Sprite( w->visual()->get_gc(),  ds )
        );

        // @todo ������������� ������.

        // ������ ��������� ��� ������� - �� ������
        const int cx = sprite->get_width()  / 2;
        const int cy = sprite->get_height() / 2;
        sprite->set_alignment( origin_center );

        // ����� �������
        // # ��������� ������������ ������� �������.
        const auto nvs = needVisualSize();
        float fixSX, fixSY;
        sprite->get_scale( fixSX, fixSY );
        const typelib::size2_t  scale(
            nvs.x / static_cast< float >( sprite->get_width()  ) * fixSX,
            nvs.y / static_cast< float >( sprite->get_height() ) * fixSY
        );
        sprite->set_scale( scale.x, scale.y );


        sprite->update();


        // ���������� ��������� ������
        addSprite( e,  std::move( sprite ) );

#ifdef _DEBUG
        std::cout << "������ ��� ������� '" << e << "' ������.\n";
#endif

    } // for (auto etr = event.cbegin(); ...
}

    
    
    
void
VIncarnate::addSprite( const uidEvent_t&  e,  std::unique_ptr< CL_Sprite >  s ) {

    assert( (mSprite->find( e ) == mSprite->end())
        && "����� ������� ��� ����. ��������� ���������." );

    mSprite->insert( std::make_pair( e,  std::move( s ) ) );
}




void VIncarnate::load(
    std::shared_ptr< World >  w,
    const std::string&        kind,
    const std::string&        name
) {
    const std::string path = PATH_MEDIA + "/" + kind + "/" + name;
    addSprite( w, path );
}


} // matchn
