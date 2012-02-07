#include <boost/test/unit_test.hpp>

#include "calendar.hxx"

#include <QtCore/QByteArray>
#include <QtCore/QBuffer>

#include "slot.hxx"

BOOST_AUTO_TEST_CASE(calendar_test)
{
    QByteArray buffer("xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "-----\n"
                      "-----\n"
                      "-----\n"
                      "-----\n"
                      "-----\n"
                      "-----\n"
                      "-----\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxxxx\n"
                      "xxx-x\n"
                     );
    QBuffer ioDevice(&buffer);
    Calendar calendar(ioDevice);

    BOOST_CHECK(calendar(Slot(Slot::Monday,6)));
    BOOST_CHECK(calendar(Slot(Slot::Friday,6)));
    BOOST_CHECK(calendar(Slot(Slot::Thursday,7))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,8))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,9))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,10))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,11))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,12))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,13))==false);
    BOOST_CHECK(calendar(Slot(Slot::Monday,14)));
    BOOST_CHECK(calendar(Slot(Slot::Monday,15)));
    BOOST_CHECK(calendar(Slot(Slot::Monday,15)));
    BOOST_CHECK(calendar(Slot(Slot::Thursday,23))==false);



}
