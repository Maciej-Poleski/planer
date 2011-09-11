/* (C) Maciej Poleski 2011 */

#include "category.hxx"

Category::Category() throw()
{

}

Category::Category(const QString &name) throw() : m_categoryName(name)
{

}

void Category::setName(const QString &name) throw()
{
    m_categoryName = name;
}

void Category::insertGroup(const Group &group) throw()
{
    m_groups.removeOne(group);
    m_groups.append(group);
}

const QList< Group >& Category::getGroups() const throw()
{
    return m_groups;
}

bool Category::operator==(const Category &category) const throw()
{
    if(m_categoryName != category.m_categoryName)
        return false;

    if(m_groups.size() != category.m_groups.size())
        return false;

    foreach(const Group & group, m_groups) {
        if(category.m_groups.contains(group) == false)
            return false;
    }

    return true;
}
