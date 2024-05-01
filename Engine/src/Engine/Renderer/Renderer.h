//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_RENDERER_H
#define FPS_DEMO_RENDERER_H


#include <memory>
#include "VertexArray.h"
#include "Camera.h"
#include "Shader.h"

namespace Engine {
    class Renderer {
    public:
        static void Init();

        static void StartScene(const std::shared_ptr<Camera>& camera);
        static void EndScene();

        static void Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray>& VA);

        static void SubmitCube(std::shared_ptr<Shader> shader, const glm::vec3& position, const glm::vec3& scale);
    };
}


#endif //FPS_DEMO_RENDERER_H
