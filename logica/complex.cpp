#include <QRegExpValidator>
#include "complex.h"

const QString Complex::regExp = "^(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*),(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)i$";

Complex::Complex(QString str)
{
    string(str);
}

Complex::Complex(double rValIn, double iValIn)
{
    this->setR(rValIn);
    this->setI(iValIn);
}

void Complex::setI(double iVal)  {
    this->iVal = iVal;
}

double Complex::getI() const {
    return this->iVal;
}

void Complex::inverseI() {
    this->iVal *= -1;
}

Complex& Complex::conjugate() const {
    Complex* res = new Complex();
    *res = *this;
    res->inverseI();
    return *res;
}

double Complex::norm() const {
    double ret;
    if (pow(getR(),2) + pow(getI(),2) < 0)
        throw exce_kalk("Errore radice negativa");
    ret = sqrt(pow(getR(),2) + pow(getI(),2));
    return ret;
}

Complex& Complex::inverse() const {
    const Complex* norma = new Complex(pow(this->norm(),2));
    Complex* ret;
    ret = &(*this / *norma);
    return *ret;
}

void Complex::string(QString str) {
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

    // Controllo il formato "2,2"
    QStringList list = str.split(',');
    if (list.size() == 2) {
        setR(list[0].toDouble());
        list[1] = list[1].replace("i", "");
        setI(list[1].toDouble());
    }else{
        throw exce_kalk(str.prepend("Qualcosa è andato storto con la conversione a complesso di:\n").toStdString());
    }
}

Complex& Complex::operator+(const Real& elem) const {
    const Complex& b = static_cast<const Complex&>(elem);
    Complex* res = new Complex();
    res->setR(this->getR() + b.getR());
    res->setI(this->getI() + b.getI());
    return *res;
}
Complex& Complex::operator-(const Real& elem) const {
    const Complex& b = static_cast<const Complex&>(elem);
    Complex* res = new Complex();
    res->setR(this->getR() - b.getR());
    res->setI(this->getI() - b.getI());
    return *res;
}
Complex& Complex::operator*(const Real& elem) const {
    const Complex& b = static_cast<const Complex&>(elem);
    Complex* res = new Complex();
    res->setR((this->getR() * b.getR()) -
                  (this->getI() * b.getI()));
    res->setI((this->getR() * b.getI()) +
                 (this->getI() * b.getR()));
    return *res;
}
Complex& Complex::operator/(const Real& elem) const {
    const Complex& b = static_cast<const Complex&>(elem);
    Complex inverse, denominatoreComplex;
    inverse = b;
    inverse.inverseI();
    denominatoreComplex = inverse * b;
    double denominatore = denominatoreComplex.getR();
    double rPart;
    double iPart;
    if (denominatore == 0)
        throw exce_kalk("Errore divisione per 0");
    inverse = *this * inverse;
    rPart = inverse.getR() / denominatore;
    iPart = inverse.getI() / denominatore;
    Complex* res = new Complex(rPart, iPart);
    return *res;
}

QString Complex::getString(unsigned int prec) const {
    return QString::number(this->getR(), 'f', prec) + ", " +
            QString::number(this->getI(), 'f', prec) + "i";
}
