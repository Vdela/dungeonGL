//
// Created by Irene on 28/12/2016.
//

#include "../include/Dungeon.h"

Dungeon::Dungeon() {}
Dungeon::~Dungeon() {}

Niveau* Dungeon::getNiveau(void){
    return &niveau;
}

void Dungeon::chargementDonjon(char* fileName) {

    ifstream fichier( GameManager::getInstance().getAppPath() + "\\..\\..\\files\\" + fileName, ios::in);

    if(fichier){

        fichier.seekg(this->position, fichier.beg);

        string description;
        string line;
        string nombreNiveau;

        string nomDeLaMap;
        const char* nomMap;

        string nombreTresors;
        unsigned int nbTresors;

        string nombreMonstres;
        unsigned int nbMonstres;


        if(position == fichier.beg) {
            getline(fichier, description);
            this->description = description;
            getline(fichier, nombreNiveau);
            this->nbNiveau = atoi(nombreNiveau.c_str());
        }
        getline(fichier, nomDeLaMap);
        nomMap = nomDeLaMap.c_str();
        niveau.lectureMap(strdup(nomMap));
        getline(fichier, nombreTresors);
        nbTresors = atoi(nombreTresors.c_str());
        niveau.setNbTresors(nbTresors);
        for(int i = 0; i < nbTresors; i++){
            getline(fichier, line);
            vector<string> splitLine = split(line);
            Tresor tresor(atoi(splitLine[0].c_str()), atof(splitLine[1].c_str()), atof(splitLine[2].c_str()), atof(splitLine[3].c_str()), splitLine[4], atoi(splitLine[5].c_str()), atoi(splitLine[6].c_str()), splitLine[7], splitLine[8]);
             niveau.getTresors().push_back(tresor);
        }
        getline(fichier, nombreMonstres);
        nbMonstres = atoi(nombreMonstres.c_str());
        niveau.setNbMonstres(nbMonstres);
        for(int j = 0; j < nbMonstres; j++){
            getline(fichier, line);
            vector<string> splitLine = split(line);
            Monstre monstre(atoi(splitLine[0].c_str()), atof(splitLine[1].c_str()), atof(splitLine[2].c_str()), splitLine[3], atoi(splitLine[4].c_str()), atoi(splitLine[5].c_str()), atoi(splitLine[6].c_str()), splitLine[7]);
            niveau.getMonstres().push_back(monstre);

        }
    }
    else{
        cerr << "Impossible d'ouvrir le fichier de la map" << endl;
    }

    this->position = fichier.tellg();
}

vector<string> Dungeon::split(string sentence)
{
    char* str = (char *)sentence.c_str();
    char * splitSent = strtok(str, ":");
    vector<string> newVector;
    do
    {
        newVector.push_back(splitSent);
        splitSent = strtok(NULL, ":");
    }while(splitSent != NULL);

    return newVector;
}
