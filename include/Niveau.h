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

#include "GameManager.h"

using namespace std;

class Niveau{

private:
    unsigned int nbTresors;
    unsigned int nbMonstres;
    vector<vector<int> > carte;
public:
    Niveau();
    void lectureMap(char* fileName);

};

#endif //IMACGL_NIVEAU_H
