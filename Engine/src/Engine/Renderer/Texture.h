//
// Created by Andrew Graser on 5/1/2024.
//

#ifndef FPS_DEMO_TEXTURE_H
#define FPS_DEMO_TEXTURE_H


#include <string>
#include <cstdint>
#include <memory>


namespace Engine {
    class Texture2D {
    public:
        Texture2D(const std::string& filepath);
        Texture2D(uint32_t width, uint32_t height);
        ~Texture2D() = default;

        static std::shared_ptr<Texture2D> Create(const std::string& filepath);
        static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);

        void SetData(void* data, uint32_t size);

        uint32_t GetWidth() const {return mWidth;};
        uint32_t GetHeight() const {return mHeight;};

        void Bind(uint32_t slot = 0) const;

    private:


    private:
        uint32_t mWidth, mHeight;
        uint32_t mRendererID;
        std::string mPath;

        uint32_t mInternalFormat, mDataFormat;
    };
}


#endif //FPS_DEMO_TEXTURE_H
