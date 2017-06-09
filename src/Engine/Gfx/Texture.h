#pragma once
namespace render
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