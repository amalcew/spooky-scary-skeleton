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

    glEnableVertexAttribArray(sp->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, verts.data()); //Wska¿ tablicê z danymi dla atrybutu vertex

    glEnableVertexAttribArray(sp->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, norms.data()); //Wska¿ tablicê z danymi dla atrybutu normal

    glEnableVertexAttribArray(sp->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords.data()); //Wska¿ tablicê z danymi dla atrybutu texCoord

    glUniform1i(sp->u("textureMap0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    glUniform1i(sp->u("textureMap1"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    glDisableVertexAttribArray(sp->a("vertex"));     //Wy³¹cz przesy³anie danych do atrybutu vertex
    glDisableVertexAttribArray(sp->a("color"));      //Wy³¹cz przesy³anie danych do atrybutu color
    glDisableVertexAttribArray(sp->a("normal"));     //Wy³¹cz przesy³anie danych do atrybutu normal
    glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
    
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