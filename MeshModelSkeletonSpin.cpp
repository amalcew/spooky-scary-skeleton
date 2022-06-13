#include "MeshModelSkeletonSpin.h"

void MeshModelSkeletonSpin::setupAnimation()
{
    sequences = std::vector<keyframesequence>(meshes.size());

    animation_length = 10;

    keyframe kf;
    keyframesequence kfs;
    glm::mat4 M0 = glm::mat4(1);
    glm::mat4 M;

    float kf0 = 0;
    float kf1 = 5;

    // ===================================                         TORS
    kfs.clear();                // wyczyœæ sekwencjê
    kf.time = 0;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kfs.push_back(kf);          // wstaw klatkê do sekwencji

    sequences[TORSO] = kfs;     // wstaw sekwencjê dla meshu

    // ===================================                         PRAWA RÊKA
    kfs.clear();

    kf.time = kf0;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = kf1;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(-30.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[ARM_R] = kfs;


    // ===================================                         LEWA RÊKA
    kfs.clear();

    kf.time = kf0;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = kf1;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[ARM_L] = kfs;


    // ===================================                         PRAWA NOGA
    kfs.clear();

    kf.time = kf0;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = kf1;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(-20.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[LEG_R] = kfs;


    // ===================================                         LEWA NOGA
    kfs.clear();

    kf.time = kf0;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = kf1;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(20.0f), glm::vec3(0.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(-25.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[LEG_L] = kfs;


    // ===================================                         G£OWA
    kfs.clear();

    kf.time = kf0;
    kf.transform = M0;
    kfs.push_back(kf);

    sequences[HEAD] = kfs;
}

void MeshModelSkeletonSpin::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time) {

    int len = meshes.size();

    glm::mat4 newM = glm::translate(M, glm::vec3(0.0, 2.3466, 0.0));
    newM = glm::rotate(newM, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    newM = glm::rotate(newM, glm::radians(spindeg), glm::vec3(0.0, 1.0, 0.0));

    for (int i = 0; i < len; ++i) {
        glm::mat4 Mt = glm::translate(newM, translations[i]) * getTransformation(i, current_time);
        meshes[i].drawMesh(V, P, Mt, cam, time);
    }

    current_time += time * 20;
    spindeg += time * 450;
    current_time = fmodf(current_time, animation_length);
    spindeg = fmodf(spindeg, 360.0f);

    //printf("Current time: %lf\n", current_time);
}
