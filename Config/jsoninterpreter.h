#ifndef JSONINTERPRETER_H
#define JSONINTERPRETER_H

#include <QList>
#include <QPair>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QDebug>

class JSONInterpreter
{
public:
    JSONInterpreter() {}

    virtual bool readFromFile(QString file) = 0;

protected:
    QJsonArray data;
    QString name;
};


#endif // JSONINTERPRETER_H
