//
// Created by Vincent on 28/12/2016.
//

#include "../include/Player.h"

Player* Player::instance = new Player();

Player::Player() {

    playerOscillation = new Oscillation( 0.0f, 0.02f, 3.5f );
    lookDirection = glm::vec2( 0, -1 );
    lookDirFlag = LookDirEnum::lookNorth;
    currentRot = 180;

    inAnim = false;
    moving = false;
    rotating = false;

}

Player& Player::getInstance() {
    if ( Player::instance == NULL ) {
        Player::instance = new Player();
    }
    return *Player::instance;
}

void Player::draw() {
    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    float newMinDist;

    if ( inAnim ) {
        if (moving) {
            glm::vec3 step = (targetPos - startingMovePos) * (float) Time::deltaTime * moveSpeed;
            this->addTranslation(step);
            currentPos += step;
            camera.setPosition(currentPos);
            newMinDist = glm::distance(currentPos, targetPos);
            if (glm::distance(currentPos, targetPos) <= 2 * glm::length(step) || newMinDist > minDistSecurity ) {
                camera.setPosition(targetPos);
                moving = false;
                inAnim = false;
            }
            minDistSecurity = newMinDist;
        }

        if (rotating) {
            float step = (targetRot - startingRot) * (float) Time::deltaTime * rotSpeed;
            this->addRotation(glm::vec3(0, 1, 0), step);
            currentRot += step;
            camera.setRotation(currentRot);
            newMinDist = glm::distance(currentRot, targetRot);
            if (glm::distance(currentRot, targetRot) <= abs(2 * step) || newMinDist > minDistSecurity ) {
                camera.setRotation(targetRot);
                rotating = false;
                inAnim = false;
            }
            minDistSecurity = newMinDist;
        }
    }

    playerOscillation->nextValueSmooth();
    camera.setPosition( glm::vec3( camera.getPosition().x, playerOscillation->getValue(), camera.getPosition().z ) );

}

void Player::stepForward() {
    if ( inAnim ) return;
    inAnim = true;
    if ( moving ) return;
    moving = true;
    targetPos = glm::vec3( mapPosition.x + lookDirection.x, 0, mapPosition.y + lookDirection.y );
    currentPos = glm::vec3( mapPosition.x, 0, mapPosition.y );
    startingMovePos = glm::vec3( mapPosition.x, 0, mapPosition.y );
    setPositionOnMap( (int)(mapPosition.x + lookDirection.x),
                      (int)(mapPosition.y + lookDirection.y) );
    minDistSecurity = 100.0f;
}

void Player::stepBack() {
    if ( inAnim ) return;
    inAnim = true;
    if ( moving ) return;
    moving = true;
    targetPos = glm::vec3( mapPosition.x - lookDirection.x, 0, mapPosition.y - lookDirection.y );
    currentPos = glm::vec3( mapPosition.x, 0, mapPosition.y );
    startingMovePos = glm::vec3( mapPosition.x, 0, mapPosition.y );
    setPositionOnMap( (int)(mapPosition.x - lookDirection.x),
                      (int)(mapPosition.y - lookDirection.y) );
    minDistSecurity = 100.0f;
}

void Player::stepLeft() {
    if ( inAnim ) return;
    inAnim = true;
    if ( moving ) return;
    moving = true;
    if ( lookDirFlag == LookDirEnum::lookNorth || lookDirFlag == LookDirEnum::lookSouth ) {
        targetPos = glm::vec3(mapPosition.x + lookDirection.y, 0, mapPosition.y + lookDirection.x);
        currentPos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        startingMovePos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        setPositionOnMap((int) (mapPosition.x + lookDirection.y),
                         (int) (mapPosition.y + lookDirection.x));
    } else {
        targetPos = glm::vec3(mapPosition.x - lookDirection.y, 0, mapPosition.y - lookDirection.x);
        currentPos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        startingMovePos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        setPositionOnMap((int) (mapPosition.x - lookDirection.y),
                         (int) (mapPosition.y - lookDirection.x));
    }
    minDistSecurity = 100.0f;
}

void Player::stepRight() {
    if ( inAnim ) return;
    inAnim = true;
    if ( moving ) return;
    moving = true;
    if ( lookDirFlag == LookDirEnum::lookEast || lookDirFlag == LookDirEnum::lookWest ) {
        targetPos = glm::vec3(mapPosition.x + lookDirection.y, 0, mapPosition.y + lookDirection.x);
        currentPos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        startingMovePos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        setPositionOnMap((int) (mapPosition.x + lookDirection.y),
                         (int) (mapPosition.y + lookDirection.x));
    } else {
        targetPos = glm::vec3(mapPosition.x - lookDirection.y, 0, mapPosition.y - lookDirection.x);
        currentPos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        startingMovePos = glm::vec3(mapPosition.x, 0, mapPosition.y);
        setPositionOnMap((int) (mapPosition.x - lookDirection.y),
                         (int) (mapPosition.y - lookDirection.x));
    }
    minDistSecurity = 100.0f;
}

void Player::rotateLeft() {
    if ( inAnim ) return;
    inAnim = true;
    if ( rotating ) return;
    rotating = true;
    targetRot = currentRot + 90.0f;
    startingRot = currentRot;

    switch ( lookDirFlag ) {
        case LookDirEnum::lookNorth:
            lookDirFlag = LookDirEnum::lookWest;
            lookDirection = glm::vec2( -1, 0 );
            break;
        case LookDirEnum::lookWest:
            lookDirFlag = LookDirEnum::lookSouth;
            lookDirection = glm::vec2( 0, 1 );
            break;
        case LookDirEnum::lookSouth:
            lookDirFlag = LookDirEnum::lookEast;
            lookDirection = glm::vec2( 1, 0 );
            break;
        case LookDirEnum::lookEast:
            lookDirFlag = LookDirEnum::lookNorth;
            lookDirection = glm::vec2( 0, -1 );
            break;
    }
    minDistSecurity = 100.0f;

}

void Player::rotateRight() {
    if ( inAnim ) return;
    inAnim = true;
    if ( rotating ) return;
    rotating = true;
    targetRot = currentRot - 90.0f;
    startingRot = currentRot;

    switch ( lookDirFlag ) {
        case LookDirEnum::lookNorth:
            lookDirFlag = LookDirEnum::lookEast;
            lookDirection = glm::vec2( 1, 0 );
            break;
        case LookDirEnum::lookEast:
            lookDirFlag = LookDirEnum::lookSouth;
            lookDirection = glm::vec2( 0, 1 );
            break;
        case LookDirEnum::lookSouth:
            lookDirFlag = LookDirEnum::lookWest;
            lookDirection = glm::vec2( -1, 0 );
            break;
        case LookDirEnum::lookWest:
            lookDirFlag = LookDirEnum::lookNorth;
            lookDirection = glm::vec2( 0, -1 );
            break;
    }
    minDistSecurity = 100.0f;

}

void Player::setPositionOnMap(int posX, int posY) {
    mapPosition = glm::vec2( posX, posY );
    setTranslation( (float)posX, 0, (float)posY);
    camera.setPosition( glm::vec3(posX, 0, posY) );
}
