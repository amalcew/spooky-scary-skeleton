#ifndef SPOOKY_SCARY_SKELETON_MESHMODEL_H
#define SPOOKY_SCARY_SKELETON_MESHMODEL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"


class MeshModel {
public:
    MeshModel() {};
    //~MeshModel();
    GLuint readTexture(const char* filename);
    void drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam);
    void loadModel(std::string path);
private:
    // void initFromScene(const aiScene* scene, std::string path)
    void initSingleMesh(const aiMesh* singleMesh);
    void initAllMeshes(const aiScene* scene);
    void freeMemory();

    int meshNum;

    ShaderProgram* sp;

    GLuint tex0;
    GLuint tex1;

    std::vector<glm::vec4> verts;
    std::vector<glm::vec4> norms;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices;
};

#endif //SPOOKY_SCARY_SKELETON_MESHMODEL_H