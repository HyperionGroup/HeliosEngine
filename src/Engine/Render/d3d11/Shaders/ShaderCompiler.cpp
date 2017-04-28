#include "ShaderCompiler.h"
#include "ShaderStages\VertexStage.h"

namespace render
{
    CShaderCompiler::CShaderCompiler()
    {

    }

    CShaderCompiler::~CShaderCompiler()
    {

    }

    CShader* CShaderCompiler::LoadShader( const std::vector< std::string >& _flags, const std::string& _vs, const std::string& _ps )
    {
        std::string lShaderSrc = GetVertexStructures(_flags);
        lShaderSrc += "Vert2Pix VertexStageMain(App2Vert in)\n{\n" + _vs + "\n}\n\n";
        lShaderSrc += "float4 PixelStageMain(Vert2Pix in) : SV_Target\n{\n" + _ps + "\n}\n\n";

        render::CVertexShader* lVertexShader = new render::CVertexShader(lShaderSrc,);
        return nullptr;
    }

    std::string CShaderCompiler::GetVertexStructures(const std::vector< std::string >& _flags)
    {
        std::string lVS = "struct App2Vert\n{\n";
        std::string lPS = "struct Vert2Pix\n{\n";
        for (size_t i = 0, lCount = _flags.size(); i < lCount; ++i)
        {
            render::VertexFlags lFlag;
            if ( EnumString<render::VertexFlags>::ToEnum(lFlag, _flags[i]) )
            {
                switch (lFlag)
                {
                case render::Position:
                {
                    lVS += "float3 position : POSITION;\n";
                    lPS += "float4 position : POSITION;\n";
                    break;
                }
                case render::Position4:
                {
                    lVS += "float4 position : POSITION;\n";
                    lPS += "float4 position : POSITION;\n";
                    break;
                }
                case render::Normal:
                {
                    break;
                }
                case render::Tangent:
                {
                    break;
                }
                case render::Binormal:
                {
                    break;
                }
                case render::Uv:
                {
                    lVS += "float2 uv : TEXCOORD0;\n";
                    lPS += "float2 uv: TEXCOORD0;\n";
                    break;
                }
                case render::Uv2:
                {
                    break;
                }
                case render::Weight:
                {
                    break;
                }
                case render::Indices:
                {
                    break;
                }
                default:
                    HELIOSASSERT(false);
                    break;
                }
            }
        }

        lVS += "};\n";
        lPS += "};\n";
        return lVS + lPS;
    }
}