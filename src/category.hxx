/* (C) Maciej Poleski 2011 */

#ifndef CATEGORY_HXX
#define CATEGORY_HXX

#include <QtCore/QString>
#include <QtCore/QList>

#include "group.hxx"

/**
 * @brief Pojedyńcza kategoria w ramach przedmiotu. Np. Ćwiczenia.
 **/
class Category
{
public:
    Category() throw();
    Category(const QString &name) throw();

    void setName(const QString &name) throw();

    void insertGroup(const Group &group) throw();

    const QList<Group> & getGroups() const throw();

    bool operator==(const Category &category) const throw();

private:
    QString m_categoryName;
    QList<Group> m_groups;
};

#endif // CATEGORY_HXX
