//
// Created by Irene on 26/12/2016.
//

#include "../include/Cell.h"
#include "../include/Porte.h"
#include "../include/Player.h"

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

bool Cell::walkableCell(Cell *cell, bool forPlayer) {
    if ( cell == NULL ) return false;
    if ( forPlayer ) {
        if (cell->type == CellType::Floor || cell->type == CellType::Start || cell->type == CellType::End) {
            return true;
        } else if ( cell->type == CellType::Door ) {
           if (cell->door != NULL) {
               if (cell->door->getIsOpen()) {
                   return true;
               } else {
                   if ( *Player::getInstance().getClef() >= 1 ) {
                       *Player::getInstance().getClef() -= 1;
                       cell->door->setIsOpen( true );
                       cell->door->addTranslation( 0, -1.48f, 0 );
                       return true;
                   }
               }
           }
        }
        return false;
    } else {
        if (cell->type == CellType::Floor || cell->type == CellType::Start || cell->type == CellType::End ||
            cell->type == CellType::Water) {
            return true;
        } else if (cell->type == CellType::Door) {
            if (cell->door == NULL || (cell->door != NULL && cell->door->getIsOpen())) {
                return true;
            }
        }
        return false;
    }
}

bool Cell::devant_Porte(Cell *cell) {
    if ( cell == NULL ) return false;
    return cell->type == CellType::Door;
}