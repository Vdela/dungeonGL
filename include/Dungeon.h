//
// Created by Irene on 28/12/2016.
//

#ifndef IMACGL_DUNGEON_H
#define IMACGL_DUNGEON_H

#include <string>
#include <istream>
#include <cstdlib>
#include <vector>

#include "Niveau.h"

using namespace std;

class Dungeon{
private:
    string description;
    unsigned int nbNiveau;
    Niveau niveau;
    streampos position;
public:
    Dungeon();
    ~Dungeon();
    Niveau* getNiveau(void);
    void chargementDonjon(char* fileName);
    vector<string> split(string sentence);
};

#endif //IMACGL_DUNGEON_H