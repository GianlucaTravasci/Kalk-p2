#ifndef COLOREDWAVE_H
#define COLOREDWAVE_H

#include<QVector>
#include "color.h"
#include "wave.h"

class ColoredWave : public Wave
{
private:
    QVector<Color*> colori;
public:

    ColoredWave();
    ~ColoredWave() = default;

    Color getColor(int) const;
    void setColor(Color, int=-1, bool=false);


    void pushPoint(double, Color, int=-1, bool=false);
    void removePoint(const int);
    int waveLenght() const;

    double getAmpVal(const int) const;
    Color getAmpColor(const int) const;


    ColoredWave operator+(const ColoredWave&);
    ColoredWave operator-(const ColoredWave&);
    ColoredWave operator/(const ColoredWave&);
    ColoredWave operator*(const ColoredWave&);

};

#endif // COLOREDWAVE_H
