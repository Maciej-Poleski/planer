/* (C) Maciej Poleski 2011 */

#ifndef SLOT_HXX
#define SLOT_HXX

#include <QtCore/QtGlobal>

/**
 * @brief Pojedyńczy "slot" w planie lekcji. Konkretna godzina w konkretnym dniu.
 **/
class Slot
{
public:
    enum Day {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday
    };

    Slot(Day day, quint8 hour) throw();
    Slot(quint8 day,quint8 hour) throw();

    quint8 day() const throw();
    quint8 hour() const throw();

    bool operator==(const Slot& slot) const throw();

private:
    quint8 m_day;
    quint8 m_hour;
};

#endif // SLOT_HXX
