#include "Core.h"
#include "Enabled.h"

#include "Serialization.h"

namespace core
{
    void CEnabled::Serialize(serialization::OutputArchive& _archive)
    {
        _archive.Add("enabled", IsEnabled(), true );
    }

    void CEnabled::Deserialize(serialization::InputArchiveNode& _archive)
    {
        SetEnabled(serialization::Get(_archive, "enabled", true));
    }
}