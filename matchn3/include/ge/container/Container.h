#pragma once

#include "../../Incarnate.h"
#include "drop-container-event.h"
#include "wait-container-event.h"


namespace matchn {


class World;


/**
* ��������� (��� ����� ������ �������).
*/
class Container :
    public Incarnate
{
protected:
    Container(
        std::shared_ptr< World >,
        const uidContainer_t&        name,
        const typelib::coord2Int_t&  logicCoord
    );




public:
    static std::shared_ptr< Container >  valueOf(
        std::shared_ptr< World >,
        const uidContainer_t&        name,
        const typelib::coord2Int_t&  logicCoord
    );




    virtual ~Container();




    /**
    * @virtual VIncarnate
    */
    virtual void draw( std::shared_ptr< World > ) const;




    inline const uidContainer_t& name() const {
        return mName;
    }




    /**
    * @virtual VIncarnate
    */
    virtual typelib::size2Int_t needVisualSize() const;




    /**
    * @return ��������� ���������.
    */
    static uidContainer_t nextRandom();




    /**
    * @return ���������� ��������� �����������.
    *
    * # ������������ �� ����������� ����� 'media/container'.
    */
    static size_t countAvailable();




protected:
    /**
    * �������� ���������� ��� ����������� �������������.
    */
    const uidContainer_t  mName;


    /**
    * ��� ��� ���������� �������.
    */
    static size_t countAvailable_;
};


} // matchn
