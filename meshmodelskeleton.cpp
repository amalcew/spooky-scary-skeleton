#include "meshmodelskeleton.h"

void MeshModelSkeleton::loadModel(std::string path) {

    MeshModel::loadModel(path);

    // domy�lnie wszystkie cz�ci s� ustawione tak, aby origin mia�y na 0,0,0
    // w celu �atwiejszego obracania. P�niej nale�y je przesuj�� na odpowiednie miejsce
    positions.push_back(glm::vec3(0.0, 0.0, 0.0)); // tors
    positions.push_back(glm::vec3(-0.49034, 1.6849, 0.0)); // prawa reka
    positions.push_back(glm::vec3(0.493008, 1.69544, 0.0)); // lewa reka
    positions.push_back(glm::vec3(-0.240031, 0.772174, 0.0)); // prawa noga
    positions.push_back(glm::vec3(0.221428, 0.761388, 0.0));  // lewa noga
    positions.push_back(glm::vec3(0.0, 1.81003, 0.0));     // g�owa
}

void MeshModelSkeleton::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam) {

    int len = meshes.size();
    glm::mat4 meshM;
    for (int i = 0; i < len; ++i) {

        // zaaplikuj przesuni�cie meshu na w�a�ciwe miejsce
        meshM = glm::translate(M, positions[i]);

        if (i == 1) {
            glm::mat4 hm = glm::rotate(meshM, (float)glm::radians(-165.0), glm::vec3(0.0, 0.0, 1.0));
            meshes[i].drawMesh(V, P, hm, cam);

        }
        else
            meshes[i].drawMesh(V, P, meshM, cam);
    }
}