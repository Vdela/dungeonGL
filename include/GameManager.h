//
// Created by Vincent on 15/12/2016.
//

#ifndef IMACGL_GAMEMANAGER_H
#define IMACGL_GAMEMANAGER_H

#include <stddef.h>

class GameManager {

public:
    static const GameManager& getInstance();

private:
    GameManager();
    static GameManager const instance;

};


#endif //IMACGL_GAMEMANAGER_H
