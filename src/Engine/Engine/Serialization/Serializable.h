#pragma once

#include "rapidjson/document.h"

#define SERIALIZABLE \
public: \
virtual void Deserialize(const io::CSerializableNode& _node); \
virtual void Serialize(io::CSerializableNode& _node) const;

namespace io
{
    typedef rapidjson::Document CSerializableDocument;
    typedef rapidjson::Value CSerializableNode;
    typedef rapidjson::SizeType ArraySize;

    namespace utils
    {
        CSerializableDocument OpenDocument(const std::string& _filename);
    }

    class CSerializableEntity
    {
    public:
        CSerializableEntity() = default;
        virtual ~CSerializableEntity() = default;
        virtual void Deserialize(const CSerializableNode& _node) = 0;
        virtual void Serialize(CSerializableNode& _node) const = 0;
    };

    class CSerializableEntityConstructor
    {
    public:

        template <typename T>
        void Register(const std::string& _name)
        {
            static_assert(std::is_base_of<CSerializableEntity, T>::value, "The object does not inherits from CSerializableEntity" );

            HELIOSASSERT(mConstructors.find(_name) == mConstructors.end());

            mConstructors[_name] = std::make_shared< STemplatedConstructor<T> >();
        }

        std::shared_ptr<CSerializableEntity> Create(const std::string& _name) const
        {
            HELIOSASSERT(mConstructors.find(_name) != mConstructors.end());
            return mConstructors.at(_name)->Create();
        }

        friend class CEngine;

        struct SGenericConstructor
        {
            virtual std::shared_ptr<CSerializableEntity> Create() const = 0;
        };

        template <typename T>
        struct STemplatedConstructor : public SGenericConstructor
        {
            virtual std::shared_ptr<CSerializableEntity> Create() const { return std::make_shared<T>(); }
        };

        CSerializableEntityConstructor() = default;
        ~CSerializableEntityConstructor() = default;

        std::map < const std::string, std::shared_ptr<SGenericConstructor>> mConstructors;

    };
}
