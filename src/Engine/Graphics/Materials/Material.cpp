#include "Graphics.h"

#include "Material.h"
#include "MaterialParameter.h"

#include "Engine.h"

namespace graphics
{
    void CMaterial::Apply()
    {

    }

    void CMaterial::Deserialize(const io::CSerializableNode& _node)
    {
        /*
        const io::CSerializableEntityConstructor& lEntityCntr = helios::CEngine::GetInstance().GetSerializableEntityConstructor();
        for (const io::CSerializableNode& m : lShaders.GetArray())
        {
            std::shared_ptr< io::CSerializableEntity > lEntity = lEntityCntr.Create(m["type"].GetString());
            lEntity->Deserialize(m);
            std::shared_ptr< T > lEntityChildClass = std::static_pointer_cast<T>(lEntity);
            Add(lEntityChildClass->GetName(), lEntityChildClass);
        }
        */
    }

    void CMaterial::Serialize(io::CSerializableNode& _node) const
    {

    }

}
