//
// Created by Vincent on 28/12/2016.
//

#ifndef IMACGL_PLAYER_H
#define IMACGL_PLAYER_H

#include "Mesh3D.h"
#include "Oscillation.h"

enum LookDirEnum {
    lookNorth,
    lookSouth,
    lookWest,
    lookEast
};

class Player : public Object3D {


private:
    Player();
    static Player * instance;
    Oscillation * playerOscillation;
    glm::vec2 mapPosition;
    glm::vec2 lookDirection;
    LookDirEnum lookDirFlag;

    bool inAnim;
    bool moving;
    bool rotating;

    glm::vec3 targetPos;
    glm::vec3 currentPos;
    glm::vec3 startingMovePos;

    float targetRot;
    float currentRot;
    float startingRot;

    float moveSpeed = 2.0f;
    float rotSpeed = 2.0f;

    float minDistSecurity;

public:
    static Player& getInstance();
    FreeflyCamera camera;
    void draw();

    glm::vec2 getPositionOnMap(){ return mapPosition; }
    void setPositionOnMap(int posX, int posY);
    void stepForward();
    void stepBack();
    void stepLeft();
    void stepRight();
    void rotateLeft();
    void rotateRight();

};

#endif //IMACGL_PLAYER_H
