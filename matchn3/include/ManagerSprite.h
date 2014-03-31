#pragma once

#include "configure.h"


namespace matchn {


/**
* ��������� ��������� ����.
*/
class ManagerSprite {
public:
    /**
    * ��������� ��������� ������ ��������.
    */
    typedef boost::unordered_map<
        std::string,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;




    ManagerSprite();




public:
    virtual ~ManagerSprite();




    /**
    * @return ��������� �� ����������� �� ���������� ���� �����
    *         � ������� ClanLib.
    *         nullptr, ���� ����� ��������� �� �������.
    */
    CL_PixelBuffer* frame( const std::string& path );




private:
    knownFrame_t  mKnownFrame;
};


} // matchn
