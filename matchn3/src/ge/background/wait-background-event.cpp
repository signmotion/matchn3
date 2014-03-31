#include "../../../include/stdafx.h"
#include "../../../include/ge/background/Background.h"


namespace matchn {


void
WaitBackground::operator()() {
    // # � ������ ���������� ���� ��������� ������ ������.
    for ( ; !mElement.expired() && world(); ) {
        Console::instance() << "\n(WaitBackground)\n";

        // #! ������ ���� boost::sleep(), ���� ����� ���������
        //    ���������� interrupt() ��� ���������� ������-��������
        boost::this_thread::sleep( TWO_SECOND );
        boost::this_thread::yield();

    } // for ( ; ; )

    Console::instance() << "\n(WaitBackground closed)\n";
}


} // matchn
