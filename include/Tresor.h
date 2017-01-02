//
// Created by Irene on 28/12/2016.
//

#ifndef IMACGL_TRESOR_H
#define IMACGL_TRESOR_H

#include <string>
#include <glm/vec2.hpp>
#include "Object3D.h"

using namespace std;

class Tresor{
private:
    unsigned int id;

    float position[3];
    glm::vec2 positionT;

    string nom;

    int type;
    int caracteristique;

    string Modele3Dobj;
    string Modele3Dmtl;

    Object3D * object;

public:
    Tresor();
    Tresor(unsigned int id, float x, float y, float z, string nom, int type, int caracteristique, string Modele3Dobj, string Modele3Dmtl);
    ~Tresor();

    unsigned int getId(void);
    void setId(unsigned int id);

    float* getPosition(void);
    void setPosition(float x, float y, float z);

    string getNom(void);
    void setNom(string nom);

    int getType(void);
    void setType(int type);

    int* getCaracteristique(void);
    void setCaracteristique(int caracteristique);

    string getModele3Dobj();
    void setModele3Dobj(string Modele3Dobj);

    string getModele3Dmtl();
    void setModele3Dmtl(string Modele3Dmtl);

    Object3D* getObject3D(void);
    void setObject3D(Object3D* object);

    bool devant_Tresor(glm::vec2 futurePosition);
    bool sur_Tresor(glm::vec2 positionJoueur);
};

#endif //IMACGL_TRESOR_H
