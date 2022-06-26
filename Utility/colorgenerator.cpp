#include "colorgenerator.h"

const double ColorGenerator::goldenRatio = 0.618033988749895;

const double ColorGenerator::seed = 0.5;

ColorGenerator::ColorGenerator()
    : hue(seed)
{

}

QColor ColorGenerator::getRandomColor()
{
    hue += goldenRatio;
    hue = fmod(hue,1.0);
    QColor color = hsvToRgb(hue, 0.7, 0.95);
    return color;
}

QColor ColorGenerator::hsvToRgb(double h, double s, double v)
{
    int h_i = floor(h * 6);
    double f = h * 6 - h_i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);
    double r = 255;
    double g = 255;
    double b = 255;
    switch (h_i) {
        case 0:
            r = v, g = t, b = p;
            break;
        case 1:
            r = q, g = v, b = p;
            break;
        case 2:
            r = p, g = v, b = t;
            break;
        case 3:
            r = p, g = q, b = v;
            break;
        case 4:
            r = t, g = p, b = v;
            break;
        case 5:
            r = v, g = p, b = q;
            break;
    }
    return QColor(floor(r * 256), floor(g * 256), floor(b * 256));
  }
