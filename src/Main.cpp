#define GLEW_STATIC


#include "../include/GameManager.h"
#include "../include/Interface.h"


int main(int argc, char **argv) {
    GameManager gameManager = GameManager::getInstance();
    gameManager.initGame( Interface::gameWidth, Interface::gameHeight, (char*)"DungeonGL" );

    return 0;
}
