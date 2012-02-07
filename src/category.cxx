/* (C) Maciej Poleski 2011-2012 */

#include "category.hxx"

#include <algorithm>

#include "group.hxx"
#include "slot.hxx"

using namespace Wt::Dbo;

Category::Category() throw()
{

}

Category::Category(const QString &name) throw() : m_categoryName(name.toStdString())
{

}

void Category::setName(const QString &name) throw()
{
    if(m_categoryName != name.toStdString()) {
        m_categoryName = name.toStdString();
        emit nameChanged();
    }
}

void Category::insertGroup(ptr<Group> group) throw()
{
    m_groups.insert(group);
    group.modify()->setParent(this);
    emit groupInserted(group);
}

void Category::removeGroup(ptr< Group > group) throw()
{
    m_groups.erase(group);
    emit groupRemoved(group);
}

const QString Category::name() const throw()
{
    return QString::fromStdString(m_categoryName);
}

#include "moc_category.cpp"