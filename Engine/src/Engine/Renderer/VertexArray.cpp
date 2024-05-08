//
// Created by Andrew Graser on 4/30/2024.
//

#include "VertexArray.h"
#include "Glad/glad.h"

namespace Engine {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type){
        switch (type) {
            case ShaderDataType::Float:             return GL_FLOAT;
            case ShaderDataType::Float2:            return GL_FLOAT;
            case ShaderDataType::Float3:            return GL_FLOAT;
            case ShaderDataType::Float4:            return GL_FLOAT;

            case ShaderDataType::Int:               return GL_INT;
            case ShaderDataType::Int2:              return GL_INT;
            case ShaderDataType::Int3:              return GL_INT;
            case ShaderDataType::Int4:              return GL_INT;

            case ShaderDataType::Mat3:              return GL_FLOAT;
            case ShaderDataType::Mat4:              return GL_FLOAT;

            case ShaderDataType::Bool:              return GL_BOOL;
        }

        return 0;
    }

    std::shared_ptr<VertexArray> VertexArray::Create() {
        return std::make_shared<VertexArray>();
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &mRendererID);
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Bind() {
        glBindVertexArray(mRendererID);
    }

    void VertexArray::Unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer) {
        glBindVertexArray(mRendererID);
        buffer->Bind();


        uint32_t index = 0;
        const auto& layout = buffer->GetLayout();
        for(const auto& element : layout){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetElementCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.Offset);
            index++;
        }

        mVertexBuffers.push_back(buffer);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) {
        mIndexBuffer = buffer;

        glBindVertexArray(mRendererID);
        buffer->Bind();
    }

    void VertexArray::RemoveBuffers() {
        mIndexBuffer = nullptr;
        mVertexBuffers.clear();
    }
}