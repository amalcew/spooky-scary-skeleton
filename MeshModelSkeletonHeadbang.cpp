#include "MeshModelSkeletonHeadbang.h"

void MeshModelSkeletonHeadbang::setupAnimation()
{
    sequences = std::vector<keyframesequence>(meshes.size());

    animation_length = 10;

    keyframe kf;
    keyframesequence kfs;
    glm::mat4 M0 = glm::mat4(1);
    glm::mat4 M;

    // ===================================                         TORS
    kfs.clear();                // wyczyœæ sekwencjê
    kf.time = 0;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kfs.push_back(kf);          // wstaw klatkê do sekwencji

    kf.time = 4;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 6;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 9;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kfs.push_back(kf);

    sequences[TORSO] = kfs;     // wstaw sekwencjê dla meshu


    // ===================================                         PRAWA RÊKA
    kfs.clear();  

    kf.time = 0;
    kf.transform = glm::translate(M0, glm::vec3(0.0, -0.1, 0.0));           
    kf.transform = glm::rotate(kf.transform, glm::radians(255.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 1;
    kf.transform = glm::translate(M0, glm::vec3(0.0, -0.1, 0.0));           
    kf.transform = glm::rotate(kf.transform, glm::radians(255.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 4;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 6;
    kf.transform = M0;
    kf.transform = glm::rotate(kf.transform, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 9;
    kf.transform = glm::translate(M0, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(255.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[ARM_R] = kfs;


    // ===================================                         LEWA RÊKA
    kfs.clear();

    kf.time = 0;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(7.0f), glm::vec3(0.0, 0.0, 1.0));
    kfs.push_back(kf);          // wstaw klatkê do sekwencji

    kf.time = 4;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 6;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 9;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(kf.transform, glm::radians(7.0f), glm::vec3(0.0, 0.0, 1.0));
    kfs.push_back(kf);

    sequences[ARM_L] = kfs;


    // ===================================                         PRAWA NOGA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);

    sequences[LEG_R] = kfs;


    // ===================================                         LEWA NOGA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);

    sequences[LEG_L] = kfs;


    // ===================================                         G£OWA
    kfs.clear();

    kf.time = 0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(M0, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 1;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(M0, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    kf.time = 4;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 6;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 9;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, -0.1, 0.0));
    kf.transform = glm::rotate(M0, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
    kfs.push_back(kf);

    sequences[HEAD] = kfs;
}
