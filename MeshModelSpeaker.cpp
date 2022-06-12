#include "MeshModelSpeaker.h"

void MeshModelSpeaker::setupAnimation()
{
    sequences = std::vector<keyframesequence>(meshes.size());

    animation_length = 10;

    keyframe kf;
    keyframesequence kfs;
    glm::mat4 M0 = glm::mat4(1);
    glm::mat4 M;

    // ===================================                         TORS
    kfs.clear();                // wyczyœæ sekwencjê


    kf.time = 0;               
    kf.transform = M0;       
    kf.transform = glm::translate(kf.transform, glm::vec3(0.0, 0.3, 0.0));
    kfs.push_back(kf);  

    kf.time = 5;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kfs.push_back(kf);          // wstaw klatkê do sekwencji
        

    for(int i = 0; i < meshes.size(); ++i)
        sequences[i] = kfs;     // wstaw sekwencjê dla meshu
}

void MeshModelSpeaker::loadModel(std::string path) {

    MeshModel::loadModel(path);

    for (int i = 0; i < meshes.size(); ++i)
        translations.push_back(glm::vec3(0.0, 1.10573, 0.0));

    setupAnimation();
}

glm::mat4 MeshModelSpeaker::interpolate(glm::mat4& m1, glm::mat4& m2, float tdif)
{
    glm::quat rot0 = glm::quat_cast(m1);
    glm::quat rot1 = glm::quat_cast(m2);

    glm::quat finalRot = glm::slerp(rot0, rot1, tdif);

    glm::mat4 finalMat = glm::mat4_cast(finalRot);

    finalMat[3] = m1[3] * (1 - tdif) + m2[3] * tdif;

    return finalMat;
}

// oblicz transformacjê dla meshu (interpolacja)
glm::mat4 MeshModelSpeaker::getTransformation(int index, double time) {
    int len = sequences[index].size();
    if (len == 1) // nie interpoluj jak jest tylko jeden element
        return sequences[index][0].transform;

    int nexti = 0;
    double nextt = 0;
    for (int i = 0; i < len; ++i) {
        // zapêtl animacjê
        time = fmodf(time, animation_length);
        //printf("time: %lf\n", time);

        if (sequences[index][i].time == time) // jeœli trafi³ idealnie czas, to nie interpoluj
            return sequences[index][i].transform;

        // znajdŸ czas nastêpnej klatki
        nexti = (i + 1) % len;
        if (nexti == 0) nextt = animation_length;
        else nextt = sequences[index][nexti].time;

        // jeœli t_obecny < time < t_nastepny
        // to interpoluj
        if (sequences[index][i].time < time && nextt > time) {
            //glm::mat4 interpolate(glm::mat4 & _mat1, glm::mat4 & _mat2, float _time)
            //{
            float tdif = (time - sequences[index][i].time) / (nextt - sequences[index][i].time);

            glm::mat4 mat = interpolate(sequences[index][i].transform, sequences[index][nexti].transform, tdif);

            float scale = 1.0;
            float mult = 0.3;
            if (i == 0) scale += mult * (1.0 - tdif);
            else scale += mult * tdif;

            return glm::scale(mat, glm::vec3(scale, scale, scale));

            //}
        }
    }

    return glm::mat4(1); // nigdy nie powinno siê zdarzyæ
}



void MeshModelSpeaker::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time) {

    int len = meshes.size();
    for (int i = 0; i < len; ++i) {
        glm::mat4 Mt = glm::translate(M, translations[i]) * getTransformation(i, current_time);
        meshes[i].drawMesh(V, P, Mt, cam, time);
    }

    current_time += time * 20;
    current_time = fmodf(current_time, animation_length);

    //printf("Current time: %lf\n", current_time);
}