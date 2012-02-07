/* (C) Maciej Poleski 2011 */

#ifndef SLOT_HXX
#define SLOT_HXX

#include <QtCore/QtGlobal>
#include <QtCore/QObject>

#include <Wt/Dbo/Dbo>

#include "group.hxx"

/**
 * @brief Pojedynczy "slot" w planie lekcji. Konkretna godzina w konkretnym dniu.
 **/
class Slot : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Slot)
public:
enum Day :
    quint8 {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday
    };

    Slot() throw();
    Slot(Day day, quint8 hour) throw();
    Slot(quint8 day, quint8 hour) throw();

    quint8 day() const throw();
    quint8 hour() const throw();

    const bool operator==(const Slot &slot) const throw();

    template<class Action>
    void persist(Action &a);

public slots:
    void setDay(Day day) throw();
    void setDay(quint8 day) throw();
    void setHour(quint8 hour) throw();

signals:
    void changed() const;

private:
    Wt::Dbo::ptr<Group> p_group;
    qint16 m_day;
    qint16 m_hour;
};

template<class Action>
inline void Slot::persist(Action &a)
{
    Wt::Dbo::field(a, m_day, "day");
    Wt::Dbo::field(a, m_hour, "hour");

    Wt::Dbo::belongsTo(a, p_group, "group");
}

#endif // SLOT_HXX
