/* (C) Maciej Poleski 2011 */

#ifndef CALENDAR_HXX
#define CALENDAR_HXX

#include <QtCore/QtGlobal>

class QIODevice;
class Subject;

class Slot;
class Group;

class Calendar
{

public:
    Calendar() throw();

    Calendar(QIODevice &inputFile) throw();

    bool &operator()(const Slot &slot) throw();

    bool insertGroup(const Group &group) throw();

private:
    bool m_calendar[5][24];
};

#endif // CALENDAR_HXX
