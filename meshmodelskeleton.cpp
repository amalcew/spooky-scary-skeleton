#include "meshmodelskeleton.h"

void MeshModelSkeleton::setupAnimation()
{
    sequences = std::vector<keyframesequence>(meshes.size());

    animation_length = 60;

    keyframe kf;
    keyframesequence kfs;
    glm::mat4 M0 = glm::mat4(1);
    glm::mat4 M;

    // ===================================                         TORS
    kfs.clear();                // wyczyœæ sekwencjê
    kf.time = 0;                // ustaw czas klatki
    kf.transform = M0;          // ustaw transformacjê klatki
    kfs.push_back(kf);          // wstaw klatkê do sekwencji

    kf.time = 5;               
    kf.transform = glm::rotate(M0, (float)glm::radians(-9.481), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);    

    kf.time = 15;
    kf.transform = glm::rotate(M0, (float)glm::radians(9.76593), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = glm::rotate(M0, (float)glm::radians(-9.481), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 30;               
    kf.transform = M0;          
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = glm::rotate(M0, (float)glm::radians(9.67742), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = glm::rotate(M0, (float)glm::radians(-9.481), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = glm::rotate(M0, (float)glm::radians(9.67742), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    sequences[TORSO] = kfs;     // wstaw sekwencjê dla meshu


    // ===================================                         PRAWA RÊKA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.490336, 1.68491, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 59.8057), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(6.98063), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.50796), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 5;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.60048, 1.59445, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 83.255), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(24.0602), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-10.8962), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 15;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.362911, 1.75781, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 102.402), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-22.9138), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(2.47372), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.60048 , 1.59445, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 102.75), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(26.1624), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-2.55568), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 30;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.490336, 1.68491, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 59.8057), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-6.98063), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.50796), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.364119, 1.75724, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 67.1638), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-30.9569), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(9.0939), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.60048, 1.59445, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 71.8194), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(21.595), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-15.3464), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.364119, 1.75724, 0.0) - translations[ARM_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 67.1638), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-30.9569), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(9.0939), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    sequences[ARM_R] = kfs;


    // ===================================                         LEWA RÊKA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.493008, 1.69544, 0.0) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 57.2129), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(9.18618), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(0.0), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 5;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.367698, 1.76682, 0.0) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 72.4755), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(42.713), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(4.58733), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 15;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.607969, 1.60138, 0.0) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 77.9464), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-25.3011), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-2.47327), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.367698, 1.76682, 0.0) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 72.4755), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(42.713), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(4.58733), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 30;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.493008, 1.69544, 0.0) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 57.2129), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(9.18618), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(0.0), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.602099, 1.68547, 0.000811) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 87.1533), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-24.9972), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(11.8316), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.367698, 1.75055, 0.073103) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 118.889), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(29.135), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(33.0182), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.602099, 1.68547, 0.000811) - translations[ARM_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 98.8485), glm::vec3(-1.0, 0.0, 0.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-26.6185), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(6.73487), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    sequences[ARM_L] = kfs;


    // ===================================                         PRAWA NOGA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.240031, 0.772174, 0.0) - translations[LEG_R]);
    kfs.push_back(kf);

    kf.time = 5;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.197847, 0.771021, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.13164), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 15;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.273142, 0.771464, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-2.45761), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.197847, 0.771021, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.13164), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 30;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.240031, 0.772174, 0.0) - translations[LEG_R]);
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.273142, 0.771464, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-2.45761), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.197847, 0.771021, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.13164), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.273142, 0.771464, 0.000811) - translations[LEG_R]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-2.45761), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    sequences[LEG_R] = kfs;


    // ===================================                         LEWA NOGA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.221428, 0.761388, 0.0) - translations[LEG_L]);
    kfs.push_back(kf);

    kf.time = 5;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.261505, 0.760333, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.01725), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 15;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.159613, 0.758875, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-4.65685), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.261505, 0.760333, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.01725), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 30;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.221428, 0.761388, 0.0) - translations[LEG_L]);
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.159613, 0.758875, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-4.65685), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.261505, 0.760333, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(3.01725), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.159613, 0.758875, 0.0) - translations[LEG_L]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-4.65685), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    sequences[LEG_L] = kfs;


    // ===================================                         G£OWA
    kfs.clear();

    kf.time = 0;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 5;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.137451, 1.79863, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-17.9537), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-30.1915), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 15;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.141543, 1.79794, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-10.6439), glm::vec3(0.0, 0.0, -1.0));
    kfs.push_back(kf);

    kf.time = 25;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.137451, 1.79863, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-17.9537), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(-30.1915), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 30;
    kf.transform = M0;
    kfs.push_back(kf);

    kf.time = 35;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.140272, 1.79816, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(18.4504), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(24.6155), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 45;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(-0.137451, 1.79863, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(90 - 90.6182), glm::vec3(-1.0, 0.0, 1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(12.7259), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(5.22822), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    kf.time = 55;
    kf.transform = M0;
    kf.transform = glm::translate(kf.transform, glm::vec3(0.140272, 1.79816, 0.0) - translations[HEAD]);
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(18.4504), glm::vec3(0.0, 0.0, -1.0));
    kf.transform = glm::rotate(kf.transform, (float)glm::radians(24.6155), glm::vec3(0.0, -1.0, 0.0));
    kfs.push_back(kf);

    sequences[HEAD] = kfs;
}

void MeshModelSkeleton::loadModel(std::string path) {

    MeshModel::loadModel(path);

    // domyœlnie wszystkie czêœci s¹ ustawione tak, aby origin mia³y na 0,0,0
    // w celu ³atwiejszego obracania. PóŸniej nale¿y je przesuj¹æ na odpowiednie miejsce
    translations.push_back(glm::vec3(0.0, 0.975578, 0.0)); // tors
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
        //printf("time: %lf\n", time);

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

    current_time += time * 22;
    current_time = fmodf(current_time, animation_length);

    //printf("Current time: %lf\n", current_time);
}