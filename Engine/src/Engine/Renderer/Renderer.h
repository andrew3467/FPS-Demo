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
#include "Light.h"

#include <memory>



namespace Engine {
    class Renderer {
    public:
        static void Init();

        static void StartScene(const Camera& camera);
        static void EndScene();

        static void Submit(Material& material, std::shared_ptr<VertexArray>& VA);
        static void Submit(std::shared_ptr<Mesh>& mesh);
        static void Submit(std::shared_ptr<Mesh>& mesh, const std::vector<PointLight> &lights);
        static void Submit(std::shared_ptr<Model>& model);
        static void Submit(std::shared_ptr<Model>& model, const std::vector<PointLight>& lights);

        static void SubmitCube(Material& material, const glm::vec3& position, const glm::vec3& scale);

        static void Submit(const PointLight& light);
    };
}


#endif //FPS_DEMO_RENDERER_H
