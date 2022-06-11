#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class custom_camera
{
private:
	glm::vec3 lookingAt;
	glm::vec3 up;

	double angleX;
	double angleY;
	double R;

	double speedX;
	double speedY;
	double speedR;

	double minR;
	double maxR;
	double minAngY;
	double maxAngY;

	void compute_position();
public:
	glm::vec3 position;

	custom_camera();
	custom_camera(glm::vec3);

	glm::mat4 getViewMatrix();
	void set_position(glm::vec3);

	void moveX(double);
	void moveY(double);
	void moveR(double);

	void debug();
};

