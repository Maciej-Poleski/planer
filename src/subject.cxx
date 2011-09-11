/* (C) Maciej Poleski 2011 */

#include "subject.hxx"

Subject::Subject() throw()
{

}

Subject::Subject(const QString &name) throw() : m_subjectName(name)
{

}

void Subject::setName(const QString &name) throw()
{
    m_subjectName = name;
}

void Subject::insertCategory(const Category &category) throw()
{
    m_categories.removeOne(category);
    m_categories.append(category);
}

const QList< Category >& Subject::getCategories() const throw()
{
    return m_categories;
}
