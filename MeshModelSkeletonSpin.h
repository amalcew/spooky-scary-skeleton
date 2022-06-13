#pragma once
#include "meshmodelskeleton.h"
class MeshModelSkeletonSpin :
    public MeshModelSkeleton
{
private:
    void setupAnimation();

    float spindeg = 0.0f;
public:
    void drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time);
};

