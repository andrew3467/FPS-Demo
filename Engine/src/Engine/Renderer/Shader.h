//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_SHADER_H
#define FPS_DEMO_SHADER_H


#include <string>
#include <memory>

#include "glm/glm.hpp"

namespace Engine {
    class Shader {
    public:
        Shader(const std::string& path);
        ~Shader();

        static std::shared_ptr<Shader> Create(const std::string& path);
        static void Init();

        static std::shared_ptr<Shader>& Get(const std::string& name);

        void Bind();
        void Unbind();

        const std::string& GetName() const {return mName;}

        int GetLocation(const std::string& name);

        void SetInt(const std::string& name, int v);
        void SetInt2(const std::string& name, const glm::ivec2& v);
        void SetInt3(const std::string& name, const glm::ivec3& v);
        void SetInt4(const std::string& name, const glm::ivec4& v);

        void SetFloat(const std::string& name, float v);
        void SetFloat2(const std::string& name, const glm::vec2& v);
        void SetFloat3(const std::string& name, const glm::vec3& v);
        void SetFloat4(const std::string& name, const glm::vec4& v);

        void SetMat3(const std::string& name, const glm::mat3& v);
        void SetMat4(const std::string& name, const glm::mat4& v);

    private:
        static std::unordered_map<std::string, std::shared_ptr<Shader>> sShaders;

    private:
        uint32_t mRendererID;
        std::string mName;
    };
}


#endif //FPS_DEMO_SHADER_H
