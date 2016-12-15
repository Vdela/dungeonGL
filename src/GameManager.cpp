//
// Created by Vincent on 15/12/2016.
//

#include "../include/GameManager.h"

GameManager const GameManager::instance = GameManager();

GameManager::GameManager() {

}

const GameManager& GameManager::getInstance() {
    return GameManager::instance;
}
