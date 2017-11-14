#include "jsontemplateinterpreter.h"

JSONTemplateInterpreter::JSONTemplateInterpreter()
{

}


bool JSONTemplateInterpreter::readFromFile(QString file){

    data = new QList<QPair<QString,QString>*>;

    QFile loadFile(file);

    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning(("Couldn't open JSON file " + file).toLatin1().data());
        return false;
    }

    QByteArray jsonByteArray = loadFile.readAll();

    loadFile.close();

    QJsonDocument loadDoc(QJsonDocument::fromJson(jsonByteArray));
    //read(loadDoc.object());
    QJsonObject dat = loadDoc.object();
    name = dat["name"].toString();

    QJsonArray readData = dat["data"].toArray();
    for(int i = 0; i < readData.size(); ++i){
        QJsonObject param = readData[i].toObject();
        QStringList all = param.keys();
        for(QStringList::iterator itr = all.begin(); itr != all.end(); ++itr){
            qDebug() << "key" << *itr << "val" << param[*itr].toString();
            QPair<QString,QString>* p = new QPair<QString,QString>(*itr,param[*itr].toString());
            data->append(p);
        }
        /*
        for(QJsonObject::iterator itr = param.begin(); itr != param.end(); ++itr){
            qDebug() << "Keys" << param.keys();
            //QPair<QString,QString>* temp = new QPair<QString,QString>;
            //temp->first = param;
            //temp->second = param[temp->first].toString();
            //data.append(temp);
        }*/
    }

    return true;
}
