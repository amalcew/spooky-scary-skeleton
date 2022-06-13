#pragma once

#include "meshmodel.h"

// rozszerzenie klasy MeshModel specjalnie pod szkieleta
class MeshModelSkeleton : public MeshModel
{
protected:
    const int TORSO = 0;
    const int ARM_R = 1;
    const int ARM_L = 2;
    const int LEG_R = 3;
    const int LEG_L = 4;
    const int HEAD  = 5;


    // przesuniêcia meshów
    std::vector<glm::vec3> translations;

    struct keyframe {
        float time;         // punkt w czasie dla keyframe'a
        glm::mat4 transform;// transformacje w danym momencie
    };
    typedef std::vector<keyframe> keyframesequence;

    // sekwencja keyframe'ów dla ka¿dego mesha
    std::vector<keyframesequence> sequences;
    double current_time = 0;
    double animation_length;

    virtual void setupAnimation();
    glm::mat4 getTransformation(int index, double time);
    glm::mat4 interpolate(glm::mat4& m1, glm::mat4& m2, float tdif);
public:

    virtual void loadModel(std::string path);
    virtual void drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time);

};

