//
// Created by Andrew Graser on 4/25/2024.
//

#include <iostream>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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
        Shader::Init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(Engine::Get().GetWindow().GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 460");

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

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

    void Engine::OnImGuiRender(const std::function<void(void)>& func) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("FPS Demo");

        func();

        ImGui::End();


        //Render ImGui window
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
