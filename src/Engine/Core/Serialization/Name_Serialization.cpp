#include "Core.h"
#include "Name.h"

#include "Serialization.h"

namespace core
{
    void CName::Serialize(serialization::OutputArchive& _archive)
    {
        _archive.Add("name", mName);
    }

    void CName::Deserialize(serialization::InputArchiveNode& _archive)
    {
        SetName(serialization::Get<core::CStr>(_archive, "name"));
    }
}