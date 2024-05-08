//
// Created by Andrew Graser on 5/6/2024.
//

#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


#include <iostream>

namespace Engine {

    std::shared_ptr<Texture2D> TextureFromFile(const char *path, const std::string &directory, bool gamma = false) {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        auto texture = Texture2D::Create(filename);

        return texture;
    }

    std::shared_ptr<Model> Model::Create(const std::string &filepath) {
        return std::make_shared<Model>(filepath);
    }

    Model::Model(const std::string &filepath) {
        LoadModel(filepath);
    }

    void Model::LoadModel(const std::string &filepath) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filepath,
                                               aiProcess_Triangulate |
                                               aiProcess_FlipUVs);

        mDirectory = filepath.substr(0, filepath.find_last_of('/'));

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode *node, const aiScene *scene) {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            mMeshes.push_back(ProcessMesh(mesh, scene));
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh *aiMesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        for(unsigned int i = 0; i < aiMesh->mNumVertices; i++)
        {
            Vertex vertex{};

            vertex.Position = {
                    aiMesh->mVertices[i].x,
                    aiMesh->mVertices[i].y,
                    aiMesh->mVertices[i].z
            };

            if(aiMesh->HasNormals()) {
                vertex.Normal = {
                        aiMesh->mNormals[i].x,
                        aiMesh->mNormals[i].y,
                        aiMesh->mNormals[i].z
                };
            } else {
                vertex.Normal = {0,0,0};
            }

            if(aiMesh->mTextureCoords[0]) {
                vertex.UV = {
                        aiMesh->mTextureCoords[0][i].x,
                        aiMesh->mTextureCoords[0][i].y
                };
            }else{
                vertex.UV = {0,0};
            }

            vertices.push_back(vertex);
        }

        for(unsigned int i = 0; i < aiMesh->mNumFaces; i++) {
            aiFace face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        auto mesh = Mesh::Create();
        mesh->SetData(vertices, indices);

        //Textures
        auto mat = std::make_shared<Material>(Engine::Shader::Get("Solid_Unlit"));
        mesh->SetMaterial(mat);
        if(aiMesh->mMaterialIndex >= 0){
            auto& mat = mesh->GetMaterial();

            auto material = scene->mMaterials[aiMesh->mMaterialIndex];
            auto diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            mat.SetDiffuse(diffuseMaps[0]);

            auto specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            //mat.SetSpecular(specularMaps[0]);
        }


        return mesh;
    }

    std::vector<std::shared_ptr<Texture2D>> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& name) {
        std::vector<std::shared_ptr<Texture2D>> textures;

        for(uint32_t i = 0; i < mat->GetTextureCount(type); i++){
            aiString str;
            mat->GetTexture(type, i, &str);
            auto tex = TextureFromFile(str.C_Str(), mDirectory);
            textures.push_back(tex);
        }

        return textures;
    }
}