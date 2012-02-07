#include <QtGui/QApplication>

#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtCore/QTemporaryFile>

#include "playground.hxx"
#include "groupwidget.hxx"
#include "group.hxx"
#include "category.hxx"
#include "categorywidget.hxx"
#include "subject.hxx"
#include "subjectwidget.hxx"
#include "slot.hxx"

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>

using namespace Wt::Dbo;

int main(int argc,char**argv)
{
    QApplication app(argc,argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QTemporaryFile tempFile;

    Session session;
    Wt::Dbo::backend::Sqlite3 connection(tempFile.fileName().toStdString());
    session.setConnection(connection);

    session.mapClass<Slot>("slot");
    session.mapClass<Group>("group");
    session.mapClass<Category>("category");
    session.mapClass<Subject>("subject");

    session.createTables();

    Transaction transaction(session);

    ptr<Subject> s=session.add(new Subject());
    GUI::SubjectWidget *widget=new GUI::SubjectWidget(s);
    widget->show();

    int r=app.exec();

    transaction.commit();

    return r;

    Playground playground;
    QTextStream out(stdout);

    out<<playground.getPossibleConfigurationsCount()<<"\n";

    return 0;
}