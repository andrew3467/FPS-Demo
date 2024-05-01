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
    }

    void Application::Update() {
        mCamController->ProcessInput();
    }

    void Application::Render() {
        Engine::Renderer::StartScene(mCamController->GetCamera());

        auto shader = Engine::Shader::Get("Solid_Unlit");

        Engine::Renderer::SubmitCube(shader, {1.0, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
        Engine::Renderer::SubmitCube(shader, {1.0, 5.0f, 0.0f}, {2.0f, 1.0f, 1.0f});
        Engine::Renderer::SubmitCube(shader, {1.0, 0.0f, 4.0f}, {1.0f, 0.5f, 4.0f});

        Engine::Renderer::EndScene();
    }
}