//
// Created by Andrew Graser on 5/6/2024.
//

#ifndef APPLICATION_MODEL_H
#define APPLICATION_MODEL_H

#include "Mesh.h"

#include "assimp/scene.h"


namespace Engine {
    class Model {
    public:
        static std::shared_ptr<Model> Create(const std::string& filepath);

    public:
        Model(const std::string& filepath);
        ~Model() = default;

        inline std::vector<std::shared_ptr<Mesh>> GetMeshes() {return mMeshes;}

    private:
        void LoadModel(const std::string& filepath);
        void ProcessNode(aiNode* node, const aiScene *scene);
        std::shared_ptr<Mesh> ProcessMesh(aiMesh *aiMesh, const aiScene *scene);
        std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &name);

    private:
        std::vector<std::shared_ptr<Mesh>> mMeshes;

        std::string mDirectory;
    };
}


#endif //APPLICATION_MODEL_H
