#include "custom_camera.h"

// ustawianie pozycji kamery
void custom_camera::set_position(glm::vec3 start, glm::vec3 offset) {
	position = start;
	lookingAt = glm::vec3(0.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);

	double allspeed = 100;
	speedX = allspeed;
	speedY = allspeed;
	speedR = allspeed/2;
	this->offset = offset;

	minR = 1;
	maxR = 10000000;
	minAngY = 0.1;
	maxAngY = 179.9;

	// wyliczanie k¹tów z pozycji
	if (position.x == 0) {
		if(position.z >= 0) angleX = 0.0;
		else angleX = 180.0;
	}
	else angleX = atanf(position.z / position.x);

	if (position.y == 0) angleY = 90.0;
	else angleY = atanf(position.x / position.y);

	// obliczanie odleg³oœci miêdzy kamer¹ a punktem 
	R = glm::distance(position, lookingAt);

	if (R < minR) R = minR;
	else if (R > maxR) R = maxR;

	// compute_position();
}

custom_camera::custom_camera() {
	set_position(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0));
}

custom_camera::custom_camera(glm::vec3 start, glm::vec3 offset) {
	set_position(start, offset);
}

// zwróæ macierz V
glm::mat4 custom_camera::getViewMatrix()
{
	return glm::lookAt(position + offset, lookingAt + offset, up);
}

// zmieñ odleg³oœæ od punktu który patrzysz
void custom_camera::moveR(double time) {
	R += time * speedR;
	if (R < minR) R = minR;
	else if (R > maxR) R = maxR;
	compute_position();
}

// obróæ siê po p³aszczyŸnie poziomej
void custom_camera::moveX(double time) {
	angleX += time * speedX;
	if (angleX >= 360.0) angleX = 0.0;
	else if (angleX < 0.0) angleX += 360.0;
	compute_position();
}

// obróæ siê góra/dó³
void custom_camera::moveY(double time) {
	angleY += time * speedY;
	if (angleY < minAngY) angleY = minAngY;
	else if (angleY > maxAngY) angleY = maxAngY;
	compute_position();
}

// oblicz pozycjê po zmianie obrotu
void custom_camera::compute_position() {
	double angleXRad = glm::radians(angleX);
	double angleYRad = glm::radians(angleY);

	position.x = R * sinf(angleXRad) * sinf(angleYRad);
	position.y = R * cosf(angleYRad);
	position.z = R * cosf(angleXRad) * sinf(angleYRad);
}

// wypisz informacje - debug
void custom_camera::debug() {
	printf("Cam: (x: %lf, y: %lf, z: %lf )\n",
		position.x, position.y, position.z);
	printf("Obrot: angX: %lf, angY: %lf, R: %lf\n\n",
		angleX, angleY, R);
}