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

        std::shared_ptr<VertexArray> CubeVA;
    };

    SceneData* sData = nullptr;

    void Renderer::Init() {
        sData = new SceneData();

        {
            float vertices[] = {
                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
                    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
                    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
                    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

                    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
                    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
                    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
                    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
                    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
                    0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
                    0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

                    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
                    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
                    0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
                    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
                    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
                    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
                    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
                    0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
            };

            uint32_t indices[6 * 6]{
                    // front and back
                    0, 3, 2,
                    2, 1, 0,
                    4, 5, 6,
                    6, 7 ,4,
                    // left and right
                    11, 8, 9,
                    9, 10, 11,
                    12, 13, 14,
                    14, 15, 12,
                    // bottom and top
                    16, 17, 18,
                    18, 19, 16,
                    20, 21, 22,
                    22, 23, 20
            };

            sData->CubeVA = std::make_shared<VertexArray>();

            std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));


            vb->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
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

    void Renderer::Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> &VA) {
        VA->Bind();

        shader->Bind();
        shader->SetMat4("uViewProj", sData->ViewProj);
        shader->SetMat4("uTransform", glm::mat4(1));
        shader->SetFloat3("uColor", glm::vec3(1));

        glDrawElements(GL_TRIANGLES, sData->CubeVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SubmitCube(std::shared_ptr<Shader> shader, const glm::vec3& position, const glm::vec3& scale) {
        sData->CubeVA->Bind();

        auto transform = glm::translate(glm::scale(glm::mat4(1), scale), position);

        shader->Bind();
        shader->SetMat4("uViewProj", sData->ViewProj);
        shader->SetMat4("uTransform", transform);
        shader->SetFloat3("uColor", glm::vec3(1));

        glDrawElements(GL_TRIANGLES, sData->CubeVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
