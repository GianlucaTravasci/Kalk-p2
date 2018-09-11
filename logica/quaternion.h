#ifndef QUATERNION_H
#define QUATERNION_H

#include <QString>
#include <QStringList>
#include <cmath>
#include "complex.h"
#include "exce_kalk.h"

class Quaternion : public Complex
{
private:
    double jVal;
    double kVal;

public:
    static const QString regExp;
    Quaternion(QString);
    Quaternion(double = 0, double = 0, double = 0, double = 0);
    ~Quaternion() = default;

    void setJ(double);
    double getJ() const;
    void setK(double);
    double getK() const;
    void inverseJ();
    void inverseK();

    Quaternion& conjugate() const;
    double norm() const;
    Quaternion& inverse() const;

    void string(QString);

    Quaternion& operator+(const Real&) const override;
    Quaternion& operator-(const Real&) const override;
    Quaternion& operator*(const Real&) const override;
    Quaternion& operator/(const Real&) const override;

    QString getString(unsigned int = 2) const override;
};

#endif // QUATERNION_H
