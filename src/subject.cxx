/* (C) Maciej Poleski 2011 */

#include "subject.hxx"

#include <algorithm>

#include "category.hxx"
#include "group.hxx"
#include "slot.hxx"

using namespace Wt::Dbo;

Subject::Subject() throw()
{

}

Subject::Subject(const QString &name) throw() : m_subjectName(name.toStdString())
{

}

void Subject::setName(const QString &name) throw()
{
    if(m_subjectName != name.toStdString()) {
        m_subjectName = name.toStdString();
        emit nameChanged();
    }
}

void Subject::insertCategory(ptr<Category> category) throw()
{
    m_categories.insert(category);
    category.modify()->setParent(this);
    emit categoryInserted(category);
}

void Subject::removeCategory(ptr< Category > category) throw()
{
    m_categories.erase(category);
    emit categoryRemoved(category);
}

const QString Subject::name() const throw()
{
    return QString::fromStdString(m_subjectName);
}

#include "moc_subject.cpp"
