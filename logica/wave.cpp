#include "wave.h"

Wave::Wave(){}

double Wave::getVAmp(int index) const {
    if (index < v.size()){
        return v[index];
    } else return 0;
}

void Wave::setVAmp(double x, int index, bool insert){
    if (index<0) {
        v.push_back(x);
    }
    else if (index < waveLenght()){
        if(insert) {
            v.insert(index, x);
        }
        else{
            v.replace(index, x);
        }
    }
}

void Wave::removeVAmp(int index) {
    if (index< v.size())
        v.remove(index);
}

void Wave::pushPoint(double x, int index, bool insert) {
    this->setVAmp(x, index, insert);
}

void Wave::removePoint(const int index){
    removeVAmp(index);
}

int Wave::waveLenght() const{
    return v.size();
}


double Wave::getAmpVal(const int x) const{
    return getVAmp(x);
}

Wave Wave::operator+ (const Wave& x) {
    Wave* aux = new Wave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());
    int i=0;
    for( ; i<maxLenght; ++i) {
        aux->pushPoint(this->getAmpVal(i) + x.getAmpVal(i));
    }
    return *aux;
}

Wave Wave::operator- (const Wave& x) {
    Wave* aux = new Wave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
        aux->pushPoint(this->getAmpVal(i) - x.getAmpVal(i));
    }
    return *aux;
}

Wave Wave::operator/ (const Wave& x) {
    Wave* aux = new Wave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
        if(x.getAmpVal(i)== 0){
            throw exce_kalk("Impossibile dividere per 0.");
        } else {
            aux->pushPoint(this->getAmpVal(i) / x.getAmpVal(i));
        }
    }
    return *aux;
}

Wave Wave::operator* (const Wave& x) {
    Wave* aux = new Wave();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
       aux->pushPoint(this->getAmpVal(i) * x.getAmpVal(i));
    }
    return *aux;
}
