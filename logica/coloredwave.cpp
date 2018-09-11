#include "coloredwave.h"

ColoredWave::ColoredWave() {}

Color ColoredWave::getColor(int index) const {
    Color ret;
    if(index < colori.size()) {
        ret= *colori[index];
    } return ret;
}


void ColoredWave::setColor(Color color, int index, bool insert) {
    Color* aux = new Color(color);
    if(index < 0) {
        colori.push_back(aux);
    } else if (index < waveLenght()){
        if(insert){
            colori.insert(index, aux);
        } else {
            colori.replace(index, aux);
        }
    }
}

void ColoredWave::pushPoint(double val, Color color, int index, bool insert) {
    this->setVAmp(val, index, insert);
    this->setColor(color, index, insert);
}

void ColoredWave::removePoint(const int index) {
    if (index < colori.size()) {
        colori.remove(index);
        v.remove(index);
    }
}

int ColoredWave::waveLenght() const{
    return colori.size();
}

double ColoredWave::getAmpVal(const int index) const {
    return getVAmp(index);
}

Color ColoredWave::getAmpColor(const int index) const {
    return getColor(index);
}

ColoredWave ColoredWave::operator+(const ColoredWave& x){
    ColoredWave* aux = new ColoredWave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    Color res;

    for(int i=0; i<maxLenght; ++i) {
        res = this->getColor(i) + x.getColor(i);
        aux->pushPoint(this->getAmpVal(i) + x.getAmpVal(i), res);
    }
    return *aux;
}
ColoredWave ColoredWave::operator-(const ColoredWave& x){
    ColoredWave* aux = new ColoredWave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    Color res;

    for(int i=0; i<maxLenght; ++i) {
        res = this->getColor(i) - x.getColor(i);
        aux->pushPoint(this->getAmpVal(i) - x.getAmpVal(i), res);
    }
    return *aux;
}
ColoredWave ColoredWave::operator*(const ColoredWave& x){
    ColoredWave* aux = new ColoredWave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    Color res;

    for(int i=0; i<maxLenght; ++i) {
        res = this->getColor(i) * x.getColor(i);
        aux->pushPoint(this->getAmpVal(i) * x.getAmpVal(i), res);
    }
    return *aux;
}
ColoredWave ColoredWave::operator/(const ColoredWave& x){
    ColoredWave* aux = new ColoredWave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    Color res;

    for(int i=0; i<maxLenght; ++i) {
        if(x.getAmpVal(i) == 0){
            throw exce_kalk("Impossibile dividere per 0.");
        } else {
            res = this->getColor(i) / x.getColor(i);
            aux->pushPoint(this->getAmpVal(i) / x.getAmpVal(i), res);
        }
    }
    return *aux;
}
