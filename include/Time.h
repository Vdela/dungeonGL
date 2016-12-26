//
// Created by Vincent on 26/12/2016.
//

#ifndef IMACGL_TIME_H
#define IMACGL_TIME_H

#include <GL/glut.h>

class Time {

private:
public:
    static int lastElapsedTime;
    static double deltaTime;
    static void updateDeltaTime();

};


#endif //IMACGL_TIME_H
