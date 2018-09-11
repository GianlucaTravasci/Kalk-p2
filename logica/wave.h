#ifndef WAVE_H
#define WAVE_H

#include <QVector>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "exce_kalk.h"

class Wave
{
protected:
    QVector<double> v;
    void setVAmp(double, int=-1, bool = false);
    double getVAmp(int) const;
    void removeVAmp(int);

public:
    Wave();

    virtual ~Wave() = default;

    virtual void pushPoint(double, int=-1, bool=false);  //aggiunge un valore all'onda
    virtual void removePoint(const int);  //rimuove valore che corrisponde a una determinata posizione
    virtual int waveLenght() const;    //ritorna la lunghezza della lista dei valori

    virtual double getAmpVal(const int) const;     //ritorna il valore di un determinato punto della lista

    Wave operator+(const Wave&);
    Wave operator-(const Wave&);
    Wave operator/(const Wave&);
    Wave operator*(const Wave&);
};

#endif // WAVE_H
