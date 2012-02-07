/* (C) Maciej Poleski 2011 */

#include "slot.hxx"

Slot::Slot() throw()
{
    // Don't know what to do.
}

Slot::Slot(Slot::Day day, quint8 hour) throw() : m_day(static_cast<quint8>(day)),
    m_hour(hour)
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

void Slot::setDay(Slot::Day day) throw()
{
    setDay(static_cast<quint8>(day));
}

void Slot::setDay(quint8 day) throw()
{
    if(day != m_day) {
        m_day = day;
        emit changed();
    }
}

void Slot::setHour(quint8 hour) throw()
{
    if(hour != m_hour) {
        m_hour = hour;
        emit changed();
    }
}

const bool Slot::operator==(const Slot &slot) const throw()
{
    return m_day == slot.m_day && m_hour == slot.m_hour;
}

#include "moc_slot.cpp"
