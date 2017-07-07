#include "Core.h"
#include "Enabled.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::core::CEnabled>(OutputArchive& _archive, const ::core::CEnabled& _object)
    {
        _archive.Add("enabled", _object.IsEnabled(), true );
    }

    template<> void Deserialize<::core::CEnabled>(InputArchiveNode& _archive, ::core::CEnabled& _object)
    {
        _object.SetEnabled(Get(_archive, "enabled", true));
    }
}