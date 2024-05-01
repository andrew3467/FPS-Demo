//
// Created by Andrew Graser on 4/25/2024.
//

#include "Application.h"

#include "engine/Core/Engine.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"

#include <iostream>

namespace Demo {
    Application* Application::sInstance = nullptr;

    std::unique_ptr<Engine::Material> mat1;
    std::unique_ptr<Engine::Material> mat2;

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
        mCamController = std::make_unique<CameraController>(1.0f, 0.25f);

        auto texture = Engine::Texture2D::Create("../assets/textures/worn_planks_diff_4k.png");

        mat1 = std::make_unique<Engine::Material>(Engine::Shader::Get("Solid_Unlit"));
        mat1->SetColor(glm::vec4(0.8f, 0.2f, 0.4f, 1.0f));
        mat1->SetTexture(texture);
        mat2 = std::make_unique<Engine::Material>(Engine::Shader::Get("Solid_Unlit"));
        mat2->SetColor(glm::vec4(0.2f, 0.8f, 0.4f, 1.0f));
    }

    void Application::Update() {
        mCamController->ProcessInput();
    }

    void Application::Render() {
        Engine::Renderer::StartScene(mCamController->GetCamera());


        Engine::Renderer::SubmitCube(*mat1, {1.0, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
        Engine::Renderer::SubmitCube(*mat2, {1.0, 5.0f, 0.0f}, {2.0f, 1.0f, 1.0f});
        Engine::Renderer::SubmitCube(*mat2, {1.0, 0.0f, 4.0f}, {1.0f, 0.5f, 4.0f});

        Engine::Renderer::EndScene();
    }
}