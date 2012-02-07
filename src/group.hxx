/* (C) Maciej Poleski 2011 */

#ifndef GROUP_HXX
#define GROUP_HXX

#include <vector>
#include <string>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QPointer>

#include <Wt/Dbo/Dbo>

#include "category.hxx"

class Slot;

/**
 * @brief Pojedyńcza grupa w ramach danej kategori danego przedmiotu.
 **/
class Group : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Group)
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::iterator begin(Group &group) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::iterator end(Group &group) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::const_iterator begin(const Group &group) throw();
    friend Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::const_iterator end(const Group &group) throw();

public:
    explicit Group() throw();
    explicit Group(const QString &name) throw();

    const QString getName() const throw();

    template<class Action>
    void persist(Action& a);

signals:
    void nameChanged();
    void slotInserted(Wt::Dbo::ptr<Slot> slot);
    void slotRemoved(Wt::Dbo::ptr<Slot> slot);

public slots:
    void setName(const QString &name) throw();
    void insertSlot(Wt::Dbo::ptr<Slot> slot) throw();
    void removeSlot(Wt::Dbo::ptr<Slot> slot) throw();

private:
    std::string m_groupName;
    Wt::Dbo::ptr<Category> p_category;
    Wt::Dbo::collection<Wt::Dbo::ptr<Slot>> m_slotsTaken;
};

inline Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::iterator begin(Group &group) throw()
{
    return group.m_slotsTaken.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::iterator end(Group &group) throw()
{
    return group.m_slotsTaken.end();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::const_iterator begin(const Group &group) throw()
{
    return group.m_slotsTaken.begin();
}

inline Wt::Dbo::collection<Wt::Dbo::ptr<Slot>>::const_iterator end(const Group &group) throw()
{
    return group.m_slotsTaken.end();
}

template<class Action>
inline void Group::persist(Action &a)
{
    Wt::Dbo::field(a,m_groupName,"group_name");

    Wt::Dbo::belongsTo(a,p_category,"category");

    Wt::Dbo::hasMany(a,m_slotsTaken,Wt::Dbo::ManyToOne,"group");
}


#endif // GROUP_HXX
