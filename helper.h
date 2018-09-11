#ifndef HELPER_H
#define HELPER_H

#include "QString"
#include "QList"
#include <math.h>

class Helper
{
public:
    Helper();

    QList<QString> hexList;

    QString decToHex (int) const;
};

#endif // HELPER_H
