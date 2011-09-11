/* (C) Maciej Poleski 2011 */

#include "calendar.hxx"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtCore/QString>

#include "slot.hxx"
#include "group.hxx"

Calendar::Calendar() throw()
{
    for(quint8 i = 0; i < 5; ++i)
        for(quint8 j = 0; j < 24; ++j)
            m_calendar[i][j] = false;
}

Calendar::Calendar(QIODevice &inputFile) throw()
{
    Q_ASSERT(inputFile.open(QIODevice::ReadOnly));
    QTextStream inputStream(&inputFile);
    for(quint8 hour = 0; hour < 24; ++hour) {
        for(quint8 day = 0; day < 5; ++day) {
            Q_ASSERT(inputStream.atEnd() == false);
            QChar inputChar;
            inputStream >> inputChar;
            m_calendar[day][hour] = (inputChar == 'x');
        }
        Q_ASSERT(inputStream.atEnd() == false);
        QChar inputChar;
        inputStream >> inputChar;
        Q_ASSERT(inputChar == '\n');
    }
}

bool &Calendar::operator()(const Slot &slot) throw()
{
    return m_calendar[slot.day()][slot.hour()];
}

bool Calendar::insertGroup(const Group &group) throw()
{
    foreach(const Slot & slot, group.getSlots()) {
        if(m_calendar[slot.day()][slot.hour()])
            return false;
    }

    foreach(const Slot & slot, group.getSlots()) {
        m_calendar[slot.day()][slot.hour()] = true;
    }
}
