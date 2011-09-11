/* (C) Maciej Poleski 2011 */

#ifndef SUBJECT_HXX
#define SUBJECT_HXX

#include <QtCore/QString>
#include <QtCore/QList>

#include "category.hxx"

/**
 * @brief Pojedyńczy przedmiot.
 **/
class Subject
{
public:
    Subject() throw();
    Subject(const QString &name) throw();

    void setName(const QString &name) throw();

    void insertCategory(const Category &category) throw();

    const QList<Category> & getCategories() const throw();

private:
    QString m_subjectName;
    QList<Category> m_categories;
};

#endif // SUBJECT_HXX
