//
// Created by Andrew Graser on 5/1/2024.
//

#ifndef FPS_DEMO_MATERIAL_H
#define FPS_DEMO_MATERIAL_H


#include "Shader.h"

namespace Engine {
    class Material {
    public:
        Material(std::shared_ptr<Shader>& shader);
        ~Material() = default;

        std::shared_ptr<Shader>& GetShader() {return mShader;}
        glm::vec4 GetColor() {return mColor;}

        inline void SetColor(const glm::vec4& color) {mColor = color;}

    private:
        std::shared_ptr<Shader> mShader;
        glm::vec4 mColor;
    };
}


#endif //FPS_DEMO_MATERIAL_H
