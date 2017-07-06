#include "Core.h"
#include "Enabled.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::core::CEnabled>(OutputArchive& _archive, const ::core::CEnabled& _object)
    {
        _archive->Key("enabled");
        _archive->Bool( _object.IsEnabled() );
    }
}