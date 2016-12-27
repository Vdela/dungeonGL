//
// Created by Vincent on 26/12/2016.
//

#include "../include/Oscillation.h"
#include "../include/Time.h"


Oscillation::Oscillation(float min, float max, float speed) {
    minValue = min;
    maxValue = max;
    this->speed = speed;

    upping = true;
    current = min;
}

float Oscillation::getValue() {
    return current;
}

void Oscillation::nextValue() {

    float change = speed * (float)Time::deltaTime;

    if ( upping ) {
        current += change;
        if ( current > maxValue ) {
            current = maxValue;
            upping = false;
        }
    } else {
        current -= change;
        if ( current < minValue ) {
            current = minValue;
            upping = true;
        }
    }

}

void Oscillation::nextValueSmooth() {

    float change;
    float range = maxValue - minValue;
    float mid = minValue + (range / 2);
    float delta = (maxValue - mid) * 0.15f;


    if ( upping ) {
        if ( current > mid ) {
            change = ( current - (maxValue + delta) ) * speed * (float) Time::deltaTime;
            if (change < 0) change = -change;
        } else {
            change = ((minValue - delta) - current) * speed * (float)Time::deltaTime;
            if (change < 0) change = -change;
        }
        current += change;
        if ( current > maxValue ) {
            current = maxValue;
            upping = false;
        }
    } else {
        if ( current > mid ) {
            change = ( current - (maxValue + delta) ) * speed * (float) Time::deltaTime;
            if (change < 0) change = -change;
        } else {
            change = ((minValue - delta) - current) * speed * (float) Time::deltaTime;
            if (change < 0) change = -change;
        }
        current -= change;
        if ( current < minValue ) {
            current = minValue;
            upping = true;
        }
    }

}