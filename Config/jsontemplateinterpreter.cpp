#include "jsontemplateinterpreter.h"

JSONTemplateInterpreter::JSONTemplateInterpreter()
{

}

// take the json files from disk and load them into memory
bool JSONTemplateInterpreter::readFromFile(QString file){
    QFile loadFile(file);

    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning(("Couldn't open JSON file " + file).toLatin1().data());
        return false;
    }

    QJsonObject dat = QJsonDocument::fromJson(loadFile.readAll()).object();
    loadFile.close();
    name = dat["name"].toString();
    data = dat["data"].toArray();

    return true;
}
