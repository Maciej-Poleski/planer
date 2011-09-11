#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>

#include <cstdio>

#include "playground.hxx"

int main(int argc,char**argv)
{
    QCoreApplication app(argc,argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    Playground playground;
    QTextStream out(stdout);

    out<<playground.getPossibleConfigurationsCount()<<"\n";

    return 0;
}