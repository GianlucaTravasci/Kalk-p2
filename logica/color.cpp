#include "color.h"

/**
 * Costruttori per la classe colore
 * -costruttore per interi: imposta il colore predefinito di default
 * -costruttore per stringhe
 * -costruttori a 3 parametri per interi
 */
Color::Color(): r(255), g(255), b(255) {}

Color::Color(int red, int green, int blue) {
    setRdec(red);
    setGdec(green);
    setBdec(blue);

}
Color::Color(const Color& x) {
    setRdec(x.getRdec());
    setGdec(x.getGdec());
    setBdec(x.getBdec());
}
Color::Color(const Color* x) {
    setRdec(x->getRdec());
    setGdec(x->getGdec());
    setBdec(x->getBdec());
}
/**
 * Per le modifiche dei colori attraverso interi:
 *      primi tre metodi per inserire i valori interi di un colore
 *      gli alri parametri sono per ritornare i valori inseriti
 */
void Color::setRdec(int red) {
    if(red<0) {
        r=0;
    }
    else if (red>255) {
        r=255;
    } else {
        r=red;
    }
}
void Color::setGdec(int green){
    if(green<0) {
        g=0;
    }
    else if (green>255) {
        g=255;
    } else {
        g=green;
    }
}
void Color::setBdec(int blue){
    if(blue<0) {
        b=0;
    }
    else if (blue>255) {
        b=255;
    } else {
        b=blue;
    }
}
unsigned int Color::getRdec() const{
    return r;
}
unsigned int Color::getGdec() const{
    return g;
}
unsigned int Color::getBdec() const{
    return b;
}

QString Color::ConvertRGBtoHex(const Color* RGB) {
    Helper aux;
    QString result="#";
    result.append(aux.decToHex(RGB->getRdec()));
    result.append(aux.decToHex(RGB->getGdec()));
    result.append(aux.decToHex(RGB->getBdec()));
    return result;
}

QString Color::GetColore() const{
    QString color;
    color.append(QString::number(getRdec()));
    color.append(",");
    color.append(QString::number(getGdec()));
    color.append(",");
    color.append(QString::number(getBdec()));
    return color;
}

Color Color::operator+ (const Color& x) const{
    return new Color ((this->getRdec()+x.getRdec()),
                      (this->getGdec()+x.getGdec()),
                      (this->getBdec()+x.getBdec()));
}
Color Color::operator- (const Color& x) const{
    return new Color ((this->getRdec()-x.getRdec()),
                      (this->getGdec()-x.getGdec()),
                      (this->getBdec()-x.getBdec()));
}
Color Color::operator* (const Color& x) const{
    return new Color ((this->getRdec()*x.getRdec()),
                      (this->getGdec()*x.getGdec()),
                      (this->getBdec()*x.getBdec()));
}
Color Color::operator/ (const Color& x) const{
    if(x.getRdec() == 0 || x.getGdec() == 0 || x.getBdec() == 0){
        throw exce_kalk("Impossibile dividere per 0.");
    } else {
        return new Color ((this->getRdec()/x.getRdec()),
                      (this->getGdec()/x.getGdec()),
                      (this->getBdec()/x.getBdec()));
    }
}
