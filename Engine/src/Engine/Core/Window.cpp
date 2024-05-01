//
// Created by Andrew Graser on 4/25/2024.
//

#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

bool Engine::Window::sGLFWInitialized = false;

void GLFWErrorCallback(int error_code, const char* description) {
    std::cerr << "GLFW ERROR: {" << error_code << "}\n" << description << "\n";
}

void InitGLFW() {
    glfwSetErrorCallback(GLFWErrorCallback);

    if(!glfwInit()){
        std::cerr << "ERROR: Failed to initialize GLFW!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_ENABLE_FORWARD_COMPAT, GLFW_TRUE);
#endif
}

namespace Engine {
    Window::Window(WindowProps &data) {
        mData.Width = data.Width;
        mData.Height = data.Height;
        mData.Title = data.Title;
        mData.VSync = false;

        if(!sGLFWInitialized) {
            InitGLFW();

            mWindow = glfwCreateWindow(1280, 720, "FPS Demo", nullptr, nullptr);

            if(!mWindow){
                std::cerr << "Failed to create GLFW window!\n";
            }

            glfwMakeContextCurrent(mWindow);

            glfwSetWindowUserPointer(mWindow, &mData);

            //GLFW Callbacks
            glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *window){
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                WindowCloseEvent e;
                data.EventCallback(e);
            });

            glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height){
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                data.Width = width;
                data.Height = height;
                WindowResizeEvent e(width, height);
                data.EventCallback(e);
            });

            glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods){
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action) {
                    case GLFW_PRESS: {
                        KeyPressedEvent event(key, 0);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        KeyReleasedEvent event(key);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT: {
                        KeyPressedEvent event(key, 1);
                        data.EventCallback(event);
                        break;
                    }
                }
            });

            glfwSetCharCallback(mWindow, [](GLFWwindow *window, unsigned int keycode) {
                WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);

                KeyTypedEvent event(keycode);

                data.EventCallback(event);
            });

            glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action) {
                    case GLFW_PRESS: {
                        MouseButtonPressedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        MouseButtonReleassedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                }
            });

            glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset){
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseScrolledEvent event((float)xoffset, (float)yoffset);
                data.EventCallback(event);
            });

            glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos){
                auto& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseMovedEvent event((float)xpos, (float)ypos);
                data.EventCallback(event);
            });
        }
    }

    void Window::ToggleCursor(bool enable) {
        glfwSetInputMode(mWindow, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
}