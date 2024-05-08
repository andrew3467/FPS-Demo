//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_RENDERER_H
#define FPS_DEMO_RENDERER_H


#include "VertexArray.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"

#include <memory>



namespace Engine {
    class Renderer {
    public:
        static void Init();

        static void StartScene(const std::shared_ptr<Camera>& camera);
        static void EndScene();

        static void Submit(Material& material, std::shared_ptr<VertexArray>& VA);
        static void Submit(Material& material, std::shared_ptr<Mesh>& mesh);
        static void Submit(std::shared_ptr<Model>& model);

        static void SubmitCube(Material& material, const glm::vec3& position, const glm::vec3& scale);
    };
}


#endif //FPS_DEMO_RENDERER_H
