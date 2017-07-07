#include "Core.h"
#include "Enabled.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::core::CEnabled>(OutputArchive& _archive, const ::core::CEnabled& _object)
    {
        _archive.Add("enabled", _object.IsEnabled(), true );
    }
}