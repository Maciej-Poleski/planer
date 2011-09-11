/* (C) Maciej Poleski 2011 */

#ifndef GROUP_HXX
#define GROUP_HXX

#include <QtCore/QList>
#include <QtCore/QString>

#include "slot.hxx"

/**
 * @brief Pojedyńcza grupa w ramach danej kategori danego przedmiotu.
 **/
class Group
{
public:
    Group() throw();
    Group(const QString &name) throw();

    void setName(const QString &name) throw();
    void insertSlot(const Slot &slot) throw();

    const QList<Slot> & getSlots() const throw();

    bool operator==(const Group &group) const throw();

private:
    QString m_groupName;
    QList<Slot> m_slotsTaken;
};

#endif // GROUP_HXX
