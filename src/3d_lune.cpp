#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include <SDL/SDL.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

int main(int argc, char **argv) {

    // Initialize SDL and open a window
    float largeur = 800;
    float hauteur = 800;
    SDLWindowManager windowManager(largeur, hauteur, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return 1;
    }

    //charge les shaders que l'on a ajouté dans le dossier shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\normals.fs.glsl");


    program.use();

    std::unique_ptr<Image> ImE = loadImage("..\\..\\assets\\textures\\EarthMap.jpg");
    std::unique_ptr<Image> ImM = loadImage("..\\..\\assets\\textures\\MoonMap.jpg");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;

    GLint  uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint  uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint  uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    glEnable(GL_DEPTH_TEST);

    glm::mat4 ProjMatrix;
    ProjMatrix = glm::perspective<float>(glm::radians(70.f),largeur/hauteur,0.1f,100.f);
    glm::mat4 MVMatrix;
    MVMatrix = glm::translate<float>(glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1), glm::vec3(0.f,0.f,-5.f));
    glm::mat4 NormalMatrix;
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    Sphere sphere(1, 32, 16);
    //sphere.getVertexCount();//nb sommets
    //sphere.getDataPointer(); // tab de sommets

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    /*Binding VBO ->GL_ARRAYY_BUFFER
    glBindBuffer(GLenum target, GLuint buffer)
                nom de la cible , buffer à binder
    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);



    /*Remplir VBO
    lBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)

   Paramètres:

   GLenum target: la cible sur laquelle le buffer est bindé (GL_ARRAY_BUFFER dans notre cas)
      GLsizeiptr size: la taille du tableau en octets. C'est le nombre de flottants multiplié par la taille d'un float (sizeof(float)).
      const GLvoid* data: le pointeur vers les données, notre tableau de flottants.
   GLenum usage: un flag indiquant à OpenGL quel usage on va faire du buffer. On utilise GL_STATIC_DRAW pour un buffer dont les données ne changeront jamais.


    */
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


    //spécification des attributs de vertex
    /*glVertexAttribPointer(GLuint index,
            GLint size, GLenum type, GLboolean normalized,
            GLsizei stride, const GLvoid* pointer);

    Paramètres:

    GLuint index: l'index de l'attribut à spécifier
    GLint size: le nombre de composantes de l'attribut. Dans notre cas c'est 2 car chaque position est décrite par deux nombres flottants.
    GLenum type: une constante OpenGL indiquant le type de chaque composante. Dans notre cas on passe GL_FLOAT pour indiquer que chaque composante est un nombre flottant.
    GLboolean normalized: pas besoin de s'occuper de ce paramètre pour le moment, on passe GL_FALSE
    GLsizei stride: indique à OpenGL le nombre d'octets séparant l'attribut pour deux sommets consécutifs. Ca ne veut rien dire ? oui je sais. Imaginez vous être OpenGL. Vous venez de lire une position dans le tableau. Vous avez besoin de savoir ou est situé la position suivante. Dans notre cas elle est juste après, il faut donc avancer de deux flottants, soit 2 * sizeof(GLfloat) octets. Nous verrons dans l'exercice suivant que la position suivante peut être situé plus loin dans le tableau lorsqu'on rajoute des attributs de sommet.
    const GLvoid* pointer: un pointeur, ou pas. Ce paramètre est un piège. Il faut en fait passer l'offset (décalage) en octets de la premiere instance de l'attribut dans le tableau. OK, ça ne veut encore rien dire. Dans notre cas, la première position est située au début du tableau, l'offset est donc 0.
    */

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
        glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(NormalMatrix));


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


            glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix2));
            glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(MVMatrix2));
            glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(NormalMatrix2));
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
            glBindVertexArray(0);
        }



        // Update the display
        windowManager.swapBuffers();
    }
    //liberation des ressources
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}
