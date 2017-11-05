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
    enum type{};
};

#endif // PARAM_H
