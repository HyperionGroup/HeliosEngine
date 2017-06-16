#pragma once
namespace gfx
{
    class CTexture
    {
        private:
            bool Load();

        public:
            CTexture() = default;
            virtual ~CTexture() = default;
    };
}