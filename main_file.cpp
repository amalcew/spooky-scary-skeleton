/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"

#include "custom_camera.h"

struct key_status {
    bool arrow_left = false;
    bool arrow_right = false;
    bool arrow_up = false;
    bool arrow_down = false;
    bool shift = false;
    bool plus = false;
    bool minus = false;
    int scrollX = 0;
    int scrollY = 0;
} pressed_keys;

float speed_x=0;
float speed_y=0;
float aspectRatio=1;

ShaderProgram *sp;


//Odkomentuj, żeby rysować kostkę
//float* vertices = myCubeVertices;
//float* normals = myCubeNormals;
//float* texCoords = myCubeTexCoords;
//float* colors = myCubeColors;
//int vertexCount = myCubeVertexCount;


//Odkomentuj, żeby rysować czajnik
//float* vertices = myTeapotVertices;
//float* normals = myTeapotVertexNormals;
//float* texCoords = myTeapotTexCoords;
//float* colors = myTeapotColors;
//int vertexCount = myTeapotVertexCount;

GLuint tex0;
GLuint tex1;
std::vector<glm::vec4> verts;
std::vector<glm::vec4> norms;
std::vector<glm::vec2> texCoords;
std::vector<unsigned int> indices;

custom_camera camera;

// =======================                                   CALLBACKI / OBSŁUGA INPUTU  <===

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) pressed_keys.arrow_left = true;
        if (key==GLFW_KEY_RIGHT) pressed_keys.arrow_right = true;
        if (key==GLFW_KEY_UP) pressed_keys.arrow_up = true;
        if (key==GLFW_KEY_DOWN) pressed_keys.arrow_down = true;
        if (key==GLFW_KEY_EQUAL || 
            key==GLFW_KEY_KP_ADD) pressed_keys.plus = true;
        if (key==GLFW_KEY_MINUS ||
            key==GLFW_KEY_KP_SUBTRACT) pressed_keys.minus = true;
        if (key==GLFW_KEY_RIGHT_SHIFT ||
            key == GLFW_KEY_LEFT_SHIFT) pressed_keys.shift = true;
    }
    if (action==GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT) pressed_keys.arrow_left = false;
        if (key == GLFW_KEY_RIGHT) pressed_keys.arrow_right = false;
        if (key == GLFW_KEY_UP) pressed_keys.arrow_up = false;
        if (key == GLFW_KEY_DOWN) pressed_keys.arrow_down = false;
        if (key == GLFW_KEY_EQUAL ||
            key == GLFW_KEY_KP_ADD) pressed_keys.plus = false;
        if (key == GLFW_KEY_MINUS ||
            key == GLFW_KEY_KP_SUBTRACT) pressed_keys.minus = false;
        if (key == GLFW_KEY_RIGHT_SHIFT ||
            key == GLFW_KEY_LEFT_SHIFT) pressed_keys.shift = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    pressed_keys.scrollX = xoffset;
    pressed_keys.scrollY = yoffset;
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

void handle_controls(double time) {
    double mulTime = time;
    double multiplier = 2.0;
    if (pressed_keys.shift) mulTime *= multiplier;
    else multiplier = 1.0;

    if (pressed_keys.arrow_left) camera.moveX(-mulTime);
    else if (pressed_keys.arrow_right) camera.moveX(mulTime);

    if (pressed_keys.arrow_up) camera.moveY(-mulTime);
    else if (pressed_keys.arrow_down) camera.moveY(mulTime);

    if (pressed_keys.scrollY > 0) camera.moveR(-mulTime);
    else if (pressed_keys.scrollY < 0) camera.moveR(mulTime);

    if (pressed_keys.scrollY == 0) {
        // częstsze callbacki z klawiszy niż ze scrolla
        // trzeba spowolnić
        mulTime = (time / 2) * multiplier;
        if (pressed_keys.plus) camera.moveR(-mulTime);
        else if (pressed_keys.minus) camera.moveR(mulTime);
    }

    // reset scroll
    pressed_keys.scrollX = 0;
    pressed_keys.scrollY = 0;
}

// =======================                                     ŁADOWANIE MODELI/TEKSTUR  <===

GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}


void loadModel(std::string plik) {
    using namespace std;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    cout << importer.GetErrorString() << endl;

    aiMesh* mesh = scene->mMeshes[0];

    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];  //aiVector3D podobny do glm::vec3
        verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];  //Wektory znormalizowane
        norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texCoord = mesh->mTextureCoords[0][i];
        texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));

        //unsigned int liczba_zest = mesh->GetNumUVChannels();
        //unsigned int wymiar_wsp_tex = mesh->mNumUVComponents[0];

        //cout << vertex.x << " " << vertex.y << " " << vertex.z << endl;
        //cout << normal.x << " " << normal.y << " " << normal.z << endl;
        //cout << texCoord.x << " " << texCoord.y << endl;
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace& face = mesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);

        }
    }
}

// =======================                                             OPENGL INIT/FREE  <===

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);
    glfwSetScrollCallback(window, scroll_callback);

    camera = custom_camera();

	sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	tex0 = readTexture("content/metal.png");
	tex1 = readTexture("content/sky.png");

    loadModel(std::string("content/monkey.fbx"));
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}




//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 V = camera.getViewMatrix(); //Wylicz macierz widoku
    //camera.debug();

    glm::mat4 P=glm::perspective(50.0f*PI/180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

    glm::mat4 M=glm::mat4(1.0f);

    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0,verts.data()); //Wskaż tablicę z danymi dla atrybutu vertex

    // cos tu nie trybi, fajnie byłoby przy okazji ogarnąć dlaczego
	//glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, colors.data()); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms.data()); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords.data()); //Wskaż tablicę z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

    // glDrawArrays(GL_TRIANGLES,0,vertexCount); //Narysuj obiekt
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    

    glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


// =======================                                                           MAIN  <===

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{

        handle_controls(glfwGetTime());

        glfwSetTime(0); //Zeruj timer
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
