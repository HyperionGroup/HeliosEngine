#include "Core.h"
#include "Render.h"

#include "ShaderStage.h"
#include "StringUtils.h"
#include "Engine.h"
#include <iosfwd>

namespace render
{
    static std::string sShadersDirectory = "shaders/";
    namespace ShaderUtils
    {
        class CShaderInclude : public ID3DInclude
        {
        public:
            CShaderInclude() {}
            HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
            {
                //std::ifstream lBinaryFile(sShadersDirectory + pFileName, std::ios::in | std::ios::binary | std::ios::ate);
                HRESULT lHR = E_FAIL;
//                 if (lBinaryFile.is_open())
//                 {
//                     std::streamoff fileSize = lBinaryFile.tellg();
//                     char* buf = new char[(uint32)fileSize];
//                     lBinaryFile.seekg(0, std::ios::beg);
//                     lBinaryFile.read(buf, fileSize);
//                     lBinaryFile.close();
//                     *ppData = buf;
//                     *pBytes = (UINT)fileSize;
//                     lHR = S_OK;
//                 }
                return lHR;
            }
            HRESULT __stdcall Close(LPCVOID pData)
            {
                char* buf = (char*)pData;
                delete[] buf;
                return S_OK;
            }
        };

        ID3DBlob* CompileShader(const std::string& aShader,
            const std::string& aShaderModel,
            const D3D_SHADER_MACRO* aDefines)
        {
            UINT lFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
            lFlags |= D3DCOMPILE_DEBUG;
#endif
            ID3DBlob* lErrorBlob = nullptr;
            ID3DBlob* lShaderBlob = nullptr;
            CShaderInclude* lShaderInclude = new CShaderInclude();
            HRESULT lHR = D3DCompile( aShader.c_str(), aShader.size(), sShadersDirectory.c_str(), aDefines, lShaderInclude,
                                      "main", aShaderModel.c_str(), 0, 0, &lShaderBlob, &lErrorBlob);
            if (FAILED(lHR))
            {
                LOG_ERROR_APPLICATION("Error compiling shader\n\n");
                if (lErrorBlob)
                {
                    WCHAR message[1024];
                    message[0] = NULL;
                    char* blobdata = reinterpret_cast<char*>(lErrorBlob->GetBufferPointer());

                    MultiByteToWideChar(CP_ACP, 0, blobdata, static_cast<int>(lErrorBlob->GetBufferSize()), message, 1024);
                    std::wstring fullMessage = L"Error compiling shader file \"";
                    fullMessage += L"\" - ";
                    fullMessage += message;

#ifdef _DEBUG
                    MessageBoxW(NULL, fullMessage.c_str(), L"Shader Compilation Error", MB_OK);
#endif
                    LOG_ERROR_APPLICATION("%s\n%s\n ", fullMessage.c_str(), aShader.c_str());
                }
                DXCheckedRelease(lErrorBlob);
                DXCheckedRelease(lShaderBlob);
            }
            CHECKED_DELETE( lShaderInclude );
            return lShaderBlob;
        }
    }

    void CShaderStage::ShutDown()
    {
        CHECKED_DELETE(m_Blob);
    }

    void CShaderStage::Initialize(ID3D11DevicePtr _device)
    {
        std::vector<std::string> lMacros;
        D3D_SHADER_MACRO *lD3DMacros = nullptr;

        if (!mMacros.empty())
        {
            std::vector<std::string> l_PreprocessorItems = core::Split(mMacros, '|');
            lD3DMacros = new D3D10_SHADER_MACRO[l_PreprocessorItems.size() + 1];
            for (size_t i = 0; i < l_PreprocessorItems.size(); ++i)
            {
                std::vector<std::string> l_PreprocessorItem = core::Split(l_PreprocessorItems[i], '=');
                if (l_PreprocessorItem.size() == 1)
                {
                    lMacros.push_back(l_PreprocessorItems[i]);
                    lMacros.push_back("1");
                }
                else if (l_PreprocessorItem.size() == 2)
                {
                    lMacros.push_back(l_PreprocessorItem[0]);
                    lMacros.push_back(l_PreprocessorItem[1]);
                }
                else
                {
                    delete[] lD3DMacros;
                    return;
                }
            }

            for (size_t i = 0; i < l_PreprocessorItems.size(); ++i)
            {
                lD3DMacros[i].Name = lMacros[i * 2].c_str();
                lD3DMacros[i].Definition = lMacros[(i * 2) + 1].c_str();
            }
            lD3DMacros[l_PreprocessorItems.size()].Name = NULL;
            lD3DMacros[l_PreprocessorItems.size()].Definition = NULL;
        }

        if (!mSource.empty())
        {
            std::ifstream ifs(sShadersDirectory + mSource);
            std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            m_Blob = ShaderUtils::CompileShader(content, GetShaderModel(), lD3DMacros);
        }

        CHECKED_DELETE_ARRAY( lD3DMacros );
    }

    void CShaderStage::Deserialize(const io::CSerializableNode& _node)
    {
        HELIOSASSERT(_node.IsObject());
        mSource = _node["src"].GetString();
        mMacros = _node["macros"].GetString();
        Initialize(helios::CEngine::GetInstance().GetDevice().Device());
    }

    void CShaderStage::Serialize(io::CSerializableNode& _node) const
    {

    }

    void CPixelStage::Initialize(ID3D11DevicePtr _device)
    {
        CShaderStage::Initialize(_device);
        DXCall(_device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader));
        mInitialized = false;
    }

    void CPixelStage::ShutDown()
    {
        if (mInitialized)
        {
            DXCheckedRelease(m_PixelShader);
            mInitialized = false;
        }
    }

    void CPixelStage::Bind(ID3D11DeviceContextPtr _device)
    {
        _device->PSSetShader(m_PixelShader, nullptr, 0);
    }

    void CPixelStage::Unbind(ID3D11DeviceContextPtr _device)
    {
        _device->PSSetShader(nullptr, nullptr, 0);
    }

    const char* CPixelStage::GetShaderModel()
    {
        return helios::CEngine::GetInstance().GetDevice().GetPixelStageFeatureLevel();
    }

    void CGeometryStage::Initialize(ID3D11DevicePtr _device)
    {
        CShaderStage::Initialize(_device);
        DXCall(_device->CreateGeometryShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_GeometryShader));
        mInitialized = true;
    }

    void CGeometryStage::ShutDown()
    {
        if (mInitialized)
        {
            DXCheckedRelease(m_GeometryShader);
            mInitialized = false;
        }
    }

    void CGeometryStage::Bind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(m_GeometryShader, nullptr, 0);
    }

    void CGeometryStage::Unbind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(nullptr, nullptr, 0);
    }

    const char* CGeometryStage::GetShaderModel()
    {
        return helios::CEngine::GetInstance().GetDevice().GetGeometryStageFeatureLevel();
    }
}