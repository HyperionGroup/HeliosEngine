#pragma once

namespace io
{
    class CAsset
    {
        SERIALIZABLE
    public:
        CAsset();
        virtual ~CAsset();
        virtual bool Load() = 0;
        const std::string& GetName() const { return mName; }
    protected:
        std::string mName;
    };

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CAsset)
    {
        ar(make_nvp("name", mName));
    }

    SERIALIZABLE_LOAD_DECLARATION(CAsset)
    {
        ar(make_nvp("name", mName));
    }
#pragma endregion Serialization
}