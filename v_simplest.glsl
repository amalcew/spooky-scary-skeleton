#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 campos;
uniform vec3 lightpos1;
uniform vec3 lightpos2;


//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec4 normal; //wektor normalny w przestrzeni modelu
in vec2 texCoord0;

//Zmienne interpolowane
out vec4 ic;
out vec4 l1;
out vec4 l2;
out vec4 l3;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0;
out vec2 iTexCoord1;

void main(void) {
    vec4 lp = vec4(lightpos1.xyz,1); //wektor światła stałego w przestrzeni świata
    vec4 lp2 = vec4(lightpos2.xyz,1); //wektor światła stałego w przestrzeni świata
    vec4 lpCam = vec4(campos.xyz, 1); //wektor światła za kamerą w przestrzeń świata
    l1 = normalize(V * lp - V*M*vertex); //wektor do światła w przestrzeni oka
    l2 = normalize(V * lpCam - V*M*vertex);
    l3 = normalize(V * lp2 - V*M*vertex);
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
    iTexCoord0 = texCoord0;
    iTexCoord1 = (n.xy + 1) / 2;
    ic = color;
    
    gl_Position=P*V*M*vertex;
}
