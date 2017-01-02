//
// Created by Irene on 28/12/2016.
//

#ifndef IMACGL_MONSTRE_H
#define IMACGL_MONSTRE_H

#include <string>
#include "Object3D.h"
#include "Demon3D.h"
#include "Cell.h"
#include "Player.h"
#include <glm/vec2.hpp>

class Niveau;

using namespace std;

class Monstre{
private:
    unsigned int id;

    float position[3];
    glm::vec2 monstrePosition;
    int rotation;

    string nom;

    int type;
    int caracteristique;
    int nbPtDeVie;

    Demon3D * object;

    float moveSpeed = 0.5f;

    bool inAnim;
    bool moving;

    glm::vec3 targetPos;
    glm::vec3 currentPos;
    glm::vec3 startingMovePos;

    float minDistSecurity;
    static float hitSecondsReload;
    float lastHit;
public:
    Monstre();
    Monstre(unsigned int id, float x, float y, float z, int rotation, string nom, int type, int caracteristique, int nbPtDeVie);
    ~Monstre();

    unsigned int getId(void);
    void setId(unsigned int id);

    float* getPosition(void);
    void setPosition(float x, float y, float z);

    int getRotation(void);
    void setRotation(int rotation);

    string getNom(void);
    void setNom(string nom);

    int getType(void);
    void setType(int type);

    int getCaracteristique(void);
    void setCaracteristique(int caracteristique);

    int* getNbPtDeVie(void);
    void setNbPtDeVie(int nbPtDeVie);

    Demon3D* getObject3D(void);
    void setObject3D(Demon3D* object);

    bool devant_Monstre(glm::vec2 futurePosition);

    void move();

    void update(Niveau * pNiveau);

    void hitPlayer();
};

#endif //IMACGL_MONSTRE_H
