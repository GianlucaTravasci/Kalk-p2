#include <QRegExpValidator>
#include "quaternion.h"

#include <QDebug>

const QString Quaternion::regExp = "^(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*),(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)i,(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)j,(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)k$";

Quaternion::Quaternion(QString str) {
    string(str);
}

Quaternion::Quaternion(double rValIn, double iValIn, double jValIn, double kValIn)
{
    setR(rValIn);
    setI(iValIn);
    setJ(jValIn);
    setK(kValIn);
}

void Quaternion::setJ(double val) {
    jVal = val;
}

double Quaternion::getJ() const {
    return jVal;
}

void Quaternion::setK(double val) {
    kVal = val;
}

double Quaternion::getK() const {
    return kVal;
}

void Quaternion::inverseJ() {
    jVal *= -1;
}

void Quaternion::inverseK() {
    kVal *= -1;
}

Quaternion& Quaternion::conjugate() const {
    Quaternion* res = new Quaternion();
    *res = *this;
    res->inverseI();
    res->inverseJ();
    res->inverseK();
    return *res;
}

double Quaternion::norm() const {
    if (pow(getR(),2) +
            pow(getI(),2) +
            pow(getJ(),2) +
            pow(getK(),2) < 0)
        throw exce_kalk("Errore radice negativa");
    return sqrt(pow(getR(),2) +
                pow(getI(),2) +
                pow(getJ(),2) +
                pow(getK(),2));
}


Quaternion& Quaternion::inverse() const {
    const Quaternion* norma = new Quaternion(pow(norm(),2));
    Quaternion* ret;
    ret = &(*this / *norma);
    qDebug() << "lol entra";
    delete norma;
    return *ret;
}

void Quaternion::string(QString str) {
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

    // Controllo il formato "2,2,2,2"
    QStringList list = str.split(',');
    if (list.size() == 4) {
        setR(list[0].toDouble());
        list[1] = list[1].replace("i", "");
        setI(list[1].toDouble());
        list[2] = list[2].replace("j", "");
        setJ(list[2].toDouble());
        list[3] = list[3].replace("k", "");
        setK(list[3].toDouble());
    }else{
        throw exce_kalk(str.prepend("\nQualcosa è andato storto con la conversione a quaternion di:\n").prepend(list[1].length()).toStdString());
    }
}

Quaternion& Quaternion::operator+(const Real& elem) const {
    const Quaternion& b = static_cast<const Quaternion&>(elem);
    Quaternion* ret = new Quaternion(
                getR() + b.getR(),
                getI() + b.getI(),
                getJ() + b.getJ(),
                getK() + b.getK()
            );
    return *ret;
}

Quaternion& Quaternion::operator-(const Real& elem) const {
    const Quaternion& b = static_cast<const Quaternion&>(elem);
    Quaternion* ret = new Quaternion(
                getR() - b.getR(),
                getI() - b.getI(),
                getJ() - b.getJ(),
                getK() - b.getK()
            );
    return *ret;
}

Quaternion& Quaternion::operator*(const Real& elem) const {
    const Quaternion& b = static_cast<const Quaternion&>(elem);
    Quaternion* ret = new Quaternion;
    // prodotti normali
    ret->setR((getR() * b.getR()) -
             (getI() * b.getI()) -
             (getJ() * b.getJ()) -
             (getK() * b.getK()));
    // prodotti tra R<>I e J<>K
    ret->setI((getR() * b.getI()) +
             (getI() * b.getR()) +
             (getJ() * b.getK()) -
             (getK() * b.getJ()));
    // prodotti tra R<>J e I<>K
    ret->setJ((getR() * b.getJ()) -
             (getI() * b.getK()) +
             (getJ() * b.getR()) +
             (getK() * b.getI()));
    // prodotti tra R<>K e I<>J
    ret->setK((getR() * b.getK()) +
             (getI() * b.getJ()) -
             (getJ() * b.getI()) +
             (getK() * b.getR()));
    return *ret;
}

Quaternion& Quaternion::operator/(const Real& elem) const {
    const Quaternion& b = static_cast<const Quaternion&>(elem);
    Quaternion* ret = new Quaternion();
    double a1 = getR();
    double b1 = getI();
    double c1 = getJ();
    double d1 = getK();
    double a2 = b.getR();
    double b2 = b.getI();
    double c2 = b.getJ();
    double d2 = b.getK();

    double denominatore = a2*a2 + b2*b2 + c2*c2 + d2*d2;
    if (denominatore == 0)
        throw exce_kalk("Errore divisione per 0");
    // Parte reale -- prodotti normali
    ret->setR( ((a1*a2)+(b1*b2)+(c1*c2)+(d1*d2)) / denominatore);
    // Parte immaginaria I -- prodotti tra R<>I e J<>K
    ret->setI( ((a1*-b2)+(b1*a2)+(c1*d2)+(d1*-c2)) / denominatore);
    // Parte immaginaria J -- prodotti tra R<>J e I<>K
    ret->setJ( ((a1*-c2)+(b1*-d2)+(c1*a2)+(d1*b2)) / denominatore);
    // Parte immaginaria K -- prodotti tra R<>K e I<>J
    ret->setK( ((a1*-d2)+(b1*c2)+(c1*-b2)+(d1*a2)) / denominatore);

    return *ret;
}

QString Quaternion::getString(unsigned int prec) const {
    return QString::number(getR(), 'f', prec) + ", " +
            QString::number(getI(), 'f', prec) + "i, " +
            QString::number(getJ(), 'f', prec) + "j, " +
            QString::number(getK(), 'f', prec) + "k";

}
