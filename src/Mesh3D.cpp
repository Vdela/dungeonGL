//
// Created by Vincent on 26/12/2016.
//

#include "../include/Mesh3D.h"
#include "../include/Player.h"
#include "../include/Texture.h"

using namespace glimac;


Mesh3D::Mesh3D(std::string meshName, std::string meshMtl, std::string textureName) {

    if ( Texture::textures[ textureName ] == NULL ) {
        Texture * texture = new Texture(textureName);
    }

    if ( MeshShared::meshesMap[ meshName + textureName ] == NULL ) {
        MeshShared * meshShared = new MeshShared( meshName, meshMtl, Texture::textures[ textureName ] );
    }

    this->meshShared = MeshShared::meshesMap[ meshName + textureName ];
    this->texture = Texture::textures[ textureName ];

}

void Mesh3D::draw() {
    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/



    // Transformations

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;


    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

    shaderProgram.program.use();

    glUniformMatrix4fv( shaderProgram.uMVPMatrixLoc ,1,GL_FALSE,glm::value_ptr( projMatrix
                                                                                * Player::getInstance().camera.getViewMatrix()
                                                                                * (*parentModel)
                                                                                * modelMatrix ) );

    glUniformMatrix4fv( shaderProgram.uMVMatrixLoc,1,GL_FALSE,glm::value_ptr((*parentModel) * modelMatrix));
    glUniformMatrix4fv( shaderProgram.uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));

    glm::vec3 camPos = Player::getInstance().camera.getPosition();
    glUniform3f( shaderProgram.uLightPosLoc, camPos.x, camPos.y, camPos.z );
    glUniform3f( shaderProgram.uLightIntensityLoc, 1,1,1 ); // white

    glBindVertexArray( meshShared->vao);

    glBindTexture( GL_TEXTURE_2D, texture->textId );
    glDrawElements(GL_TRIANGLES, meshShared->geometry.getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindTexture( GL_TEXTURE_2D, 0 );

    glBindVertexArray(0);

}
