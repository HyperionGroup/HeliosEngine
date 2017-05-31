#include "Render.h"

#include "Texture.h"

namespace render
{
    void CTexture::Deserialize(const io::CSerializableNode& _node)
    {
        bool lOk = EnumString<SamplerType>::ToEnum(mSampler, _node["sampler_type"].GetString() );
        mFilename = _node["filename"].GetString();
        lOk &= Load();
    }
    
    void CTexture::Serialize(io::CSerializableNode& _node) const
    {

    }

    void CTexture::Bind(uint32 aStageId, ID3D11DeviceContextPtr aContext)
    {

    }

    bool CTexture::Load()
    {
        /*
        RenderManager& lRM = CEngine::GetInstance().GetRenderManager();
        ID3D11Device *lDevice = lRM.GetDevice();
        ID3D11DeviceContext *lContext = lRM.GetDeviceContext();

        ID3D11Resource * lResource = nullptr;

        // Convert the string filename to wide string
        std::wstring lTextureFileNameWString = std::wstring(m_Name.begin(), m_Name.end());

        std::string lExtension = base::utils::GetFilenameExtension(m_Name);
        HRESULT lHR = E_FAIL;

        DirectX::TexMetadata info;
        DirectX::ScratchImage *image = new DirectX::ScratchImage();

        if (lExtension == "dds")
            lHR = DirectX::LoadFromDDSFile(lTextureFileNameWString.c_str(), DirectX::DDS_FLAGS_NONE, &info, *image);
        else if (lExtension == "tga")
            lHR = DirectX::LoadFromTGAFile(lTextureFileNameWString.c_str(), &info, *image);
        else
            lHR = DirectX::LoadFromWICFile(lTextureFileNameWString.c_str(), DirectX::WIC_FLAGS_NONE, &info, *image);

        if (SUCCEEDED(lHR))
        {
            lHR = CreateTexture(lDevice, image->GetImages(), image->GetImageCount(), image->GetMetadata(), &lResource);
            if (SUCCEEDED(lHR))
                lHR = CreateShaderResourceView(lDevice, image->GetImages(), image->GetImageCount(), image->GetMetadata(), &m_Texture);

            if (SUCCEEDED(lHR))
            {
                ID3D11Texture2D * lTex2D = static_cast<ID3D11Texture2D *>(lResource);
                D3D11_TEXTURE2D_DESC desc;
                lTex2D->GetDesc(&desc);

                mSize.x = desc.Width;
                mSize.y = desc.Height;
            }

        return SUCCEEDED(lHR);
        */
        return false;
    }
}