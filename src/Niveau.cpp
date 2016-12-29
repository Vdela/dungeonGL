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

        fichier >> formatImage >> widthImage >> heightImage >> nbColor;

        this->heightMap = (unsigned int) heightImage;
        this->widthMap = (unsigned int) widthImage;
        int i, j; // i=largeur, j=hauteur
        for(i = 0; i < heightImage; i++){
            carteId.push_back( vector<CellType>() );
            for(j = 0; j < widthImage; j++){
                int r, g, b;
                fichier >> r;
                fichier >> g;
                fichier >> b;

                if(r == 0 && g == 0 && b == 0){
                    carteId[i].push_back( CellType::Wall );
                }
                else if(r == 255 &&g == 255 &&b == 255){
                    carteId[i].push_back( CellType::Floor );
                }
                else if(r == 255 && g == 0 && b == 0) {
                    carteId[i].push_back( CellType::Start );
                }
                else if(r == 0 && g == 255 && b == 0){
                    carteId[i].push_back( CellType::End );
                }
                else if(r == 0 && g == 0 && b == 255){
                    carteId[i].push_back( CellType::Water );
                }
                else {
                    carteId[i].push_back( CellType::EmptyCell ); // Autre couleur
                }

            }
        }
    }
    else{
        cerr << "Impossible d'ouvrir le fichier de la map" << endl;
    }
}

Niveau::~Niveau() {

}

vector<vector<CellType> > Niveau::getCarteId(void) {
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

void Niveau::setNbTresors(unsigned int nbTresors){
    this->nbTresors = nbTresors;
}

void Niveau::setNbMonstres(unsigned int nbMonstres){
    this->nbMonstres = nbMonstres;
}

void Niveau::createMap(void) {

    for(int i = 0; i < heightMap; i++){
        cellules.push_back( std::vector<Cell>() );
        for(int j = 0; j < widthMap; j++){

            switch ( carteId[i][j] ) {
                case CellType::Wall : {
                    Mesh3D * wall = new Mesh3D( "wall.obj", "wall.mtl", "wood.jpg" );
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    wall->setTranslation( i, 0, j );
                    break;
                }
                case CellType::Floor : {
                    Mesh3D * floor = new Mesh3D( "quad.obj", "quad.mtl", "bone01.png" );
                    Mesh3D * ceiling = new Mesh3D( "quad.obj", "quad.mtl", "bone01.png" );
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    floor->setTranslation( i, -0.5f, j );
                    ceiling->setTranslation( i, 0.5f, j );
                    ceiling->setRotation( glm::vec3(1,0,0), 180 );
                    break;
                }
                case CellType::Water : {
                    Mesh3D * water = new Mesh3D( "quad.obj", "quad.mtl", "water.png" );
                    Mesh3D * ceiling = new Mesh3D( "quad.obj", "quad.mtl", "bone01.png" );
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    water->setTranslation( i, -0.8f, j );
                    ceiling->setTranslation( i, 0.5f, j );
                    ceiling->setRotation( glm::vec3(1,0,0), 180 );
                    if ( i > 0 && carteId[i-1][j] != CellType::Water) {
                        Mesh3D *border = new Mesh3D("quad.obj", "quad.mtl", "bone02.png");
                        border->setRotation(glm::vec3(0, 0, 1), 270);
                        border->setTranslation(i-0.5f, -1, j);
                    }
                    if ( i+1 < widthMap && carteId[i+1][j] != CellType::Water) {
                        Mesh3D *border = new Mesh3D("quad.obj", "quad.mtl", "bone02.png");
                        border->setRotation(glm::vec3(0, 0, 1), 90);
                        border->setTranslation(i+0.5f, -1, j);
                    }
                    if ( j > 0 && carteId[i][j-1] != CellType::Water) {
                        Mesh3D *border = new Mesh3D("quad.obj", "quad.mtl", "bone02.png");
                        border->setRotation(glm::vec3(1, 0, 0), 90);
                        border->setTranslation(i, -1, j-0.5f);
                    }
                    if ( j+1 < heightMap && carteId[i][j+1] != CellType::Water) {
                        Mesh3D *border = new Mesh3D("quad.obj", "quad.mtl", "bone02.png");
                        border->setRotation(glm::vec3(1, 0, 0), 270);
                        border->setTranslation(i, -1, j+0.5f);
                    }
                    break;
                }
                case CellType::Start : {
                    Mesh3D * floor = new Mesh3D( "quad.obj", "quad.mtl", "water.png" );
                    Mesh3D * ceiling = new Mesh3D( "quad.obj", "quad.mtl", "bone02.png" );
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    floor->setTranslation( i, -0.5f, j );
                    ceiling->setTranslation( i, 0.5f, j );
                    ceiling->setRotation( glm::vec3(1,0,0), 180 );
                    startPos = glm::vec2( i, j );
                    break;
                }
                case CellType::End : {
                    Mesh3D * floor = new Mesh3D( "quad.obj", "quad.mtl", "bone02.png" );
                    Mesh3D * ceiling = new Mesh3D( "quad.obj", "quad.mtl", "water.png" );
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    floor->setTranslation( i, -0.5f, j );
                    ceiling->setTranslation( i, 0.5f, j );
                    ceiling->setRotation( glm::vec3(1,0,0), 180 );
                    endPos = glm::vec2( i, j );
                    break;
                }
                case CellType::EmptyCell : {
                    Cell cellule(carteId[i][j], i, j);
                    cellules[i].push_back(cellule);
                    break;
                }
                default:
                    break;
            }

        }
    }

}

vector<Monstre> Niveau::getMonstres(void) {
    return monstres;
}

vector<Tresor> Niveau::getTresors(void) {
    return tresors;
}


