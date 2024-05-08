//
// Created by Andrew Graser on 5/1/2024.
//

#ifndef FPS_DEMO_MESH_H
#define FPS_DEMO_MESH_H

#include "Material.h"
#include "VertexArray.h"
#include "Buffer.h"



namespace Engine {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UV;
    };

    class Mesh {
    public:
        Mesh();
        ~Mesh() = default;

        static std::shared_ptr<Mesh> Create();

        std::shared_ptr<VertexArray>& GetVertexArray();

        inline void SetDirty(bool dirty) {mIsDirty = dirty;}
        inline Material& GetMaterial() {return *mMaterial;}

        void SetData(const std::vector<Vertex>& data, const std::vector<uint32_t>& indices);
        inline void SetMaterial(std::shared_ptr<Material>& mat) {mMaterial = mat;}

    private:
        uint32_t VAO, VBO, EBO;

        bool mIsDirty;

        std::shared_ptr<VertexArray> mVA;
        std::shared_ptr<Material> mMaterial;

        std::vector<Vertex> mVertices;
        std::vector<uint32_t> mIndices;
    };
}


#endif //FPS_DEMO_MESH_H
