/* (C) Maciej Poleski 2011-2012 */

#ifndef CATEGORY_HXX
#define CATEGORY_HXX

#include <vector>
#include <string>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <Wt/Dbo/Dbo>

#include "subject.hxx"

class Group;

/**
 * @brief Pojedyńcza kategoria w ramach przedmiotu. Np. Ćwiczenia.
 **/
class Category : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Category)

    friend Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::iterator begin(Category &category) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::iterator end(Category &category) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::const_iterator begin(const Category &category) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::const_iterator end(const Category &category) throw();

public:
    Category() throw();
    Category(const QString &name) throw();

    const QString name() const throw();

    template<class Action>
    void persist(Action& a);

signals:
    void nameChanged();
    void groupInserted(Wt::Dbo::ptr<Group> group);
    void groupRemoved(Wt::Dbo::ptr<Group> group);

public slots:
    void setName(const QString &name) throw();
    void insertGroup(Wt::Dbo::ptr<Group> group) throw();
    void removeGroup(Wt::Dbo::ptr<Group> group) throw();

private:
    std::string m_categoryName;
    Wt::Dbo::ptr<Subject> p_subject;
    Wt::Dbo::collection<Wt::Dbo::ptr<Group>> m_groups;
};

template<class Action>
inline void Category::persist(Action &a)
{
    using namespace Wt::Dbo;
    field(a,m_categoryName,"name");

    belongsTo(a,p_subject,"subject");

    hasMany(a,m_groups,ManyToOne,"category");
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::iterator begin(Category &category) throw()
{
    return category.m_groups.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::const_iterator begin(const Category &category) throw()
{
    return category.m_groups.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::iterator end(Category &category) throw()
{
    return category.m_groups.end();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Group>>::const_iterator end(const Category &category) throw()
{
    return category.m_groups.end();
}

#endif // CATEGORY_HXX
