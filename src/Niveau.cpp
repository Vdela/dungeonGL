//
// Created by Irene on 23/12/2016.
//

#include "../include/Niveau.h"

Niveau::Niveau(){}

void Niveau::lectureMap(char* fileName){

    ifstream fichier( GameManager::getInstance().getAppPath() + "\\..\\..\\files\\" + fileName, ios::in);

    if(fichier){

        string contenu;
        string formatImage;
        int heightImage;
        int widthImage;
        int nbColor;

        fichier >> formatImage >> heightImage >> widthImage >> nbColor;

        this->heightMap = (unsigned int) heightImage;
        this->widthMap = (unsigned int) widthImage;

        for(int i = 0; i < heightImage; i++){
            carteId.push_back( vector<int>() );
            for(int j = 0; j < widthImage; j++){
                int r, g, b;
                fichier >> r;
                fichier >> g;
                fichier >> b;

                if(r == 0 && g == 0 && b == 0){
                    carteId[i].push_back( 0 );
                }
                else if(r == 255 &&g == 255 &&b == 255){
                    carteId[i].push_back( 1 );
                }
                else if(r == 255 && g == 0 && b == 0) {
                    carteId[i].push_back( 2 );
                }
                else if(r == 0 && g == 255 && b == 0){
                    carteId[i].push_back( 3 );
                }
                else {
                    carteId[i].push_back( -1 ); // Valeur inattendue
                }

            }
        }

        associationCell(heightImage, widthImage);
    }
    else{
        cerr << "Impossible d'ouvrir le fichier de la map" << endl;
    }
}

void Niveau::associationCell(int heightImage, int widthImage) {

    float x = 0;
    float z = 0;

    for (int i = 0; i < heightImage; i++) {
        cellules.push_back(vector<Cell>());
        for (int j = 0; j < widthImage; j++) {

            if (carteId[i][j] == 0) {
                Cell cellule(carteId[i][j], x, -1, z, "wood.jpg");
                cellules[i].push_back(cellule);
            } else if (carteId[i][j] == 1) {
                Cell cellule(carteId[i][j], x, -2, z, "sol.jpg");
                cellules[i].push_back(cellule);
            } else if (carteId[i][j] == 2) {
                Cell cellule(carteId[i][j], x, -2, z, "sol.jpg");
                cellules[i].push_back(cellule);
            } else if (carteId[i][j] == 3) {
                Cell cellule(carteId[i][j], x, -2, z, "sol.jpg");
                cellules[i].push_back(cellule);
            }

            x+=1;
        }
        z+=1;
    }
}

Niveau::~Niveau() {

}

vector<vector<int> > Niveau::getCarteId(void) {
    return carteId;
}

vector<vector<Cell> > Niveau::getCellules(void) {
    return cellules;
}

unsigned int Niveau::getHeightMap(void) {
    return this->heightMap;
}

unsigned int Niveau::getWidthMap(void) {
    return this->widthMap;
}

void Niveau::createMap(void) {

    for(int i = 0; i < heightMap; i++){
        for(int j = 0; i < widthMap; i++){
            Cube3D * cube = new Cube3D(cellules[i][j].getTextureName());
            cube->setTranslation(cellules[i][j].getPosition()[0], cellules[i][j].getPosition()[1], cellules[i][j].getPosition()[2]);
        }
    }
}




