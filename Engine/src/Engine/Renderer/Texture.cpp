//
// Created by Andrew Graser on 5/1/2024.
//

#include <iostream>

#include "Texture.h"
#include "Glad/glad.h"
#include "stbimage/stb_image.h"


namespace Engine {
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string &filepath) {
        return std::make_shared<Texture2D>(filepath);
    }

    std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        return std::make_shared<Texture2D>(width, height);
    }

    Texture2D::Texture2D(uint32_t width, uint32_t height)
        : mWidth(width), mHeight(height)
    {
        mInternalFormat = GL_RGBA8;
        mDataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
        glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);

        glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    Texture2D::Texture2D(const std::string &filepath) {
        int width, height, channels;
        stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if(!data)
            std::cerr << "Failed to load image\n";

        mWidth = width;
        mHeight = height;


        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        mInternalFormat = internalFormat;
        mDataFormat = dataFormat;


        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);
        glTextureStorage2D(mRendererID, 1, internalFormat, mWidth, mHeight);

        glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    void Texture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, mRendererID);
    }

    void Texture2D::SetData(void *data, uint32_t size) {
        glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data);
    }
}