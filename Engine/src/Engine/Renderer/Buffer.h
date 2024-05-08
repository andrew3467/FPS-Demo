//
// Created by Andrew Graser on 4/30/2024.
//

#ifndef FPS_DEMO_BUFFER_H
#define FPS_DEMO_BUFFER_H


#include <cstdint>
#include <string>
#include <initializer_list>
#include <vector>
#include <memory>

namespace Engine {
    enum class ShaderDataType {
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type){
        switch (type) {
            case ShaderDataType::Float:              return 4;
            case ShaderDataType::Float2:             return 4 * 2;
            case ShaderDataType::Float3:             return 4 * 3;
            case ShaderDataType::Float4:             return 4 * 4;

            case ShaderDataType::Int:                return 4;
            case ShaderDataType::Int2:               return 4 * 2;
            case ShaderDataType::Int3:               return 4 * 3;
            case ShaderDataType::Int4:               return 4 * 4;

            case ShaderDataType::Mat3:               return 4 * 3 * 3;
            case ShaderDataType::Mat4:               return 4 * 4 * 4;

            case ShaderDataType::Bool:               return 1;
        }


        return 0;
    }

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Offset;
        uint32_t Size;

        bool Normalized;

        BufferElement(){}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
                : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        uint32_t GetElementCount() const {
            switch (Type) {
                case ShaderDataType::Float:             return 1;
                case ShaderDataType::Float2:            return 2;
                case ShaderDataType::Float3:            return 3;
                case ShaderDataType::Float4:            return 4;

                case ShaderDataType::Int:               return 1;
                case ShaderDataType::Int2:              return 2;
                case ShaderDataType::Int3:              return 3;
                case ShaderDataType::Int4:              return 4;

                case ShaderDataType::Mat3:              return 3 * 3;
                case ShaderDataType::Mat4:              return 4 * 4;

                case ShaderDataType::Bool:              return 1;
            }

            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements)
                : mElements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const {return mElements;}

        inline const uint32_t GetStride() const {return mStride;}

        std::vector<BufferElement>::iterator begin() {return mElements.begin();}
        std::vector<BufferElement>::iterator end() {return mElements.end();}

        std::vector<BufferElement>::const_iterator  begin() const {return mElements.begin();}
        std::vector<BufferElement>::const_iterator end() const {return mElements.end();}

    private:
        void CalculateOffsetsAndStride(){
            uint32_t offset = 0;
            mStride = 0;
            for(auto& element : mElements){
                element.Offset = offset;
                offset += element.Size;
                mStride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> mElements;
        uint32_t mStride = 0;
    };

    class VertexBuffer {
    public:
        VertexBuffer(float *data, uint32_t size);
        ~VertexBuffer() = default;

        static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);

        void SetLayout(const BufferLayout& layout) {mLayout = layout;}
        const BufferLayout& GetLayout() const {return mLayout;}

        void Bind();
        void Unbind();


    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

    class IndexBuffer {
    public:
        IndexBuffer(uint32_t *data, uint32_t count);
        ~IndexBuffer() = default;

        static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t count);


        void Bind();
        void Unbind();

        uint32_t GetCount() const;

    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };
}


#endif //FPS_DEMO_BUFFER_H
