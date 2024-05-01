//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_INPUT_H
#define FPS_DEMO_INPUT_H


#include <utility>

namespace Engine {
    class Input {
    public:
        static bool IsKeyPressed(int keycode);

        static bool IsMouseButtonPressed(int button);
        static float GetMouseX();
        static float GetMouseY();
        static std::pair<float, float> GetMousePos();
        static void SetMousePos(float x, float y);

    private:
        static Input* sInstance;
    };
}


#endif //FPS_DEMO_INPUT_H
