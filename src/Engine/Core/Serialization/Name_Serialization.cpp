#include "Core.h"
#include "Name.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::core::CName>(OutputArchive& _archive, const ::core::CName& _object)
    {
        _archive.Add("name", _object.GetName());
    }

    template<> void Deserialize<::core::CName>(InputArchiveNode& _archive, ::core::CName& _object)
    {
        _object.SetName(Get<core::CStr>(_archive, "name"));
    }
}