/* (C) Maciej Poleski 2011 */

#include "slot.hxx"

Slot::Slot(Slot::Day day, quint8 hour) throw() : m_day(day), m_hour(hour)
{

}

Slot::Slot(quint8 day, quint8 hour) throw() : m_day(day), m_hour(hour)
{

}

quint8 Slot::day() const throw()
{
    return m_day;
}

quint8 Slot::hour() const throw()
{
    return m_hour;
}

bool Slot::operator==(const Slot &slot) const throw()
{
    return m_day == slot.m_day && m_hour == slot.m_hour;
}
