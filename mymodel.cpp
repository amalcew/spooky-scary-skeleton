#include "mymodel.h"

GLuint mymodel::readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamiêci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamiêci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}

mymodel::mymodel(std::string path)
{
    using namespace std;

    sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
    tex0 = readTexture("content/metal.png");
    tex1 = readTexture("content/sky.png");

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    if (scene) {
        meshNum = 0;
        if (scene->HasMeshes()) {
            meshNum = scene->mNumMeshes;
        }

        for (int i = 0; i < meshNum; i++) {
            if (i == 2) {
                aiMesh* aimesh = scene->mMeshes[i];
                meshes.push_back(mesh(aimesh));
            }
        }
    }
    else {
        printf("Error parsing '%s': '%s'\n", path.c_str(), importer.GetErrorString());
    }
}

void mymodel::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam) {
    for (mesh m : meshes) {
        m.drawMesh(V, P, M, cam);
    }
}
