//
// Created by Andrew Graser on 5/1/2024.
//

#include "Mesh.h"
#include "Glad/glad.h"


#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <iostream>
#include <queue>


namespace Engine {

    std::shared_ptr<Mesh> Mesh::Create() {
        return std::make_shared<Mesh>();
    }

    Mesh::Mesh() : mIsDirty(true) {
        mVA = VertexArray::Create();
    }

    void Mesh::SetData(const std::vector<Vertex> &data, const std::vector<uint32_t>& indices) {
        mVertices = data;
        mIndices = indices;

        mIsDirty = true;
    }

    std::shared_ptr<VertexArray> &Mesh::GetVertexArray() {
        if(mIsDirty){
            mVA->RemoveBuffers();

            auto vb = VertexBuffer::Create((float*)&mVertices[0], mVertices.size() * sizeof(Vertex));
            vb->SetLayout({
                                  {ShaderDataType::Float3, "aPosition"},
                                  {ShaderDataType::Float3, "aNormal"},
                                  {ShaderDataType::Float2, "aTexCoord"},
                          });

            mVA->SetVertexBuffer(vb);

            auto ib = IndexBuffer::Create(&mIndices[0], mIndices.size());
            mVA->SetIndexBuffer(ib);

            mIsDirty = false;
        }

        return mVA;
    }
}