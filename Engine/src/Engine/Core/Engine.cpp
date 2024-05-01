//
// Created by Andrew Graser on 4/25/2024.
//

#include <iostream>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

#include "Engine.h"
#include "Renderer/Renderer.h"

namespace Engine {
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

    Engine* Engine::sInstance = nullptr;

    Engine::Engine() {

    }

    void Engine::Init() {
        WindowProps data(1280, 720, "FPS Demo");
        mWindow = std::make_shared<Window>(data);

        mWindow->SetEventCallback(BIND_EVENT_FUNC(Engine::OnEvent));

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cerr << "Failed to initialize GLAD!\n";
        }

        sInstance = this;

        Renderer::Init();

        mRunning = true;
    }

    void Engine::Update() {
        glfwPollEvents();
        glfwSwapBuffers(mWindow->GetNativeWindow());
    }

    void Engine::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Engine::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(Engine::OnWindowResize));
    }

    bool Engine::OnWindowClosed(WindowCloseEvent &e) {
        mRunning = false;

        return true;
    }

    bool Engine::OnWindowResize(WindowResizeEvent &e) {
        return false;
    }
}
