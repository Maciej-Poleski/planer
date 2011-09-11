/* (C) Maciej Poleski 2011 */

#include "group.hxx"

Group::Group() throw()
{

}

Group::Group(const QString &name) throw() : m_groupName(name)
{

}

void Group::setName(const QString &name) throw()
{
    m_groupName = name;
}

void Group::insertSlot(const Slot &slot) throw()
{
    m_slotsTaken.removeOne(slot);
    m_slotsTaken.append(slot);
}

const QList< Slot >& Group::getSlots() const throw()
{
    return m_slotsTaken;
}

bool Group::operator==(const Group &group) const throw()
{
    if(m_groupName != group.m_groupName)
        return false;

    if(m_slotsTaken.size() != group.m_slotsTaken.size())
        return false;

    foreach(const Slot & slot, m_slotsTaken) {
        if(group.m_slotsTaken.contains(slot) == false)
            return false;
    }

    return true;
}
