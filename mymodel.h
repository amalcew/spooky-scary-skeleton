#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "mesh.h"

class mymodel
{
public:
	std::vector<Mesh> meshes;

	int meshNum;

	ShaderProgram* sp;

	GLuint tex0;
	GLuint tex1;
	mymodel(std::string path);
	void drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam);

	GLuint readTexture(const char* filename);

};

