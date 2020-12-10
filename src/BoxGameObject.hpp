#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <iostream>
#include <random>

GLfloat vertices[]{
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //
    1.0f,  -1.0f, -1.0f, 1.0f, 0.0f, //
    -1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, //
    1.0f,  1.0f,  -1.0f, 1.0f, 1.0f, //
    -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, //
    1.0f,  -1.0f, 1.0f,  1.0f, 1.0f, //
    -1.0f, 1.0f,  1.0f,  0.0f, 1.0f, //
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f, //
};
GLuint indices[]{
    0, 1, 2, 1, 2, 3, //
    0, 2, 4, 2, 4, 6, //
    1, 3, 5, 3, 5, 7, //
    0, 1, 4, 1, 4, 5, //
    2, 3, 6, 3, 6, 7, //
    4, 5, 6, 5, 6, 7  //
};

class AssimpError : public std::runtime_error {
  public:
    AssimpError(const std::string &message) : std::runtime_error("ERROR::ASSIMP:: " + message) {}
};

class BoxGameObject {
    std::unique_ptr<Mesh> ourMesh;
    std::unique_ptr<Shader> ourShader;
    std::unique_ptr<Texture> ourTexture;
    glm::vec3 position;

  public:
    BoxGameObject() : position{glm::vec3(0.2f, 0.2f, 0.2f)} {

        // probando assimp para cargar la cabeza de mono :D
        std::cout << "BoxGameObject" << std::endl;
        Assimp::Importer importer{};
        const aiScene *scene = importer.ReadFile("./media/mokey.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            throw AssimpError(importer.GetErrorString());

        std::cout << (scene->HasMeshes() ? "true" : "false") << std::endl;
        auto mesh = scene->mMeshes[0];
        if (mesh == nullptr)
            throw AssimpError("mesh node");
        std::cout << mesh << std::endl;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0, 1);

        std::vector<GLfloat> vertices2;
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            vertices2.push_back(mesh->mVertices[i].x);
            vertices2.push_back(mesh->mVertices[i].y);
            vertices2.push_back(mesh->mVertices[i].z);

            //random uvs...
            vertices2.push_back(static_cast<float>(dist(mt)));
            vertices2.push_back(static_cast<float>(dist(mt)));
        }

        std::vector<unsigned int> indices2;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices2.push_back(face.mIndices[j]);
        }

        // ourMesh = std::make_unique<Mesh>(vertices, indices, 40, 36);
        ourMesh = std::make_unique<Mesh>(vertices2.data(), indices2.data(), vertices2.size(), indices2.size());
        ourShader = std::make_unique<Shader>("./media/triangles.vert", "./media/triangles.frag");
        ourTexture = std::make_unique<Texture>("./media/brick.png");
        ourTexture->loadTexture();
    }
    void render(const glm::mat4 &projection, const glm::mat4 &view) {

        ourShader->use();
        ourTexture->useTexture();
        GLuint uniformProjection = ourShader->uniformProjection;
        GLuint uniformModel = ourShader->uniformModel;
        GLuint uniformView = ourShader->uniformView;

        glm::mat4 model{glm::translate(glm::mat4(1.0f), position)};

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        ourMesh->renderMesh();
    }
};