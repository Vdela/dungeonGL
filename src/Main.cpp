#define GLEW_STATIC


#include "../include/GameManager.h"



int main(int argc, char **argv) {

    GameManager gameManager = GameManager::getInstance();
    gameManager.initGame( 800, 800, (char*)"DungeonGL" );

    return 0;
}
