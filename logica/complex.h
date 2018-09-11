#ifndef COMPLEX_H
#define COMPLEX_H

#include <QString>
#include <QStringList>
#include <QRegExp>
#include <cmath>
#include "real.h"
#include "exce_kalk.h"

class Complex : public Real
{
private:
    double iVal;

public:
    static const QString regExp;
    Complex(QString);
    Complex(double = 0, double = 0);
    ~Complex() = default;

    void setI(double);
    double getI() const;
    void inverseI();

    virtual Complex& conjugate() const;
    virtual double norm() const;
    virtual Complex& inverse() const;

    void string(QString);

    Complex& operator+(const Real&) const;
    Complex& operator-(const Real&) const;
    Complex& operator*(const Real&) const;
    Complex& operator/(const Real&) const;

    QString getString(unsigned int = 2) const override;
};

#endif // COMPLEX_H
