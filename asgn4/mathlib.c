#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// normalize angle to [0, 2PI)
double NormalizeAngle(double x) {
    x = fmod(x, 2 * M_PI);
    if (x < 0) {
        x += 2 * M_PI;
    }
    return x;
}

double Abs(double x) {
    return x < 0 ? -x : x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}

double Sin(double x) {
    x = NormalizeAngle(x);

    double result = 0.0;
    double term = x;
    int i = 1;
    while (Abs(term) > EPSILON) {
        result += term;
        term *= -1;
        term *= x * x / ((2 * i) * (2 * i + 1));
        i++;
    }
    return result;
}

double Cos(double x) {
    x = NormalizeAngle(x);

    double result = 1.0;
    double term = 1.0;
    int i = 1;
    while (Abs(term) > EPSILON) {
        term *= -1;
        term *= x * x / ((2 * i - 1) * (2 * i));
        result += term;
        i++;
    }
    return result;
}

double Tan(double x) {
    double sinx = Sin(x);
    double cosx = Cos(x);
    return sinx / cosx;
}
