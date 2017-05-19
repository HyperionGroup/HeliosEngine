#include "Render.h"

#include "ShaderStage.h"
#include "StringUtils.h"

static std::string sShadersDirectory = "data/shaders/";
namespace ShaderUtils
{
    class CShaderInclude : public ID3DInclude
    {
    public:
        CShaderInclude() {}
        HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
        {
            std::ifstream lBinaryFile(sShadersDirectory + pFileName, std::ios::in | std::ios::binary | std::ios::ate);
            HRESULT lHR = E_FAIL;
            if (lBinaryFile.is_open())
            {
                std::streamoff fileSize = lBinaryFile.tellg();
                char* buf = new char[(uint32)fileSize];
                lBinaryFile.seekg(0, std::ios::beg);
                lBinaryFile.read(buf, fileSize);
                lBinaryFile.close();
                *ppData = buf;
                *pBytes = (UINT)fileSize;
                lHR = S_OK;
            }
            return lHR;
        }
        HRESULT __stdcall Close(LPCVOID pData)
        {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };

    ID3DBlob* CompileShader( const std::string& aShader,
                             const std::string& aEntryPoint,
                             const std::string& aShaderModel,
                             const D3D_SHADER_MACRO* aDefines )
    {
        UINT lFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
        lFlags |= D3DCOMPILE_DEBUG;
#endif
        ID3DBlob* lErrorBlob = nullptr;
        ID3DBlob* lShaderBlob = nullptr;
        CShaderInclude* lShaderInclude = new CShaderInclude();
        HRESULT lHR = D3DCompile( aShader.c_str(), aShader.size(),
                                  sShadersDirectory.c_str(),
                                  aDefines,
                                  lShaderInclude,
                                  aEntryPoint.c_str(), aShaderModel.c_str(),
                                  0, 0, &lShaderBlob, &lErrorBlob );
        if (FAILED(lHR))
        {
            LOG_ERROR_APPLICATION("Error compiling shader\n\n");
            if (lErrorBlob)
            {
                LOG_ERROR_APPLICATION("%s\n --------- %s \n ---------",
                  (char*)lErrorBlob->GetBufferPointer(), aShader.c_str());
            }
            if (lErrorBlob) lErrorBlob->Release();
            if (lShaderBlob) lShaderBlob->Release();
        }
        delete lShaderInclude;
        return lShaderBlob;
    }
}

namespace render
{
    void CShaderStage::ShutDown()
    {
        delete[] m_ShaderMacros;
        delete m_Blob;
    }

    void CShaderStage::Initialize(ID3D11DevicePtr _device, const std::string& aShaderCode)
    {
        m_ShaderCode = aShaderCode;
        if (!m_ShaderCode.empty())
            m_Blob = ShaderUtils::CompileShader(m_ShaderCode, m_EntryPoint, GetShaderModel(), m_ShaderMacros);
        HELIOSASSERT(m_Blob != nullptr);
    }

    void CShaderStage::SetPreprocessor( const std::string& _preprocessor )
    {
        if (m_ShaderMacros)
        {
            delete[] m_ShaderMacros;
            m_ShaderMacros = nullptr;
        }

        m_PreprocessorMacros.clear();
        if (_preprocessor.empty())
        {
            m_ShaderMacros = nullptr;
            return;
        }
        std::vector<std::string> l_PreprocessorItems = core::Split(_preprocessor, '|');
        m_ShaderMacros = new D3D10_SHADER_MACRO[l_PreprocessorItems.size() + 1];
        for (size_t i = 0; i < l_PreprocessorItems.size(); ++i)
        {
            std::vector<std::string> l_PreprocessorItem = core::Split(l_PreprocessorItems[i], '=');
            if (l_PreprocessorItem.size() == 1)
            {
                m_PreprocessorMacros.push_back(l_PreprocessorItems[i]);
                m_PreprocessorMacros.push_back("1");
            }
            else if (l_PreprocessorItem.size() == 2)
            {
                m_PreprocessorMacros.push_back(l_PreprocessorItem[0]);
                m_PreprocessorMacros.push_back(l_PreprocessorItem[1]);
            }
            else
            {
                delete[] m_ShaderMacros;
                return;
            }
        }
        for (size_t i = 0; i < l_PreprocessorItems.size(); ++i)
        {
            m_ShaderMacros[i].Name = m_PreprocessorMacros[i * 2].c_str();
            m_ShaderMacros[i].Definition = m_PreprocessorMacros[(i * 2) + 1].c_str();
        }
        m_ShaderMacros[l_PreprocessorItems.size()].Name = NULL;
        m_ShaderMacros[l_PreprocessorItems.size()].Definition = NULL;
    }
}