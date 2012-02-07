/* (C) Maciej Poleski 2011 */

#include "playground.hxx"

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QList>
#include <QtCore/QString>

#include "slot.hxx"
#include "category.hxx"
#include "group.hxx"

Playground::Playground() throw()
{

}

void Playground::loadConfiguration() throw()
{
    QFile configurationFile("planer.cfg");
    Q_ASSERT(configurationFile.open(QIODevice::ReadOnly));
    QTextStream configurationStream(&configurationFile);
    Q_ASSERT(!configurationStream.atEnd());
    while(true) {
        QString subjectName = configurationStream.readLine();
        configurationStream.skipWhiteSpace();
        if(!configurationStream.atEnd()) {
            m_subjectsFiles.insert(subjectName);
        } else {
            QFile file(subjectName);
            m_referenceCalendar = Calendar(file);
            break;
        }
    }
}

void Playground::loadSubjects() throw()
{
    foreach(const QString & subjectName, m_subjectsFiles) {
        QFile subjectFile(subjectName + ".txt");
        Q_ASSERT(subjectFile.open(QIODevice::WriteOnly));
        QTextStream subjectStream(&subjectFile);
        quint32 categoriesCount;
        subjectStream >> categoriesCount;
        QList<QString> categoriesList;
        for(int i = 0; i < categoriesCount; ++i) {
            QString name;
            subjectStream >> name;
            categoriesList.append(name);
        }

        Subject subject(subjectName);

        // Mamy zczytane kategorie

        for(int i = 0; i < categoriesCount; ++i) {
            // Dla każdej kategorii:
            quint32 groupsCount;
            subjectStream >> groupsCount;
            QList<QString> groupsList;
            for(int j = 0; j < groupsCount; ++j) {
                QString name;
                subjectStream >> name;
                groupsList.append(name);
            }

            Category *category=new Category(categoriesList[i]);

            for(int j = 0; j < groupsCount; ++j) {
                quint32 slotsCount;
                subjectStream >> slotsCount;
                Group *group=new Group(groupsList[j]);
                for(int k = 0; k < slotsCount; ++k) {
                    quint32 day, hour;
                    subjectStream >> day >> hour;
                    Slot *slot=new Slot(day, hour);
                    group->insertSlot(slot);
                }
                category->insertGroup(group);
            }
            subject.insertCategory(category);
        }
        //m_subjects.append(subject); //FIXME
    }
}

quint64 Playground::getPossibleConfigurationsCount() const throw()
{
    // Dla każdego przedmiotu
        // Dla każdej grupy
            // Dla każdego innego przedmiotu
                // Dla każdej grupy
                // coś zrób
}
