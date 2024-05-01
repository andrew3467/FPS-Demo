//
// Created by Andrew Graser on 4/30/2024.
//

#include "Buffer.h"
#include "Glad/glad.h"

namespace Engine {
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *data, uint32_t size) {
        return std::make_shared<VertexBuffer>(data, size);
    }

    VertexBuffer::VertexBuffer(float *data, uint32_t size) {
        glGenBuffers(1, &mRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *data, uint32_t count) {
        return std::make_shared<IndexBuffer>(data, count);
    }

    IndexBuffer::IndexBuffer(uint32_t *data, uint32_t count)
            : mCount(count)
    {
        glGenBuffers(1, &mRendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, data, GL_STATIC_DRAW);
    }

    void IndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void IndexBuffer::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::GetCount() const {
        return mCount;
    }
}
