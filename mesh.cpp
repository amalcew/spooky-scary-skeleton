#include "mesh.h"

Mesh::Mesh(const aiMesh* singleMesh) {

    using namespace std;

    for (int i = 0; i < singleMesh->mNumVertices; i++) {
        aiVector3D vertex = singleMesh->mVertices[i];  //aiVector3D podobny do glm::vec3
        aiVector3D normal = singleMesh->mNormals[i];  //Wektory znormalizowane
        aiVector3D texCoord = singleMesh->mTextureCoords[0][i];

        verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));
        norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));

        //unsigned int liczba_zest = mesh->GetNumUVChannels();
        //unsigned int wymiar_wsp_tex = mesh->mNumUVComponents[0];

        //cout << vertex.x << " " << vertex.y << " " << vertex.z << endl;
        //cout << normal.x << " " << normal.y << " " << normal.z << endl;
        //cout << texCoord.x << " " << texCoord.y << endl;
    }

    for (int i = 0; i < singleMesh->mNumFaces; i++) {
        aiFace& face = singleMesh->mFaces[i];

        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void Mesh::setTexture(GLuint tex0, GLuint tex1)
{
    this->tex0 = tex0;
    this->tex1 = tex1;
}

void Mesh::setShaderProgram(ShaderProgram* sp)
{
    this->sp = sp;
}

// rysuje pojedynczy mesh
void Mesh::drawMesh(glm::mat4 V, glm::mat4 P, glm::mat4 M, glm::vec3 cam, double time) {

    sp->use();//Aktywacja programu cieniuj¹cego
    //Przeslij parametry programu cieniuj¹cego do karty graficznej
  
    glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

    float campos[] = { cam.x, cam.y, cam.z };
    glUniform3fv(sp->u("campos"), 1, campos);


    globalTime += time;
    int flag = (int) (globalTime) % 6;
    // printf("flag %d\n", flag);
    float r, g, b;
    float x, y, z;
    float r2, g2, b2;
    float x2, y2, z2;
    if (flag == 0) {
        r = 0.1; g = 0.0; b = 1.0;
        x = 2.5; y = 3.0, z = 0.0;
        r2 = 0.0; g2 = 1.0; b2 = 0.1;
        x2 = -2.5; y2 = 3.0, z2 = 0.0;
    } else if (flag == 1) {
        r = 0.0; g = 1.0; b = 0.1;
        x = 5.0; y = 3.0, z = 5.0;
        r2 = 0.1; g2 = 1.0; b2 = 1.0;
        x2 = -5.0; y2 = 3.0, z2 = -5.0;
    } else if (flag == 2) {
        r = 0.1; g = 1.0; b = 1.0;
        x = -5.0; y = 3.0, z = 5.0;
        r2 = 0.1; g2 = 0.0; b2 = 1.0;
        x2 = 5.0; y2 = 3.0, z2 = -5.0;
    } else if (flag == 3) {
        r = 1.0; g = 0.1; b = 0.1;
        x = 5.0; y = 3.0, z = -5.0;
        r2 = 1.0; g2 = 0.1; b2 = 1.0;
        x2 = -5.0; y2 = 3.0, z2 = 5.0;
    } else if (flag == 4) {
        r = 1.0; g = 0.1; b = 1.0;
        x = -5.0; y = 3.0, z = -5.0;
        r2 = 1.0; g2 = 1.0; b2 = 0.0;
        x2 = 5.0; y2 = 3.0, z2 = 5.0;
    } else if (flag == 5) {
        r = 1.0; g = 1.0; b = 0.0;
        x = -2.5; y = 3.0, z = 0.0;
        r2 = 1.0; g2 = 0.1; b2 = 0.1;
        x2 = 2.5; y2 = 3.0, z2 = 0.0;
    }
    float shift[] = { r, g, b };
    //float shift[] = { 1.0, 1.0,  1.0 };
    glUniform3fv(sp->u("shift"), 1, shift);

    float lightpos1[] = { x, y, z };
    glUniform3fv(sp->u("lightpos1"), 1, lightpos1);

    float shift2[] = { r2, g2, b2 };
    //float shift[] = { 1.0, 1.0,  1.0 };
    glUniform3fv(sp->u("shift2"), 1, shift2);

    float lightpos2[] = { x2, y2, z2 };
    glUniform3fv(sp->u("lightpos2"), 1, lightpos2);

    glEnableVertexAttribArray(sp->a("vertex"));  //Wï¿½ï¿½cz przesyï¿½anie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts.data()); //Wskaï¿½ tablicï¿½ z danymi dla atrybutu vertex

    glEnableVertexAttribArray(sp->a("normal"));  //Wï¿½ï¿½cz przesyï¿½anie danych do atrybutu normal
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms.data()); //Wskaï¿½ tablicï¿½ z danymi dla atrybutu normal

    glEnableVertexAttribArray(sp->a("texCoord0"));  //Wï¿½ï¿½cz przesyï¿½anie danych do atrybutu texCoord
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords.data()); //Wskaï¿½ tablicï¿½ z danymi dla atrybutu texCoord

    glUniform1i(sp->u("textureMap0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    glUniform1i(sp->u("textureMap1"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    glDisableVertexAttribArray(sp->a("vertex"));     //Wyï¿½ï¿½cz przesyï¿½anie danych do atrybutu vertex
    glDisableVertexAttribArray(sp->a("color"));      //Wyï¿½ï¿½cz przesyï¿½anie danych do atrybutu color
    glDisableVertexAttribArray(sp->a("normal"));     //Wyï¿½ï¿½cz przesyï¿½anie danych do atrybutu normal
    glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyï¿½ï¿½cz przesyï¿½anie danych do atrybutu texCoord0
    
}

void Mesh::freeMemory() {
    glDeleteTextures(1, &tex0);
    glDeleteTextures(1, &tex1);
    /*//usuniecie VBO z GPU
    glDeleteBuffers(1, &bufVertex);
    glDeleteBuffers(1, &bufNormal);
    glDeleteBuffers(1, &bufTexCoord);
    glDeleteBuffers(1, &bufIndex);*/
    delete sp;
}