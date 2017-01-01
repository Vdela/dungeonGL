//
// Created by Vincent on 14/12/2016.
//

#include "../include/Object3D.h"

//map<string, Node*> Node::nodesMap = map<string, Node*>();
std::vector<Object3D*> Object3D::sceneObjects = std::vector<Object3D*>();

// Matrice de projection, à utiliser pour obtenir une projection en 3D des objets
glm::mat4 const Object3D::projMatrix = glm::perspective<float>(glm::radians(70.f),1.0,0.1f,100.f);

GLuint Object3D::programID; // Doit être set depuis GameManager

Object3D::Object3D() {
    sceneObjects.push_back( this );
    parentModel = new glm::mat4();
}

void Object3D::setTranslation(glm::vec3 translation) {
    this->translationMatrix = glm::translate( glm::mat4(1), translation );
}

void Object3D::addTranslation(glm::vec3 translation) {
    this->translationMatrix *= glm::translate( glm::mat4(1), translation );
}

void Object3D::setTranslation(float x, float y, float z) {
    this->translationMatrix = glm::translate( glm::mat4(1), glm::vec3(x,y,z) );
}

void Object3D::addTranslation(float x, float y, float z) {
    this->translationMatrix *= glm::translate( glm::mat4(1), glm::vec3(x,y,z) );
}


void Object3D::setRotation(glm::vec3 rotation, float angleDegree) {
    this->rotationMatrix = glm::rotate(glm::mat4(), (float)(angleDegree * PI/180), rotation);
}

void Object3D::addRotation(glm::vec3 rotation, float angleDegree) {
    this->rotationMatrix *= glm::rotate(glm::mat4(), (float)(angleDegree * PI/180), rotation);
}

void Object3D::setScale(glm::vec3 scale) {
    this->scaleMatrix = glm::scale(glm::mat4(), scale);
}

void Object3D::setScale(float x, float y, float z) {
    this->scaleMatrix = glm::scale( glm::mat4(), glm::vec3(x, y, z) );
}

void Object3D::setScale(float xyz) {
    this->scaleMatrix = glm::scale( glm::mat4(), glm::vec3(xyz, xyz, xyz) );
}

void Object3D::addScale(glm::vec3 scale) {
    this->scaleMatrix *= glm::scale(glm::mat4(), scale);
}

void Object3D::addScale(float x, float y, float z) {
    this->scaleMatrix *= glm::scale( glm::mat4(), glm::vec3(x, y, z) );
}

void Object3D::eraseObject3D(Object3D *object) {
    std::vector<Object3D*>::iterator position = std::find(sceneObjects.begin(), sceneObjects.end(), object);
    if (position != sceneObjects.end())
        sceneObjects.erase(position);

}
