//
// Created by Vincent on 26/12/2016.
//

#ifndef IMACGL_OSCILLATION_H
#define IMACGL_OSCILLATION_H

#include <cstdlib>

class Oscillation {

private:
    float minValue;
    float maxValue;
    float current;
    float speed;
    bool upping;
public:
    Oscillation(float min, float max, float speed);
    float getValue();
    float setValue(float value){ current = value; };
    void nextValue();
    void nextValueSmooth();
    float getMaxValue(){ return maxValue; }
    float getMinValue(){ return minValue; }

};


#endif //IMACGL_OSCILLATION_H
