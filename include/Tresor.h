//
// Created by Irene on 28/12/2016.
//

#ifndef IMACGL_TRESOR_H
#define IMACGL_TRESOR_H

#include <string>

using namespace std;

class Tresor{
private:
    unsigned int id;
    float position[3];
    string nom;
    int type;
    int caracteristique;
    string Modele3Dobj;
    string Modele3Dmtl;

public:
    Tresor();
    Tresor(unsigned int id, float x, float y, float z, string nom, int type, int caracteristique, string Modele3Dobj, string Modele3Dmtl);
    ~Tresor();

    unsigned int getId(void);
    void setId(unsigned int id);

    float* getPosition(void);
    void setPosition(float x, float y, float z);

    string getNom(void);
    void setNom(string nom);

    int getType(void);
    void setType(int type);

    int getCaracteristique(void);
    void setCaracteristique(int caracteristique);

    string getModele3Dobj();
    void setModele3Dobj(string Modele3Dobj);

    string getModele3Dmtl();
    void setModele3Dmtl(string Modele3Dmtl);
};

#endif //IMACGL_TRESOR_H
