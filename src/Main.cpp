#define GLEW_STATIC


#include "../include/GameManager.h"
#include "../include/Niveau.h"


int main(int argc, char **argv) {

    GameManager gameManager = GameManager::getInstance();
    gameManager.initGame( 800, 800, (char*)"DungeonGL" );

    Niveau niveau1;
    niveau1.lectureMap((char*)"../files/map3.ppm");

    return 0;
}
