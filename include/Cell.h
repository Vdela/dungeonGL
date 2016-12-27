//
// Created by Irene on 26/12/2016.
//

#ifndef IMACGL_CELL_H
#define IMACGL_CELL_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <string>
#include <glm/vec3.hpp>
#include "Object3D.h"

using namespace std;

enum CellType {
    Wall,
    Floor,
    Water,
    Start,
    End,
    InvalidCell
};

class Cell{
private:
    CellType type; // Voir enum CellType ci-dessus
    glm::vec2 cellPosition; //position du Cell dans le tableau (pas position réelle de l'objet3D)
    Object3D * cellObject3D; // Le Cell peut être représenté par un Cube3D, un Quad3D, etc
    //string textureName;
public:
    Cell(){};
    ~Cell();
    Cell(CellType type, float cellPosX, float cellPosY, Object3D * object3D);

    CellType getType(void);
    void setType(CellType type);
    void setObject3D(Object3D * object3D);

    //string getTextureName(void);

    glm::vec2 getCellPosition(void);
    /*void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 position);*/


};

#endif //IMACGL_CELL_H
