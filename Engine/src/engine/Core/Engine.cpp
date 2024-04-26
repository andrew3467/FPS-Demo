//
// Created by Andrew Graser on 4/25/2024.
//

#include <iostream>

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

#include "Engine.h"


namespace Engine {
    Engine::Engine() {

    }

    void Engine::Init() {
        if(!glfwInit()){
            std::cerr << "Failed to initialize GLFW!\n";
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
        glfwWindowHint(GLFW_ENABLE_FORWARD_COMPAT, GLFW_TRUE);
#endif
        mWindow = glfwCreateWindow(1280, 720, "FPS Demo", nullptr, nullptr);

        if(!mWindow){
            std::cerr << "Failed to create GLFW window!\n";
        }

        glfwMakeContextCurrent(mWindow);

        //GLFW Callbacks
        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *window){

        });


        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cerr << "Failed to initialize GLAD!\n";
        }
    }

    void Engine::Update() {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
}
