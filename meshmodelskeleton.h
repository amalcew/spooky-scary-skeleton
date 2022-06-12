#pragma once

#include "meshmodel.h"

// rozszerzenie klasy MeshModel specjalnie pod szkieleta
class MeshModelSkeleton : public MeshModel
{
public:

    std::vector<glm::vec3> positions;
    virtual void loadModel(std::string path);
    virtual void drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam);
};

