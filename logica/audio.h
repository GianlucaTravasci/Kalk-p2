#ifndef AUDIO_H
#define AUDIO_H
#include <QVector>
#include <QString>
#include <QPair>
#include "wave.h"
#include "exce_kalk.h"

class Audio : public Wave {
protected:
    double getWAmp(int) const;    //ritorna l'ampiezza dell'onda nei vari punti
    void setWAmp(double, int=-1, bool=false);   //per settare altezza desiderata o con indice di default
    void removeWAmp(int);   //rimuove valori delle due onde del file audio da un determinato indice

private:
    QVector<double> w;
public:
    Audio();
    ~Audio() = default;

    enum ondeDisponibili{
        ondaSx,
        ondaDx
    };

    void pushPoint(double, double, int=-1, bool=false);  //aggiunge un valore all'onda
    void removePoint(const int);  //rimuove valore che corrisponde a una determinata posizione
    int waveLenght() const;    //ritorna la lunghezza della lista dei valori

    double getAmpVal(const int, int=Audio::ondeDisponibili::ondaSx) const;     //ritorna il valore destro o sinistro di un determinato punto della lista

    Audio operator+(const Audio&);
    Audio operator-(const Audio&);
    Audio operator/(const Audio&);
    Audio operator*(const Audio&);
};

#endif // AUDIO_H
