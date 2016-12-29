//
// Created by Irene on 28/12/2016.
//

#include "../include/Monstre.h"

Monstre::Monstre() {}

Monstre::Monstre(unsigned int id, float x, float y, float z, string nom, int type, int caracteristique, int nbPtDeVie) {
    this->id = id;
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
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





