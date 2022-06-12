#include "meshmodelskeleton.h"

void MeshModelSkeleton::setupAnimation()
{
    sequences = std::vector<keyframesequence>(meshes.size());

    animation_length = 1;

    keyframe kf;
    keyframesequence kfs;
    glm::mat4 M0 = glm::mat4(1);
    glm::mat4 M;

    //tors
    kfs.clear();                // wyczyœæ sekwencjê
    kf.time = 0;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kfs.push_back(kf);          // wstaw klatkê do sekwencji
    sequences[TORSO] = kfs;     // wstaw sekwencjê dla meshu


    kfs.clear();

    kf.time = 0;
    kf.transform = glm::rotate(M0, (float)glm::radians(-165.0), glm::vec3(0.0, 0.0, 1.0));
    kfs.push_back(kf);

    kf.time = 0.5;
    kf.transform = glm::rotate(M0, (float)glm::radians(-185.0), glm::vec3(0.0, 0.0, 1.0));
    kfs.push_back(kf);


    kf.time = 0.75;
    kf.transform = glm::translate(M0, glm::vec3(0.0, 0.2, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-185.0), glm::vec3(0.0, 0.0, 1.0));
    kfs.push_back(kf);

    sequences[ARM_R] = kfs;


    kfs.clear();
    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);
    sequences[ARM_L] = kfs;


    kfs.clear();
    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);
    sequences[LEG_R] = kfs;


    kfs.clear();
    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);
    sequences[LEG_L] = kfs;


    kfs.clear();
    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);
    sequences[HEAD] = kfs;

}

void MeshModelSkeleton::loadModel(std::string path) {

    MeshModel::loadModel(path);

    // domyœlnie wszystkie czêœci s¹ ustawione tak, aby origin mia³y na 0,0,0
    // w celu ³atwiejszego obracania. PóŸniej nale¿y je przesuj¹æ na odpowiednie miejsce
    translations.push_back(glm::vec3(0.0, 0.0, 0.0)); // tors
    translations.push_back(glm::vec3(-0.49034, 1.6849, 0.0)); // prawa reka
    translations.push_back(glm::vec3(0.493008, 1.69544, 0.0)); // lewa reka
    translations.push_back(glm::vec3(-0.240031, 0.772174, 0.0)); // prawa noga
    translations.push_back(glm::vec3(0.221428, 0.761388, 0.0));  // lewa noga
    translations.push_back(glm::vec3(0.0, 1.81003, 0.0));     // g³owa

    setupAnimation();
}

glm::mat4 MeshModelSkeleton::interpolate(glm::mat4& m1, glm::mat4& m2, float tdif)
{
    glm::quat rot0 = glm::quat_cast(m1);
    glm::quat rot1 = glm::quat_cast(m2);

    glm::quat finalRot = glm::slerp(rot0, rot1, tdif);

    glm::mat4 finalMat = glm::mat4_cast(finalRot);

    finalMat[3] = m1[3] * (1 - tdif) + m2[3] * tdif;

    return finalMat;
}

// oblicz transformacjê dla meshu (interpolacja)
glm::mat4 MeshModelSkeleton::getTransformation(int index, double time) {
    int len = sequences[index].size();
    if (len == 1) // nie interpoluj jak jest tylko jeden element
        return sequences[index][0].transform;

    int nexti = 0;
    double nextt = 0;
    for (int i = 0; i < len; ++i) {
        // zapêtl animacjê
        time = fmodf(time, animation_length);

        if(sequences[index][i].time == time) // jeœli trafi³ idealnie czas, to nie interpoluj
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

            return interpolate(sequences[index][i].transform, sequences[index][nexti].transform, tdif);
            //}
        }
    }

    return glm::mat4(1); // nigdy nie powinno siê zdarzyæ
}



void MeshModelSkeleton::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time) {

    int len = meshes.size();
    for (int i = 0; i < len; ++i) {
        glm::mat4 Mt = glm::translate(M, translations[i]) * getTransformation(i, current_time);
        meshes[i].drawMesh(V, P, Mt, cam, time);
    }

    current_time += time;
    current_time = fmodf(current_time, animation_length);
}