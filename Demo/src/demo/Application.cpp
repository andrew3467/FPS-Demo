//
// Created by Andrew Graser on 4/25/2024.
//

#include <iostream>

#include <Glad/glad.h>

#include "Application.h"
#include "engine/Core/Engine.h"

namespace Demo {
    Application* Application::sInstance = nullptr;

    void Application::Run() {
        Engine::Engine engine;
        engine.Init();
        Init();

        mRunning = true;

        while(mRunning){
            Update();
            Render();
            engine.Update();
        }
    }

    void Application::Init() {

    }

    void Application::Update() {

    }

    void Application::Render() {

    }

}