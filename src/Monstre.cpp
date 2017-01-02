//
// Created by Irene on 28/12/2016.
//

#include "../include/Monstre.h"
#include "../include/Niveau.h"
#include "../include/Player.h"

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

    currentPos = glm::vec3(x,y,z);
    targetPos = currentPos;

    switch (rotation) {
        case 0 :
            lookDirection = glm::vec2( 0, -1 );
            lookDirFlag = LookDirEnum::lookNorth;
            break;
        case 90 :
            lookDirection = glm::vec2( -1, 0 );
            lookDirFlag = LookDirEnum::lookWest;
            break;
        case 180 :
            lookDirection = glm::vec2( 0, 1 );
            lookDirFlag = LookDirEnum::lookSouth;
            break;
        case 270 :
            lookDirection = glm::vec2( 1, 01 );
            lookDirFlag = LookDirEnum::lookEast;
            break;
        default :
            rotation = 0;
            lookDirection = glm::vec2( 0, -1 );
            lookDirFlag = LookDirEnum::lookNorth;
            break;
    }
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

int* Monstre::getNbPtDeVie(void) {
    return &(this->nbPtDeVie);
}

void Monstre::setNbPtDeVie(int nbPtDeVie) {
    this->nbPtDeVie = nbPtDeVie;
}

Demon3D *Monstre::getObject3D(void) {
    return this->object;
}

void Monstre::setObject3D(Demon3D *object) {
    this->object = object;
}

bool Monstre::devant_Monstre(glm::vec2 futurePosition) {
    return (futurePosition == monstrePosition);
}
void Monstre::update(Niveau * pNiveau) {
    int index;
    Player player = Player::getInstance();
    if ( !inAnim && !moving && (player.getPositionOnMap().x == monstrePosition.x || player.getPositionOnMap().y  == monstrePosition.y) ) {
        glm::vec2 targetMap;
        minDistSecurity = 100.0f;
        if ( player.getPositionOnMap().x == monstrePosition.x ) {
            int diff = (int)player.getPositionOnMap().y - (int)monstrePosition.y;
            targetMap = monstrePosition + glm::vec2( 0, diff / abs(diff) );
            if ( diff < 0 ) object->setRotation( glm::vec3(0,1,0), 90 );
            else object->setRotation( glm::vec3(0,1,0), 270 );
            if ( abs(diff) >= 2
                 && !(pNiveau->faceCoffre(targetMap, &index))
                 && Cell::walkableCell( pNiveau->getCell(targetMap), false)
                 && !pNiveau->faceMonstre(targetMap, &index))
            {
                targetPos = currentPos + glm::vec3(0, 0, diff / abs(diff));
            } else {
                return;
            }
        } else if ( player.getPositionOnMap().y == monstrePosition.y ) {
            int diff = (int)player.getPositionOnMap().x - (int)monstrePosition.x;
            targetMap = monstrePosition + glm::vec2( diff / abs(diff), 0 );
            if ( diff < 0 ) object->setRotation( glm::vec3(0,1,0), 180 );
            else object->setRotation( glm::vec3(0,1,0), 0 );
            if ( abs(diff) >= 2
                 && !(pNiveau->faceCoffre(targetMap, &index))
                 && Cell::walkableCell( pNiveau->getCell(targetMap), false)
                 && !pNiveau->faceMonstre(targetMap, &index))
            {
                targetPos = currentPos + glm::vec3(diff / abs(diff), 0, 0);
            } else {
                return;
            }
        }


        moving = true;
        inAnim = true;
        startingMovePos = currentPos;
    }
    move();
}

void Monstre::move() {
    if ( !moving ) return;
    if ( !inAnim ) return;
    float newMinDist;
    glm::vec3 step = (targetPos - startingMovePos) * (float) Time::deltaTime * moveSpeed * 0.5f;
    object->addTranslation(step);
    currentPos += step;
    monstrePosition = glm::vec2(targetPos.x, targetPos.z);
    position[0] = currentPos.x;
    position[1] = currentPos.y;
    position[2] = currentPos.z;
    newMinDist = glm::distance(currentPos, targetPos);
    if (glm::distance(currentPos, targetPos) <= glm::length(step) || newMinDist > minDistSecurity ) {
        currentPos = targetPos;
        object->setTranslation(targetPos);
        moving = false;
        inAnim = false;
    }
    minDistSecurity = newMinDist;
}




