//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_VERTEXARRAY_H
#define FPS_DEMO_VERTEXARRAY_H


#include <memory>
#include "Buffer.h"

namespace Engine {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray() = default;

        static std::shared_ptr<VertexArray> Create();

        void Bind();
        void Unbind();

        inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() { return mVertexBuffers;}
        inline std::shared_ptr<IndexBuffer> GetIndexBuffer() { return mIndexBuffer;}

        void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

    private:
        uint32_t mRendererID;

        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}


#endif //FPS_DEMO_VERTEXARRAY_H
