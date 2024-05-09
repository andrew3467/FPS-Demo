//
// Created by Andrew Graser on 4/25/2024.
//

#include "Application.h"

#include "Engine/Core/Engine.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Model.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace Demo {
    Application* Application::sInstance = nullptr;

    std::unique_ptr<Engine::Material> mat1;
    std::unique_ptr<Engine::Material> mat2;
    std::unique_ptr<Engine::Material> mat3;

    std::shared_ptr<Engine::Model> model;

    std::vector<Engine::PointLight> pointLights;

    void Application::Run() {
        Engine::Engine engine;
        engine.Init();
        Init();

        while(engine.IsRunning()){
            Update();
            Render();
            engine.Update();
        }
    }

    void Application::Init() {
        mCamController = std::make_unique<CameraController>(0.125f, 0.25f);

        auto texture = Engine::Texture2D::Create("../assets/textures/worn_planks_diff_4k.png");

        mat1 = std::make_unique<Engine::Material>(Engine::Shader::Get("Standard_Unlit"));
        mat1->SetColor(glm::vec4(0.8f, 0.2f, 0.4f, 1.0f));
        mat1->SetDiffuse(texture);
        mat2 = std::make_unique<Engine::Material>(Engine::Shader::Get("Standard_Unlit"));
        mat2->SetColor(glm::vec4(0.2f, 0.8f, 0.4f, 1.0f));
        mat3 = std::make_unique<Engine::Material>(Engine::Shader::Get("Standard_Unlit"));
        mat3->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        model = Engine::Model::Create("../assets/models/Airplane/Airplane.obj");

        pointLights.push_back({glm::vec3(0, 0, 20),
                               glm::vec3(1,1,1)});

        pointLights.push_back({glm::vec3(10, 10, -10),
                               glm::vec3(1,1,1)});
    }

    void Application::Update() {
        mCamController->ProcessInput();

        pointLights[0].Position.z += sin(glfwGetTime());
    }

    void Application::Render() {
        Engine::Renderer::StartScene(*mCamController->GetCamera());

        Engine::Renderer::Submit(model, pointLights);

        //Render Lights
        for(auto& light : pointLights){
            Engine::Renderer::Submit(light);

        }

        Engine::Renderer::EndScene();
    }
}