#include <QRegExpValidator>
#include "real.h"

const QString Real::regExp = "^(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)$";

Real::Real(double initVal) {
    this->setR(initVal);
}

void Real::setR(double valToSet) {
    this->rVal = valToSet;
}

double Real::getR() const {
    return this->rVal;
}

void Real::string(QString str) {
    str = str.simplified().toLower();
    str = str.replace( " ", "" );

    // Inizializziamo un validator per verificare il pattern
    QRegExpValidator validator;
    QRegExp rexp(regExp);
    validator.setRegExp(rexp);
    int pos = 0;
    if (validator.validate(str, pos) != QRegExpValidator::State::Acceptable) {
        throw exce_kalk(str.prepend("Formato numero non corretto\n").toStdString());
        return;
    }

    setR(str.toDouble());
}

Real& Real::operator+(const Real& b) const {
    Real* res = new Real();
    res->rVal = this->rVal + b.rVal;
    return *res;
}
Real& Real::operator-(const Real& b) const {
    Real* res = new Real();
    res->rVal = this->rVal - b.rVal;
    return *res;
}
Real& Real::operator*(const Real& b) const {
    Real* res = new Real();
    res->rVal = this->rVal * b.rVal;
    return *res;
}
Real& Real::operator/(const Real& b) const {
    Real* res = new Real();
    if (b.rVal == 0)
        throw exce_kalk("Errore divisione per 0");
    res->rVal = this->rVal / b.rVal;
    return *res;
}

QString Real::getString(unsigned int precision) const {
    return QString::number(this->rVal, 'f', precision);
}
