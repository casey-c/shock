#ifndef JSONTEMPLATEINTERPRETER_H
#define JSONTEMPLATEINTERPRETER_H

#include "jsoninterpreter.h"

class JSONTemplateInterpreter : public JSONInterpreter
{
public:
    JSONTemplateInterpreter();

    bool readFromFile(QString file) override;

    QString getName() {return this->name;}
    QList<QPair<QString,QString>*>* getData() {return data;}
};

#endif // JSONTEMPLATEINTERPRETER_H
