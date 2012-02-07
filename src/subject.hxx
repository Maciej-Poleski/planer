/* (C) Maciej Poleski 2011 */

#ifndef SUBJECT_HXX
#define SUBJECT_HXX

#include <vector>
#include <string>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <Wt/Dbo/Dbo>

class Category;

/**
 * @brief Pojedyńczy przedmiot.
 **/
class Subject : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Subject)

    friend Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::iterator begin(Subject &subject) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::iterator end(Subject &subject) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::const_iterator begin(const Subject &subject) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::const_iterator end(const Subject &subject) throw();

public:
    Subject() throw();
    Subject(const QString &name) throw();

    const QString name() const throw();

    template<class Action>
    void persist(Action &a);

signals:
    void nameChanged();
    void categoryInserted(Wt::Dbo::ptr<Category> category);
    void categoryRemoved(Wt::Dbo::ptr<Category> category);

public slots:
    void setName(const QString &name) throw();
    void insertCategory(Wt::Dbo::ptr<Category> category) throw();
    void removeCategory(Wt::Dbo::ptr<Category> category) throw();

private:
    std::string m_subjectName;
    Wt::Dbo::collection<Wt::Dbo::ptr<Category>> m_categories;
};

template<class Action>
inline void Subject::persist(Action &a)
{
    using namespace Wt::Dbo;
    field(a, m_subjectName, "subject_name");

    hasMany(a, m_categories, ManyToOne, "subject");
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::iterator begin(Subject &subject) throw()
{
    return subject.m_categories.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::const_iterator begin(const Subject &subject) throw()
{
    return subject.m_categories.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::iterator end(Subject &subject) throw()
{
    return subject.m_categories.end();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Category>>::const_iterator end(const Subject &subject) throw()
{
    return subject.m_categories.end();
}
#endif // SUBJECT_HXX
