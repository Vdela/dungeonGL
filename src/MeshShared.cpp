//
// Created by Vincent on 28/12/2016.
//

#include "../include/MeshShared.h"
#include "../include/Player.h"
#include "../include/Texture.h"


using namespace glimac;

std::map<std::string,MeshShared*> MeshShared::meshesMap = std::map<std::string,MeshShared*>();

MeshShared::MeshShared(std::string meshName, std::string meshMtl, Texture * texture) {

    FilePath path(".\\opengl.exe");
    geometry.loadOBJ( path.dirPath() + "\\..\\..\\assets\\models\\" + meshName,
                      path.dirPath() + "\\..\\..\\assets\\models\\" + meshMtl,
                      true
    );

    shaderProgram = SimpleTextureLambert();

    //********************************
    //HERE SHOULD COME THE INITIALIZATION CODE
    //*********************************

    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, geometry.getVertexCount()*sizeof(Geometry::Vertex), geometry.getVertexBuffer(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.getIndexCount() * sizeof(const unsigned int), geometry.getIndexBuffer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCORD);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*)( offsetof(Geometry::Vertex, m_Position) ) );
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*)( offsetof(Geometry::Vertex, m_Normal) ) );
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*)( offsetof(Geometry::Vertex, m_TexCoords) ) );
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);


    // Chargement Texture
    std::unique_ptr<Image> textureImg = loadImage( path.dirPath() + "\\..\\..\\assets\\textures\\" + texture->textureName);

    if ( textureImg == NULL ) {
        std::cerr << "IMAGE NOT FOUND!" << std::endl;
    }

    glGenTextures( 1, &texture->textId );
    glBindTexture( GL_TEXTURE_2D, texture->textId );
    glTexImage2D( GL_TEXTURE_2D, 0, 4, textureImg->getWidth(), textureImg->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImg->getPixels() );


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    meshesMap[meshName + texture->textureName] = this;

}
