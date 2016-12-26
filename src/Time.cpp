//
// Created by Vincent on 26/12/2016.
//

#include "../include/Time.h"

int Time::lastElapsedTime = glutGet(GLUT_ELAPSED_TIME);
double Time::deltaTime = 0;

void Time::updateDeltaTime() {
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    Time::deltaTime = glutGet(GLUT_ELAPSED_TIME) - Time::lastElapsedTime;
    Time::deltaTime *= 0.001f;
    Time::lastElapsedTime = elapsedTime;
}
