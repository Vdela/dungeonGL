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
class Porte;

enum CellType {
    Wall,
    Floor,
    Water,
    Start,
    Door,
    End,
    EmptyCell
};

class Cell{
private:
    CellType type; // Voir enum CellType ci-dessus
    glm::vec2 cellPosition; //position du Cell dans le tableau (pas position réelle de l'objet3D)
   // Object3D * cellObject3D; // Le Cell peut être représenté par un Cube3D, un Quad3D, etc
    //Porte *m_porte;
//    Porte par;
public:
    //Cell(){};
    ~Cell();
    Cell(CellType type, float cellPosX, float cellPosY);
    //Cell(CellType type, float cellPosX, float cellPosY, Object3D * object3D);

    CellType getType(void);
    void setType(CellType type);

    static bool walkableCell( Cell * cell );
    static bool devant_Porte( Cell * cell );

    glm::vec2 getCellPosition(void);
    Porte* m_porte;

};

#endif //IMACGL_CELL_H
