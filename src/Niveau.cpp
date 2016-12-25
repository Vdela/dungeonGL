//
// Created by Irene on 23/12/2016.
//

#include "../include/Niveau.h"

Niveau::Niveau(){}

void Niveau::lectureMap(char* fileName){

    glimac::FilePath applicationPath(".\\opengl.exe");

    ifstream fichier(applicationPath.dirPath() + "\\..\\..\\files\\" + fileName, ios::in);

    if(fichier){

        string contenu;
        string formatImage;
        int heightImage;
        int widthImage;
        int nbColor;

        fichier >> formatImage >> heightImage >> widthImage >> nbColor;

        for(int i = 0; i < heightImage; i++){
            carte.push_back( vector<int>() );
            for(int j = 0; j < widthImage; j++){
                int r, g, b;
                fichier >> r;
                fichier >> g;
                fichier >> b;

                if(r == 0 && g == 0 && b == 0){
                    carte[i].push_back( 0 );
                }
                else if(r == 255 &&g == 255 &&b == 255){
                    carte[i].push_back( 1 );
                }
                else if(r == 255 && g == 0 && b == 0) {
                    carte[i].push_back( 2 );
                }
                else if(r == 0 && g == 255 && b == 0){
                    carte[i].push_back( 3 );
                }
                else {
                    carte[i].push_back( -1 ); // Valeur inattendue
                }

            }
        }
    }
    else{
        cerr << "Impossible d'ouvrir le fichier de la map" << endl;
    }

    /*cout << carte[0][0] << carte[0][1] << carte[0][2] << carte[0][3] << endl;
    cout << carte[1][0] << carte[1][1] << carte[1][2] << carte[1][3] << endl;
    cout << carte[2][0] << carte[2][1] << carte[2][2] << carte[2][3] << endl;
    cout << carte[3][0] << carte[3][1] << carte[3][2] << carte[3][3] << endl;*/
}



