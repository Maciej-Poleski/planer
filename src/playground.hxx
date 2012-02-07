/* (C) Maciej Poleski 2011 */

#ifndef PLAYGROUND_HXX
#define PLAYGROUND_HXX

#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QList>

#include "subject.hxx"
#include "calendar.hxx"

/**
 * @brief Główna klasa. Tutaj będzie miało miejsce składowanie i obliczanie danych.
 **/
class Playground
{
public:
    Playground() throw();

    void loadConfiguration() throw();

    void loadSubjects() throw();

    quint64 getPossibleConfigurationsCount() const throw();

private:
    QSet<QString> m_subjectsFiles;
    QList<Subject> m_subjects;
    Calendar m_referenceCalendar;
};

#endif // PLAYGROUND_HXX
