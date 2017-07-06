#include "Core.h"
#include "Name.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::core::CName>(OutputArchive& _archive, const ::core::CName& _object)
    {
        _archive->Key("name");
        _archive->String(_object.GetName().ToCStr());
    }
}