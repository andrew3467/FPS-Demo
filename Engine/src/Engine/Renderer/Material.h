//
// Created by Andrew Graser on 5/1/2024.
//

#ifndef FPS_DEMO_MATERIAL_H
#define FPS_DEMO_MATERIAL_H


#include "Shader.h"
#include "Texture.h"

namespace Engine {
    class Material {
    public:
        Material(std::shared_ptr<Shader>& shader);
        ~Material() = default;

        std::shared_ptr<Shader>& GetShader() {return mShader;}
        std::shared_ptr<Texture2D>& GetDiffuse() {return mDiffuse;}
        std::shared_ptr<Texture2D>& GetSpecular() {return mSpecular;}
        std::shared_ptr<Texture2D>& GetNormalMap() {return mNormalMap;}
        glm::vec4 GetColor() {return mColor;}

        inline void SetDiffuse(const std::shared_ptr<Texture2D>& texture) {mDiffuse = texture;}
        inline void SetSpecular(const std::shared_ptr<Texture2D>& texture) {mSpecular = texture;}
        inline void SetNormalMap(const std::shared_ptr<Texture2D>& texture) {mNormalMap = texture;}
        inline void SetColor(const glm::vec4& color) {mColor = color;}

    private:
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Texture2D> mDiffuse = nullptr;
        std::shared_ptr<Texture2D> mSpecular = nullptr;
        std::shared_ptr<Texture2D> mNormalMap = nullptr;

        glm::vec4 mColor;
    };
}


#endif //FPS_DEMO_MATERIAL_H
