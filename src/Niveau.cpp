//
// Created by Irene on 23/12/2016.
//

#include "../include/Niveau.h"

Niveau::Niveau(){}

void Niveau::lectureMap(char* fileName){

    glimac::FilePath applicationPath(".\\opengl.exe");

    ifstream fichier(applicationPath.dirPath() + "\\..\\..\\files\\" + fileName, ios::in);

    //ifstream fichier(fileName, ios::in);

    if(fichier){

        string contenu;
        string formatImage;
        int heightImage;
        int widthImage;
        int nbColor;

        fichier >> formatImage >> heightImage >> widthImage >> nbColor;

        //cin.ignore();

        char valeur[3];


        for(int i = 0; i < heightImage; i++){
            carte.push_back( vector<int>() );
            for(int j = 0; j < widthImage; j++){
                for(int k = 0; k < 3; k++){fichier.get(valeur[k]);}
                if(valeur[0] == 0 && valeur[1] == 0 && valeur[2] == 0){
                    carte[i].push_back( 0 );
                }
                else if(valeur[0] == 255 && valeur[1] == 255 && valeur[2] == 255){
                    carte[i].push_back( 1 );
                }
                else if(valeur[0] == 255 && valeur[1] == 0 && valeur[2] == 0) {
                    carte[i].push_back( 2 );
                }
                else if(valeur[0] == 0 && valeur[1] == 255 && valeur[2] == 0){
                    carte[i].push_back( 3 );
                }
                else {
                    carte[i].push_back( -1 ); // Valeur innatendue
                }
            }
        }

        /*for(int i = 0; i < heightImage; i++){
            for(int j = 0; j < widthImage; j++){
                for(int k = 0; k < 3; k++){fichier.get(valeur[k]);}
                if(valeur[0] == 0 && valeur[1] == 0 && valeur[2] == 0){
                    carte[i][j] = 0;
                }
                else if(valeur[0] == 255 && valeur[1] == 255 && valeur[2] == 255){
                    carte[i][j] = 1;
                }
                else if(valeur[0] == 255 && valeur[1] == 0 && valeur[2] == 0) {
                    carte[i][j] = 2;
                }
                else if(valeur[0] == 0 && valeur[1] == 255 && valeur[2] == 0){
                    carte[i][j] = 3;
                }
            }
        }*/

    }
    else{
        cerr << "Impossible d'ouvrir le fichier de la map" << endl;
    }

    /*cout << carte[0][0] << carte[0][1] << carte[0][2] << carte[0][3] << endl;
    cout << carte[1][0] << carte[1][1] << carte[1][2] << carte[1][3] << endl;
    cout << carte[2][0] << carte[2][1] << carte[2][2] << carte[2][3] << endl;
    cout << carte[3][0] << carte[3][1] << carte[3][2] << carte[3][3] << endl;*/
}



