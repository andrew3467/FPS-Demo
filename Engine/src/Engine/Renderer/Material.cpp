//
// Created by Andrew Graser on 5/1/2024.
//

#include "Material.h"


namespace Engine {

    Material::Material(std::shared_ptr<Shader> &shader)
        : mShader(shader)
    {

    }
}