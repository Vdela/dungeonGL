//
// Created by Irene on 26/12/2016.
//

#include "../include/Cell.h"

Cell::Cell(CellType type, float cellPosX, float cellPosY) {
    this->type = type;
    this->cellPosition.x = cellPosX;
    this->cellPosition.y = cellPosY;
    //this->cellObject3D = NULL;
}
/*
Cell::Cell(CellType type, float cellPosX, float cellPosY, Object3D * object3D) {
    this->type = type;
    this->cellPosition.x = cellPosX;
    this->cellPosition.y = cellPosY;
    this->cellObject3D = object3D;
}*/

Cell::~Cell(){}


CellType Cell::getType(void)
{
    return type;
}

void Cell::setType(CellType type)
{
    this->type = type;
}


glm::vec2 Cell::getCellPosition(void)
{
    return this->cellPosition;
}