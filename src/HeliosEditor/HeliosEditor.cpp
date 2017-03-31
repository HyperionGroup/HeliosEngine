#include <Mathpp.h>
#include "Textures/Sampler.h"
#include "Assets/TextureAsset.h"

int main(int argc, char *argv[])
{
    Float3 point;
    Float3 point2(3.0f);
    Float3 point3 = point + point2;
    
    render::CSampler lSampler;

    std::ofstream file("out.json");
    std::ifstream filein("in.json");

    cereal::JSONOutputArchive archive(file);
    archive(cereal::make_nvp("sampler", lSampler));

    cereal::JSONInputArchive archivein(filein);
    archivein(cereal::make_nvp("sampler", lSampler));

    io::CTextureAsset lTexture("opiece.jpg");
    lTexture.Load();
    archive(cereal::make_nvp("texture_asset", lTexture));



    return 0;
}
