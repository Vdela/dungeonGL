//
// Created by Irene on 28/12/2016.
//

#include "../include/Monstre.h"

Monstre::Monstre() {}

Monstre::Monstre(unsigned int id, float x, float y, float z, int rotation, string nom, int type, int caracteristique, int nbPtDeVie) {
    this->id = id;
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->monstrePosition.x = (int) x;
    this->monstrePosition.y = (int) z;
    this->rotation = rotation;
    this->nom = nom;
    this->type = type;
    this->caracteristique = caracteristique;
    this->nbPtDeVie = nbPtDeVie;
}

Monstre::~Monstre() {}

unsigned int Monstre::getId(void) {
    return this->id;
}

void Monstre::setId(unsigned int id) {
    this->id = id;
}

float *Monstre::getPosition(void) {
    return position;
}

void Monstre::setPosition(float x, float y, float z) {
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

int Monstre::getRotation(void) {
    return this->rotation;
}

void Monstre::setRotation(int rotation) {
    this->rotation = rotation;
}

string Monstre::getNom(void) {
    return this->nom;
}

void Monstre::setNom(string nom) {
    this->nom = nom;
}

int Monstre::getType(void) {
    return this->type;
}

void Monstre::setType(int type) {
    this->type = type;
}

int Monstre::getCaracteristique(void) {
    return this->caracteristique;
}

void Monstre::setCaracteristique(int caracteristique) {
    this->caracteristique = caracteristique;
}

int Monstre::getNbPtDeVie(void) {
    return this->nbPtDeVie;
}

void Monstre::setNbPtDeVie(int nbPtDeVie) {
    this->nbPtDeVie = nbPtDeVie;
}

Object3D *Monstre::getObject3D(void) {
    return this->object;
}

void Monstre::setObject3D(Object3D *object) {
    this->object = object;
}

bool Monstre::devant_Monstre(glm::vec2 futurePosition) {
    return (futurePosition == monstrePosition);
}




