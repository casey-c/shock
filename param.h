#ifndef PARAM_H
#define PARAM_H

#include <QString>

class Param
{
public:
    Param();
    QString toString();
private:
    void* data;
    QString name;
};

#endif // PARAM_H
