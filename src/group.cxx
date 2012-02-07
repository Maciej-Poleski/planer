/* (C) Maciej Poleski 2011 */

#include "group.hxx"

#include <algorithm>

#include "slot.hxx"

Group::Group() throw()
{

}

Group::Group(const QString &name) throw() : m_groupName(name.toStdString())
{

}

void Group::setName(const QString &name) throw()
{
    if(m_groupName != name.toStdString()) {
        m_groupName = name.toStdString();
        emit nameChanged();
    }
}

void Group::insertSlot(Wt::Dbo::ptr<Slot> slot) throw()
{
    m_slotsTaken.insert(slot);
    slot.modify()->setParent(this);
    emit slotInserted(slot);
}

void Group::removeSlot(Wt::Dbo::ptr< Slot > slot) throw()
{
    m_slotsTaken.erase(slot);
    emit slotRemoved(slot);
}

const QString Group::getName() const throw()
{
    return QString::fromStdString(m_groupName);
}

#include "moc_group.cpp"
