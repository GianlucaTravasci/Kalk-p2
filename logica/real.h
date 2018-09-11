#ifndef REAL_H
#define REAL_H

#include "QString"
#include "exce_kalk.h"

class Real
{
private:
    double rVal;

public:
    static const QString regExp;
    Real(double = 0);
    virtual ~Real() = default;

    void setR(double);
    double getR() const;

    virtual void string(QString);

    virtual Real& operator+(const Real&) const;
    virtual Real& operator-(const Real&) const;
    virtual Real& operator*(const Real&) const;
    virtual Real& operator/(const Real&) const;

    virtual QString getString(unsigned int = 2) const;
};

#endif // REAL_H
