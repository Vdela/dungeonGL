//
// Created by Irene on 28/12/2016.
//

#ifndef IMACGL_MONSTRE_H
#define IMACGL_MONSTRE_H

#include <string>

using namespace std;

class Monstre{
private:
    unsigned int id;
    float position[3];
    string nom;
    int type;
    int caracteristique;
    int nbPtDeVie;
    string Modele3D;
public:
    Monstre();
    Monstre(unsigned int id, float x, float y, float z, string nom, int type, int caracteristique, int nbPtDeVie);
    ~Monstre();

    unsigned int getId(void);
    void setId(unsigned int id);

    float* getPosition(void);
    void setPosition(float x, float y, float z);

    string getNom(void);
    void setNom(string nom);

    int getType(void);
    void setType(int type);

    int getCaracteristique(void);
    void setCaracteristique(int caracteristique);

    int getNbPtDeVie(void);
    void setNbPtDeVie(int nbPtDeVie);
};

#endif //IMACGL_MONSTRE_H
