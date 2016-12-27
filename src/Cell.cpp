//
// Created by Irene on 26/12/2016.
//

#include "../include/Cell.h"

Cell::Cell(int type, float x, float y, float z, string textureName){
    this->type = type;
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->textureName = textureName;
}

Cell::~Cell(){}


int Cell::getType(void)
{
    return type;
}

void Cell::setType(int type)
{
    this->type = type;
}

float* Cell::getPosition(void)
{
    return this->position;
}

void Cell::setPosition(float x, float y, float z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

string Cell::getTextureName(void) {
    return this->textureName;
}
