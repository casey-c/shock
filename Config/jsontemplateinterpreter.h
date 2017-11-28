#ifndef JSONTEMPLATEINTERPRETER_H
#define JSONTEMPLATEINTERPRETER_H

#include "config/jsoninterpreter.h"

class JSONTemplateInterpreter : public JSONInterpreter
{
public:
    JSONTemplateInterpreter();

    bool readFromFile(QString file) override;

    QString getName() {return this->name;}
    QJsonArray getData() {return data;}
};

#endif // JSONTEMPLATEINTERPRETER_H
