//
// Created by Andrew Graser on 4/25/2024.
//

#ifndef FPS_DEMO_ENGINE_H
#define FPS_DEMO_ENGINE_H

#include <memory>

#include "Window.h"
#include "../Events/ApplicationEvent.h"

namespace Engine {
    class Engine {
    public:
        Engine();
        ~Engine() = default;

        inline bool IsRunning() const {return mRunning;}
        inline Window& GetWindow() {return *mWindow;}

        static Engine& Get() {return *sInstance;}

        void Init();
        void Update();

        void OnImGuiRender(const std::function<void(void)>& func);

        void OnEvent(Event &e);

    private:
        bool OnWindowClosed(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);

    private:
        static Engine *sInstance;

    private:
        bool mRunning;

        std::shared_ptr<Window> mWindow;
    };
}


#endif //FPS_DEMO_ENGINE_H
