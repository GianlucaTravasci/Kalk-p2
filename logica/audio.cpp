#include "audio.h"


Audio::Audio(){}

double Audio::getWAmp(int index) const {
    if(index < w.size()) {
        return w[index];
    }else return 0;
}

void Audio::setWAmp(double x, int index, bool insert) {
    if(index<0) {
        w.push_back(x);
    } else if (index<waveLenght()){
        if(insert) {
            w.insert(index, x);
        } else {
            w.replace(index, x);
        }
    }
}
void Audio::removeWAmp(int index) {
    if (index < w.size())
        w.remove(index);
}

void Audio::pushPoint(double x, double y, int index, bool insert) {
    setVAmp(x, index, insert);
    setWAmp(y, index, insert);
}

void Audio::removePoint(const int index){
    removeWAmp(index);
    removeVAmp(index);
}

int Audio::waveLenght() const {
    return w.size();
}

double Audio::getAmpVal(const int index, int ondaRichiesta) const{
    if(ondaRichiesta==Audio::ondeDisponibili::ondaSx) {
        return getVAmp(index);
    }else{
        return getWAmp(index);
    }
}

Audio Audio::operator+ (const Audio& x) {
    Audio* aux = new Audio();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
         aux->pushPoint(this->getAmpVal(i) + x.getAmpVal(i),
                         this->getAmpVal(i, Audio::ondeDisponibili::ondaDx) + x.getAmpVal(i, Audio::ondeDisponibili::ondaDx));
    }
    return *aux;
}
Audio Audio::operator- (const Audio& x) {
    Audio* aux = new Audio();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
         aux->pushPoint(this->getAmpVal(i) - x.getAmpVal(i),
                         this->getAmpVal(i, Audio::ondeDisponibili::ondaDx) - x.getAmpVal(i, Audio::ondeDisponibili::ondaDx));
    }
    return *aux;
}
Audio Audio::operator/ (const Audio& x) {
    Audio* aux = new Audio();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
        if(x.getAmpVal(i)==0 || x.getAmpVal(i, Audio::ondeDisponibili::ondaDx) == 0){
            throw exce_kalk("Impossibile dividere per 0.");
        } else {
            aux->pushPoint(this->getAmpVal(i) / x.getAmpVal(i),
                         this->getAmpVal(i, Audio::ondeDisponibili::ondaDx) / x.getAmpVal(i, Audio::ondeDisponibili::ondaDx));
        }
    }
    return *aux;
}
Audio Audio::operator* (const Audio& x) {
    Audio* aux = new Audio();
    int maxLenght = qMax(this->waveLenght(), x.waveLenght());

    for(int i=0; i<maxLenght; ++i) {
         aux->pushPoint(this->getAmpVal(i) * x.getAmpVal(i),
                         this->getAmpVal(i, Audio::ondeDisponibili::ondaDx) * x.getAmpVal(i, Audio::ondeDisponibili::ondaDx));
    }
    return *aux;
}
