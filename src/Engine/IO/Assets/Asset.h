#pragma once

namespace io
{
    class CAsset
    {
    public:
        CAsset();
        virtual ~CAsset();
        virtual bool Load() = 0;
        const std::string& GetName() const { return mName; }
    protected:
        std::string mName;
    };
}