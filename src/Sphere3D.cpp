//
// Created by Vincent on 13/12/2016.
//


#include "../include/Sphere3D.h"

Sphere3D::Sphere3D(SDLWindowManager windowManager) {

    //charge les shaders que l'on a ajouté dans le dossier shaders
    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\normals.fs.glsl");

    std::unique_ptr<Image> ImE = loadImage("..\\..\\assets\\textures\\EarthMap.jpg");
    std::unique_ptr<Image> ImM = loadImage("..\\..\\assets\\textures\\MoonMap.jpg");

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;

    GLint  uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint  uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint  uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    projMatrix = glm::perspective<float>(glm::radians(70.f), 800/800 ,0.1f,100.f); // 800/800 ==> window ratio
    mvMatrix = glm::translate<float>(glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1), glm::vec3(0.f,0.f,-5.f));
    normalMatrix = glm::transpose(glm::inverse(mvMatrix));

    sphere = Sphere(1, 32, 16);

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    //Debinder glBindBufer avec second para 0
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //création VAO : pour pouvoir interpreter les données du VBO
    //creation comme gen vbo
    GLuint vao;
    glGenVertexArrays(1, &vao);


    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    //activation des attributs de vertex, prend en para l'index renseignant le type de data
    //on prefere les déclarer auparavant dans des constantes plutot que en clair

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCORD);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) (offsetof(ShapeVertex, position)));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) (offsetof(ShapeVertex, normal)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) (offsetof(ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Application loop:
    bool done = false;
    std::vector<glm::vec3> nbRand;
    for(int i = 0; i <32 ; i++){
        nbRand.push_back(glm::sphericalRand(20.f));
    }
    while (!done) {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e)) {
            if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        //Nettoyer la fenetre, para indique ce qu'il faut nettoyer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //envoyer les matrices
        glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(projMatrix * mvMatrix));
        glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(mvMatrix));
        glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));


        //Dessiner avec le VAO
        glBindVertexArray(vao);
        /*	glDrawArrays(GLenum mode, GLint first, GLsizei count);

               Paramètres:

                      GLenum mode: le type de primitive à dessiner, dans notre cas GL_TRIANGLES
                      GLint first: l'indice du premier sommet dans le VBO. On passe 0.
                   GLsizei count: le nombre de sommets à dessiner, on passe 3 car on veut dessiner un triangle qui est composé de 3 sommets. Si on voulait dessiner plus de triangles il faudrait changer ce paramètre.

       */
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

        glBindVertexArray(0);



        for(int i =0;i<32;i++){
            glm::mat4 MVMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            MVMatrix2 = glm::rotate(MVMatrix2, windowManager.getTime()/i, nbRand[i]); // Translation * Rotation
            MVMatrix2 = glm::translate(MVMatrix2, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
            MVMatrix2 = glm::scale(MVMatrix2, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

            glm::mat4 NormalMatrix2;
            NormalMatrix2 = glm::transpose(glm::inverse(MVMatrix2));


            glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(projMatrix * MVMatrix2));
            glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(MVMatrix2));
            glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(NormalMatrix2));
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
            glBindVertexArray(0);
        }



        // Update the display
        windowManager.swapBuffers();
    }


}

void Sphere3D::draw() {

    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    //envoyer les matrices
    glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(projMatrix * mvMatrix));
    glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(mvMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));


    //Dessiner avec le VAO
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

    glBindVertexArray(0);

}

void Sphere3D::setTransform(glm::mat4 transformMatrix) {
    this->modelMatrix = transformMatrix;
}

void Sphere3D::addTransform(glm::mat4 transformMatrix) {
    this->modelMatrix = transformMatrix * this->modelMatrix;
}
