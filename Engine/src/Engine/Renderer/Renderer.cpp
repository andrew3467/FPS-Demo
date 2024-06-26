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
        glm::vec3 ViewPos;

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

    void Renderer::StartScene(const Camera& camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sData->ViewProj = camera.GetViewProjection();
        sData->ViewPos = camera.GetPosition();
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

    void Renderer::Submit(std::shared_ptr<Mesh> &mesh) {
        auto& material = mesh->GetMaterial();
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

        auto transform = glm::scale(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-90, 0, 0)), glm::vec3(1.f));

        s->SetInt("uTexture", 0);
        s->SetMat4("uViewProj", sData->ViewProj);
        s->SetMat4("uTransform", transform);

        glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Submit(std::shared_ptr<Mesh> &mesh, const std::vector<PointLight> &lights) {
        auto& shader = mesh->GetMaterial().GetShader();
        shader->Bind();

        shader->SetFloat3("uViewPos", sData->ViewPos);

        shader->SetFloat3("uLight.Position", lights[0].Position);
        shader->SetFloat3("uLight.Ambient", lights[0].Ambient);

        Submit(mesh);
    }

    void Renderer::Submit(std::shared_ptr<Model> &model) {
        for(auto& mesh : model->GetMeshes()) {
            Submit(mesh);
        }
    }

    void Renderer::Submit(const PointLight &light) {
        auto transform = glm::translate(glm::mat4(1), light.Position);

        auto shader = Shader::Get("Standard_Unlit");
        shader->Bind();

        shader->SetMat4("uViewProj", sData->ViewProj);
        shader->SetMat4("uTransform", transform);

        sData->WhiteTexture->Bind(0);
        shader->SetFloat4("uColor", glm::vec4(light.Ambient, 1.0));

        sData->CubeVA->Bind();
        glDrawElements(GL_TRIANGLES, sData->CubeVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Submit(std::shared_ptr<Model> &model, const std::vector<PointLight> &lights) {
        for(auto& mesh : model->GetMeshes()) {
            Submit(mesh, lights);
        }
    }
}
