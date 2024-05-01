//
// Created by Andrew Graser on 4/30/2024.
//

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <filesystem>


#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1

#define SHADER_VERTEX_PREPROCESSOR "#type vertex"
#define SHADER_FRAGMENT_PREPROCESSOR "#type fragment"

struct ShaderSource {
    std::string VertexSource;
    std::string FragmentSource;

    void AddLine(int type, const std::string& line){
        switch (type) {
            case VERTEX_SHADER:          VertexSource.append('\n' + line); break;
            case FRAGMENT_SHADER:        FragmentSource.append('\n' + line); break;
        }
    }
};

ShaderSource LoadShaderSource(const std::string& path){
    ShaderSource source;

    int currentShader = VERTEX_SHADER;
    std::ifstream file(path);

    if(!file.is_open()){
        std::cerr << "Failed to open file at: " << path << "\n";
    }

    std::string line;
    while(std::getline(file, line)){
        if(line == SHADER_VERTEX_PREPROCESSOR){
            currentShader = VERTEX_SHADER;
            continue;
        } else if(line == SHADER_FRAGMENT_PREPROCESSOR) {
            currentShader = FRAGMENT_SHADER;
            continue;
        }

        source.AddLine(currentShader, line);
    }
    file.close();

    return source;
}


std::unordered_map<std::string, std::shared_ptr<Engine::Shader>> Engine::Shader::sShaders;

namespace Engine {
    void Shader::Init() {
        Create("../assets/shaders/Solid_Unlit.glsl");
    }

    std::shared_ptr<Shader> Shader::Create(const std::string &path) {
        auto shader = std::make_shared<Shader>(path);
        sShaders[shader->GetName()] = shader;

        std::cout << shader->GetName() << '\n';

        return shader;
    }

    std::shared_ptr<Shader>& Shader::Get(const std::string &name) {
        return sShaders[name];
    }

    Shader::Shader(const std::string &path) {
        std::filesystem::path p = path;
        mName = p.stem().string();

        auto source = LoadShaderSource(path);

        GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        {
            auto src = source.VertexSource.c_str();
            glShaderSource(vertexShader, 1, &src, 0);

            glCompileShader(vertexShader);
            int success;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

            if(!success){
                GLint maxLength = 0;
                glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(vertexShader);

                std::cerr << "Error: Vertex SolidShader compilation failure!\n" << infoLog.data() << "\n";

                return;
            }
        }

        {
            auto src = source.FragmentSource.c_str();
            glShaderSource(fragmentShader, 1, &src, 0);

            glCompileShader(fragmentShader);
            int success;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

            if(!success){
                GLint maxLength = 0;
                glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(fragmentShader);

                std::cerr << "Error: Fragment SolidShader compilation failure!\n" << infoLog.data() << "\n";

                return;
            }
        }

        mRendererID = glCreateProgram();

        glAttachShader(mRendererID, vertexShader);
        glAttachShader(mRendererID, fragmentShader);

        glLinkProgram(mRendererID);

        GLint success;
        glGetProgramiv(mRendererID, GL_LINK_STATUS, (int *) &success);
        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(mRendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(mRendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(mRendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            std::cerr << "Error: SolidShader link failure!\n" << infoLog.data() << "\n";

            return;
        }

        glDetachShader(mRendererID, vertexShader);
        glDetachShader(mRendererID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(mRendererID);
    }

    void Shader::Bind() {
        glUseProgram(mRendererID);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    int Shader::GetLocation(const std::string &name) {
        return glGetUniformLocation(mRendererID, name.c_str());
    }

    void Shader::SetInt(const std::string &name, int v) {
        glUniform1i(GetLocation(name), v);
    }

    void Shader::SetInt2(const std::string &name, const glm::ivec2 &v) {
        glUniform2i(GetLocation(name), v.x, v.y);
    }

    void Shader::SetInt3(const std::string &name, const glm::ivec3 &v) {
        glUniform3i(GetLocation(name), v.x, v.y, v.z);
    }

    void Shader::SetInt4(const std::string &name, const glm::ivec4 &v) {
        glUniform4i(GetLocation(name), v.x, v.y, v.z, v.w);
    }

    void Shader::SetFloat(const std::string &name, float v) {
        glUniform1f(GetLocation(name), v);
    }

    void Shader::SetFloat2(const std::string &name, const glm::vec2 &v) {
        glUniform2f(GetLocation(name), v.x, v.y);
    }

    void Shader::SetFloat3(const std::string &name, const glm::vec3 &v) {
        glUniform3f(GetLocation(name), v.x, v.y, v.z);
    }

    void Shader::SetFloat4(const std::string &name, const glm::vec4 &v) {
        glUniform4f(GetLocation(name), v.x, v.y, v.z, v.w);
    }

    void Shader::SetMat3(const std::string &name, const glm::mat3 &v) {
        glUniformMatrix3fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(v));
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &v) {
        glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(v));
    }
}