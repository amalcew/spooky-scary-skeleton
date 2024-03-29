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
#include "meshmodel.h"
#include "shaderprogram.h"

#include "custom_camera.h"
#include "meshmodelskeleton.h"
#include "MeshModelSpeaker.h"
#include "MeshModelSkeletonHeadbang.h"
#include "MeshModelSkeletonSpin.h"

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

float speed_x = 0;
float speed_y = 0;

int window_x = 2560;
int window_y = 1440;
float aspectRatio = window_x / (float) window_y;

glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -50.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku

glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatio, 0.001f, 200.0f); //Wylicz macierz rzutowania

glm::mat4 M = glm::mat4(1.0f);

MeshModelSkeleton spooky;
MeshModelSkeletonHeadbang spooky2;
MeshModelSkeletonSpin spooky3;
MeshModelSpeaker speaker1;
MeshModelSpeaker speaker2;
MeshModel sceneFloor;
custom_camera camera;

// =======================                                   CALLBACKI / OBSŁUGA INPUTU  <===

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) pressed_keys.arrow_left = true;
        if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) pressed_keys.arrow_right = true;
        if (key == GLFW_KEY_UP || key == GLFW_KEY_W) pressed_keys.arrow_up = true;
        if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) pressed_keys.arrow_down = true;
        if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD || key == GLFW_KEY_E) pressed_keys.plus = true;
        if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_Q) pressed_keys.minus = true;
        if (key == GLFW_KEY_RIGHT_SHIFT || key == GLFW_KEY_LEFT_SHIFT) pressed_keys.shift = true;
    }
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) pressed_keys.arrow_left = false;
        if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) pressed_keys.arrow_right = false;
        if (key == GLFW_KEY_UP || key == GLFW_KEY_W) pressed_keys.arrow_up = false;
        if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) pressed_keys.arrow_down = false;
        if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD || key == GLFW_KEY_E) pressed_keys.plus = false;
        if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_Q) pressed_keys.minus = false;
        if (key == GLFW_KEY_RIGHT_SHIFT ||
            key == GLFW_KEY_LEFT_SHIFT) pressed_keys.shift = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    pressed_keys.scrollX = xoffset;
    pressed_keys.scrollY = yoffset;
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);
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



// =======================                                             OPENGL INIT/FREE  <===
ShaderProgram* sp;
//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scroll_callback);

    camera = custom_camera(
        glm::vec3(-6.0, 2.0, 6.0),
        glm::vec3(0.0, 1.0, 0.0)
    );


    sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");

    //spooky.loadModel(std::string("content/directions.obj"));
    //spooky.loadModel(std::string("content/skeleton.fbx"));
    //spooky.loadModel(std::string("content/skelly-rig.fbx"));

    // UWAGA!!!!
    // setShaderProgram MUSI BYĆ PRZED loadModel
    // bo przypisany shader jest w loadModel przekazywany dalej do meshu

    sceneFloor.setShaderProgram(sp);
    sceneFloor.setTexture("content/disco.png");
    sceneFloor.loadModel(std::string("content/floor.obj"));

    spooky.setShaderProgram(sp);
    spooky.setTexture("content/bone2.png");
    spooky.loadModel(std::string("content/lowpolytest03-all.obj"));
    spooky2.setShaderProgram(sp);
    spooky2.setTexture("content/bone2.png");
    spooky2.loadModel(std::string("content/lowpolytest03-all.obj"));
    spooky3.setShaderProgram(sp);
    spooky3.setTexture("content/bone2.png");
    spooky3.loadModel(std::string("content/lowpolytest03-all.obj"));

    speaker1.setShaderProgram(sp);
    speaker1.setTexture("content/Speaker.png");
    speaker1.loadModel(std::string("content/Speaker.obj"));
    speaker2.setShaderProgram(sp);
    speaker2.setTexture("content/Speaker.png");
    speaker2.loadModel(std::string("content/Speaker.obj"));

    //spooky.loadModel(std::string("content/SKELETON.fbx"));
    //spooky.loadModel(std::string("content/skeleton-model.fbx"));
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    //delete sp;
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, double time) {
    //************Tutaj umieszczaj kod rysujący obraz******************l
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    V = camera.getViewMatrix(); //Wylicz macierz widoku
    //camera.debug();
    //printf("Start of frame\n");
    spooky.drawModel(V, P, glm::translate(M, glm::vec3(0.0, 0.0, 2.0)), camera.position, time);
    spooky2.drawModel(V, P, glm::translate(M, glm::vec3(1.5, 0.0, 0.0)), camera.position, time);
    spooky3.drawModel(V, P, glm::translate(M, glm::vec3(-1.5, 0.0, 0.0)), camera.position, time);

    //printf("END of frame\n");
    speaker1.drawModel(V, P, glm::translate(M, glm::vec3(2.5, 0.0, -2.5)) , camera.position, time); 
    speaker2.drawModel(V, P, glm::translate(M, glm::vec3(-2.5, 0.0, -2.5)) , camera.position, time); 
    sceneFloor.drawModel(V, P, M, camera.position, time);
    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

int main(void)
{
    GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

    glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

    if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
        fprintf(stderr, "Nie można zainicjować GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(window_x, window_y, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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
        double time = glfwGetTime();
        handle_controls(time);

        glfwSetTime(0); //Zeruj timer
        drawScene(window, time); //Wykonaj procedurę rysującą
        glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
    }

    freeOpenGLProgram(window);

    glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
    exit(EXIT_SUCCESS);
}
