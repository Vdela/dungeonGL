//
// Created by Irene on 28/12/2016.
//

#include "../include/Tresor.h"


Tresor::Tresor() {}

Tresor::Tresor(unsigned int id, float x, float y, float z, string nom, int type, int caracteristique, string Modele3Dobj, string Modele3Dmtl) {
    this->id = id;
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->positionT.x = (int) x;
    this->positionT.y = (int) z;
    this->nom = nom;
    this->type = type;
    this->caracteristique = caracteristique;
    this->Modele3Dobj = Modele3Dobj;
    this->Modele3Dmtl = Modele3Dmtl;
}

Tresor::~Tresor() {}

unsigned int Tresor::getId(void) {
    return this->id;
}

void Tresor::setId(unsigned int id) {
    this->id = id;
}

float *Tresor::getPosition(void) {
    return position;
}

void Tresor::setPosition(float x, float y, float z) {
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

string Tresor::getNom(void) {
    return this->nom;
}

void Tresor::setNom(string nom) {
    this->nom = nom;
}

int Tresor::getType(void) {
    return this->type;
}

void Tresor::setType(int type) {
    this->type = type;
}

int* Tresor::getCaracteristique(void) {
    return &(this->caracteristique);
}

void Tresor::setCaracteristique(int caracteristique) {
    this->caracteristique = caracteristique;
}

string Tresor::getModele3Dobj() {
    return this->Modele3Dobj;
}

void Tresor::setModele3Dobj(string Modele3Dobj) {
    this->Modele3Dobj = Modele3Dobj;
}

string Tresor::getModele3Dmtl() {
    return this->Modele3Dmtl;
}

void Tresor::setModele3Dmtl(string Modele3Dmtl) {
    this->Modele3Dmtl = Modele3Dmtl;
}

Object3D *Tresor::getObject3D(void) {
    return this->object;
}

void Tresor::setObject3D(Object3D *object) {
    this->object = object;
}

bool Tresor::devant_Tresor(glm::vec2 futurePosition) {
    return (futurePosition == positionT && type == 2);
}

bool Tresor::sur_Tresor(glm::vec2 positionJoueur) {
    return (positionJoueur == positionT);
}














