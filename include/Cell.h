//
// Created by Irene on 26/12/2016.
//

#ifndef IMACGL_CELL_H
#define IMACGL_CELL_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <string>

using namespace std;

class Cell{
private:
    int type; //0 mur, 1 couloir, 2 entree, 3 sortie
    float position[3]; //centre du cube
    string textureName;
public:
    Cell();
    ~Cell();
    Cell(int type, float x, float y, float z, string textureName);

    int getType(void);
    void setType(int type);

    string getTextureName(void);

    float* getPosition(void);
    void setPosition(float x, float y, float z);


};

#endif //IMACGL_CELL_H
