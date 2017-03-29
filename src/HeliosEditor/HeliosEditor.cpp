#include <Mathpp.h>
#include "Textures/Sampler.h"

int main(int argc, char *argv[])
{
    Float3 point;
    Float3 point2(3.0f);
    Float3 point3 = point + point2;
    
    render::CSampler lSampler;

    std::ofstream file("out.json");
    std::ifstream filein("in.json");

    cereal::XMLOutputArchive archive(file);
    archive(cereal::make_nvp("sampler", lSampler));

    cereal::JSONInputArchive archivein(filein);
    archivein(cereal::make_nvp("sampler", lSampler));
    return 0;
}
