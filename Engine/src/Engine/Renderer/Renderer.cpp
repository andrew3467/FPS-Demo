//
// Created by Andrew Graser on 4/30/2024.
//

#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"

#include <Glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    struct SceneData {
        glm::mat4 ViewProj;

        std::shared_ptr<Texture2D> WhiteTexture;

        std::shared_ptr<VertexArray> CubeVA;
    };

    SceneData* sData = nullptr;

    void Renderer::Init() {
        sData = new SceneData();

        sData->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t texData = 0xffffffff;
        sData->WhiteTexture->SetData(&texData, sizeof(texData));

        {
            uint32_t indices[] = {
                    0, 1, 2,    2, 3, 0,
                    4, 5, 6,    6, 7, 4,
                    8, 9, 10,   10, 11, 8,
                    12, 13, 14, 14, 15, 12,
                    16, 17, 18, 18,19,16,
                    20, 21, 22, 22,23,20
                    };

            float vertices[] = {
                    // positions          // normals           // texture coords
                    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

                    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

                    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

                    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

                    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
                    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
                    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

                    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            };

            sData->CubeVA = std::make_shared<VertexArray>();

            std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));


            vb->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
                                  {ShaderDataType::Float3, "aNormal"},
                                  {ShaderDataType::Float2, "aTexCoord"},
                          });
            sData->CubeVA->SetVertexBuffer(vb);

            std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(indices,
                                                                            sizeof(indices) / sizeof(uint32_t));
            sData->CubeVA->SetIndexBuffer(ib);
        }
    }

    void Renderer::StartScene(const std::shared_ptr<Camera>& camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sData->ViewProj = camera->GetViewProjection();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(Material& material, std::shared_ptr<VertexArray> &VA) {
        VA->Bind();

        auto s = material.GetShader();

        s->Bind();

        if(material.GetDiffuse() == nullptr){
            sData->WhiteTexture->Bind(0);
            s->SetFloat4("uColor", material.GetColor());
        }else{
            material.GetDiffuse()->Bind(0);
            s->SetFloat4("uColor", glm::vec4(1.0f));
        }

        s->SetInt("uTexture", 0);
        s->SetMat4("uViewProj", sData->ViewProj);
        s->SetMat4("uTransform", glm::mat4(1));

        glDrawElements(GL_TRIANGLES, sData->CubeVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SubmitCube(Material& material, const glm::vec3& position, const glm::vec3& scale) {
        sData->CubeVA->Bind();

        auto transform = glm::translate(glm::scale(glm::mat4(1), scale), position);


        auto s = material.GetShader();
        s->Bind();

        if(material.GetDiffuse() == nullptr){
            sData->WhiteTexture->Bind(0);
            s->SetFloat4("uColor", material.GetColor());
        }else{
            material.GetDiffuse()->Bind(0);
            s->SetFloat4("uColor", glm::vec4(1.0f));
        }

        s->SetInt("uTexture", 0);
        s->SetMat4("uViewProj", sData->ViewProj);
        s->SetMat4("uTransform", transform);



        glDrawElements(GL_TRIANGLES, sData->CubeVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Submit(Material &material, std::shared_ptr<Mesh> &mesh) {
        mesh->GetVertexArray()->Bind();


        auto s = material.GetShader();

        s->Bind();

        if(material.GetDiffuse() == nullptr){
            sData->WhiteTexture->Bind(0);
            s->SetFloat4("uColor", material.GetColor());
        }else{
            material.GetDiffuse()->Bind(0);
            s->SetFloat4("uColor", glm::vec4(1.0f));
        }

        const glm::vec3 scale = {10, 10, 10};
        const glm::vec3 position = {0,0,0};

        s->SetInt("uTexture", 0);
        s->SetMat4("uViewProj", sData->ViewProj);
        s->SetMat4("uTransform", glm::mat4(1));

        glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Submit(std::shared_ptr<Model> &model) {
        auto transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for(auto& mesh : model->GetMeshes()) {
            auto& material = mesh->GetMaterial();
            auto& shader = material.GetShader();

            shader->Bind();

            shader->SetInt("uTexture", 0);
            shader->SetMat4("uViewProj", sData->ViewProj);
            shader->SetMat4("uTransform", transform);

            shader->SetFloat4("uColor", glm::vec4(1.0f));

            material.GetDiffuse()->Bind(0);
            shader->SetInt("uTexture", 0);


            mesh->GetVertexArray()->Bind();
            glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }
}
