//
// Created by Andrew Graser on 5/8/2024.
//

#ifndef APPLICATION_LIGHT_H
#define APPLICATION_LIGHT_H

#include "glm/vec3.hpp"

namespace Engine {
    struct PointLight {
        glm::vec3 Position = {0,0,0};
        glm::vec3 Ambient = {1,1,1};
    };
}

#endif //APPLICATION_LIGHT_H
