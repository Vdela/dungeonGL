#pragma once

#include "glm.hpp"

namespace glimac {


class FreeflyCamera {

public:
    FreeflyCamera();
    void moveFront(float t);
	void moveLeft(float t);
    void rotateLeft(float degrees); 
    void rotateUp(float degrees);
    void computeDirectionVectors();
	glm::mat4 getViewMatrix() const;
	glm::vec3 getPosition() { return m_Position; }
	glm::vec3 setPosition(glm::vec3 pos) { m_Position = pos; }
	void setRotation(float degrees);

private:
	float m_fPhi;
	float m_fTheta;
	glm::vec3 m_Position;
	glm::vec3 m_FrontVector;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;
};
    
}