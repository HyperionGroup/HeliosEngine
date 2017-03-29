#include <Mathpp.h>
#include "Textures/Sampler.h"
#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

int main(int argc, char *argv[])
{
    Float3 point;
    Float3 point2(3.0f);
    Float3 point3 = point + point2;

    std::ofstream filejson("out.json");
    std::ofstream filexml("out.xml");
    std::ofstream filebin("out.meta");
    render::CSampler lSampler;
    cereal::JSONOutputArchive archive(filejson);
    cereal::XMLOutputArchive archive1(filexml);
    cereal::BinaryOutputArchive archive2(filebin);
    archive(cereal::make_nvp("sampler", lSampler));
    archive1(cereal::make_nvp("sampler", lSampler));
    archive2(cereal::make_nvp("sampler", lSampler));
    return 0;
}
