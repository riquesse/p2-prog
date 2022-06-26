#ifndef COLORGENERATOR_H
#define COLORGENERATOR_H

#include <cmath>

#include <QColor>

class ColorGenerator
{
private:


    static const double goldenRatio;
    static const double seed;
    double hue;

public:
ColorGenerator();
    QColor getRandomColor();
    QColor hsvToRgb(double h, double s, double v);
};

#endif // COLORGENERATOR_H
