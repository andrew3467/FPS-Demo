//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_WINDOW_H
#define FPS_DEMO_WINDOW_H

#include <functional>

#include "../Events/Event.h"


class GLFWwindow;

namespace Engine {
    struct WindowProps {
        uint32_t Width;
        uint32_t Height;
        const char* Title;

        WindowProps(uint32_t w, uint32_t h, const char* t)
            : Width(w), Height(h), Title(t) {

        }

        WindowProps()
            : Width(1280), Height(720), Title("FPS Demo") {

        }
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(WindowProps &data);
        ~Window() = default;

        inline void SetEventCallback(const EventCallbackFn &callback) {
            mData.EventCallback = callback;
        }

        GLFWwindow* GetNativeWindow() const { return mWindow;}


        void ToggleCursor(bool b);

    private:

    private:
        static bool sGLFWInitialized;

        GLFWwindow* mWindow;

        struct WindowData{
            const char* Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        } mData;
    };
}


#endif //FPS_DEMO_WINDOW_H
