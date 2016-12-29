//
// Created by Vincent on 28/12/2016.
//

#include "../include/Player.h"
#include "../include/Mesh3D.h"

Player* Player::instance = new Player();

Player::Player() {

    playerOscillation = new Oscillation( 0.0f, 0.02f, 3.5f );
    lookDirection = glm::vec2( 0, -1 );
    lookDirFlag = LookDirEnum::lookNorth;
    currentRot = 180;

    inAnim = false;
    moving = false;
    rotating = false;

    weapon = NULL;
    hitOscillation = new Oscillation( 0, 300, 260 );

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
                currentPos = targetPos;
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
                currentRot = targetRot;
                rotating = false;
                inAnim = false;
            }
            minDistSecurity = newMinDist;
        }
    }

    playerOscillation->nextValueSmooth();
    camera.setPosition( glm::vec3( camera.getPosition().x, playerOscillation->getValue(), camera.getPosition().z ) );

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    if ( weapon != NULL ) {
        if (hitting) {
            hitOscillation->nextValue();
            if ( hitOscillation->getValue() <= 55 ) {
                camera.moveFront((float)Time::deltaTime * 1);
            } else {
                camera.moveFront((float)Time::deltaTime * -1);
            }
            if ( hitOscillation->getValue() >= 110 ) {
                hitting = false;
                inAnim = false;
                hitOscillation->setValue( hitOscillation->getMinValue() );
                camera.setPosition( glm::vec3(currentPos.x, camera.getPosition().y, currentPos.z) );
            }
        }
        weapon->setScale( 0.75f );
        weapon->setTranslation( camera.getPosition() );
        weapon->addTranslation(  0, -0.225f - hitOscillation->getValue()*0.008f, 0 );
        weapon->setRotation(  glm::vec3(0,1,0), currentRot + 180 - 35 + hitOscillation->getValue() );
        weapon->addRotation(  glm::vec3(1,0,0), 40 );
        weapon->addRotation(  glm::vec3(0,0,1), 80 );
    }

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

void Player::setPositionOnMap(int posX, int posY, bool updateCamera) {
    mapPosition = glm::vec2( posX, posY );
    setTranslation( (float)posX, 0, (float)posY);
    if (updateCamera) {
        camera.setPosition( glm::vec3(posX, 0, posY) );
        currentPos = glm::vec3( posX, 0, posY );
    }
}

glm::vec2 Player::getLeftDirection() {
    if ( lookDirFlag == LookDirEnum::lookNorth ) {
        return glm::vec2(-1, 0);
    }
    else if ( lookDirFlag == LookDirEnum::lookWest ) {
        return glm::vec2( 0, 1 );
    }
    else if ( lookDirFlag == LookDirEnum::lookSouth ) {
        return glm::vec2( 1, 0 );
    }
    else {
        return glm::vec2( 0, -1 );
    }

}

void Player::setWeapon(Mesh3D *weapon) {
    this->weapon = weapon;
}

void Player::hit() {
    if (inAnim) return;
    if (hitting) return;
    inAnim = true;
    hitting = true;
}
