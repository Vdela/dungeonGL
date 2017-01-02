//
// Created by Irene on 23/12/2016.
//

#ifndef IMACGL_NIVEAU_H
#define IMACGL_NIVEAU_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdlib.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/BBox.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/common.hpp>

#include "Cell.h"
#include "Object3D.h"
#include "Demon3D.h"
#include "GameManager.h"
#include "Mesh3D.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Porte.h"

using namespace std;

class Niveau{

private:
    unsigned int nbTresors;
    unsigned int nbMonstres;
    vector<Monstre> monstres;
    vector<Tresor> tresors;
    unsigned int heightMap;
    unsigned int widthMap;
    vector<vector<CellType > > carteId;
    vector<vector<Cell> > cellules;
    vector<glm::vec2> portes;
    glm::vec2 startPos;
    glm::vec2 endPos;
public:
    Niveau();
    ~Niveau();

    vector<Monstre>& getMonstres(void);
    vector<Tresor>& getTresors(void);

    vector<vector<CellType> > getCarteId(void);
    vector<vector<Cell> > getCellules(void);

    unsigned int getHeightMap(void);
    unsigned int getWidthMap(void);

    void setNbTresors(unsigned int nbTresors);
    void setNbMonstres(unsigned int nbMonstres);

    glm::vec2 getStartPos() { return startPos; }
    glm::vec2 getEndPos() { return endPos; }

    Cell* getCell( glm::vec2 pos ) {
        return &cellules[(int)pos.x][(int)pos.y];
    }

    void lectureMap(char* fileName);

    void createMap(void);

    void createTresors();
    void createMonstres();
    void createPortes();

    bool faceCoffre(glm::vec2 futurePosition, int* id);
    bool faceMonstre(glm::vec2 futurePosition, int* id);

    void frappeCoffre(glm::vec2 futurePosition);
    void frappeMonstre(glm::vec2 futurePosition);

    bool recupTresor(glm::vec2 futurePosition, int* id);
    void associationPt(int* nmb, int i);
};

#endif //IMACGL_NIVEAU_H
