#include "meshmodel.h"

// wczytuje pojedyncz¹ teksturê
GLuint MeshModel::readTexture(const char* filename) {
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

// rysuje wszystkie meshe w modelu
void MeshModel::drawModel(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time) {

    int len = meshes.size();
    glm::mat4 meshM;
    for (int i = 0; i < len; ++i) {
        meshes[i].drawMesh(V, P, M, cam, time);
    }
}

void MeshModel::setShaderProgram(ShaderProgram* sp) {
    this->sp = sp;
}

void MeshModel::setTexture(const char* path) {
    GLuint tex = readTexture(path);
    this->tex = tex;
}

// ³aduje model z pliku + wczytuje tekstury
void MeshModel::loadModel(std::string path) {
    using namespace std;

    /*tex0 = readTexture("content/bone.png");
    tex1 = readTexture("content/disco.png");*/
    tex0 = tex;
    tex1 = tex;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    if (scene) {
        meshNum = 0;
        if (scene->HasMeshes()) {
            meshNum = scene->mNumMeshes;
        }

        for (int i = 0; i < meshNum; i++) {
            aiMesh* aimesh = scene->mMeshes[i];
            Mesh mesh = Mesh(aimesh);
            mesh.setTexture(tex0, tex1);
            mesh.setShaderProgram(sp);
            meshes.push_back(mesh);
        }
    }
    else {
        printf("Error parsing '%s': '%s'\n", path.c_str(), importer.GetErrorString());
    }
}

void MeshModel::freeMemory() {
    glDeleteTextures(1, &tex0);
    glDeleteTextures(1, &tex1);
    /*//usuniecie VBO z GPU
    glDeleteBuffers(1, &bufVertex);
    glDeleteBuffers(1, &bufNormal);
    glDeleteBuffers(1, &bufTexCoord);
    glDeleteBuffers(1, &bufIndex);*/
    delete sp;
}