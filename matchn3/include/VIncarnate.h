#pragma once

#include "GE.h"


namespace matchn {


class World;
class ManagerSprite;


/**
* ������, ������������������ � ���������� ������ (� ����).
* # � �������� ���. ������ ������������ ClanLib.
*
* @see http://clanlib.org
*/
class VIncarnate {
public:
    /**
    * ������� ������������� �� ��������.
    * ������ ������� ����� ����� ���� ������ (����� ��� ������������).
    */
    typedef std::map<
        uidEvent_t,
        std::unique_ptr< CL_Sprite >
    > sprite_t;




protected:
    VIncarnate(
        const typelib::coord2Int_t&  coord,
        int  order
    );



    virtual ~VIncarnate();




public:
    /**
    * ������������� �������.
    */
    virtual void draw( std::shared_ptr< World > ) const = 0;




    inline sprite_t const* sprite() const {
        return mSprite.get();
    }




    /**
    * @return ������ ��� ������� 'E'.
    *         nullptr, ���� ������ ��� ������� �� ������.
    */
    CL_Sprite* sprite( const uidEvent_t& ) const;




    /**
    * ���������� ������ ��� ��������� �������.
    */
    void drawSprite( std::shared_ptr< World >, const uidEvent_t& ) const;




    /**
    * ��������� �������, ������� �� �� ������� �� 'path'.
    *
    * # ������ �������� ������������� �� ������ ������� - ��. ����������
    *   �������� � ManagerEvent::uid< T >().
    * # ������ �������� ������ ���� ������ �������.
    */
    void addSprite( std::shared_ptr< World >,  const std::string&  path );




    /**
    * ��������� ������ ��� �������.
    */
    void addSprite( const uidEvent_t&,  std::unique_ptr< CL_Sprite > );




    /**
    * @return ������ ������ � ���, ������� ����� �������� �� ������.
    *         ������ ����� �������� ��� ���� ������.
    */
    virtual typelib::size2Int_t needVisualSize() const = 0;




    /**
    * @return ���������� ������.
    *
    * # ������� � ����������, ����� ����� �������� ������ �� ��������� ����.
    */
    template< typename T1, typename T2 >
    inline void visualCoord( T1 x, T1 y ) {
        visualCoord( coord2Int_t( x, y ) );
    };


    inline const typelib::coord2Int_t& visualCoord() const {
        return mCoord;
    };


    inline void visualCoord( const typelib::coord2Int_t& c ) {
        mCoord = c;
    };




    /**
    * @return ���� �������� �������� � ��������.
    */
    template< typename T >
    inline void visualRotation( T a ) {
        mRotation = static_cast< int >( a );
    };


    template< typename T >
    inline T visualRotation() const {
        return static_cast< T >( mRotation );
    };


    inline int visualRotation() const {
        return mRotation;
    };




    /**
    * @return ������������ �������� [0.0; 1.0].
    */
    template< typename T >
    inline void visualAlpha( T a ) {
        mAlpha = static_cast< float >( a );
    };


    inline float visualAlpha() const {
        return mAlpha;
    };




    /**
    * @return ������� ��������� ��������. ������ - ������.
    */
    inline int visualOrder() const {
        return mOrder;
    }




    void load(
        std::shared_ptr< World >,
        const std::string&  kind,
        const std::string&  name
    );




private:
    typelib::coord2Int_t  mCoord;
    int                   mRotation;
    float                 mAlpha;

    /**
    * ������� ��������� ��������. ������ - ������.
    */
    int  mOrder;

    /**
    * ������� ��������, ��������������� �� ��������.
    */
    std::unique_ptr< sprite_t >  mSprite;

    static std::unique_ptr< ManagerSprite >  mManagerSprite;
};



} // matchn
