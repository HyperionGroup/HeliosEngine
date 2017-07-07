#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h> // for stringify JSON

#include "Core/Str.h"
#include <fstream>
#include <string>
#include <iostream>
#include <memory>

namespace serialization
{
    typedef rapidjson::Document Archive;
    typedef rapidjson::Value Node;

    class OutputArchive : public rapidjson::PrettyWriter<rapidjson::StringBuffer>
    {
    public:
        OutputArchive()
           : rapidjson::PrettyWriter<rapidjson::StringBuffer>(mBuffer)
        {
        }
        void Begin() { StartObject(); }
        void End()   { EndObject();   }
        virtual ~OutputArchive() = default;
        template< typename T > void Add(const char* _name, const T& _value, const T& _defValue = T() );
        void WriteIntoFile(const core::CStr& _filename) const
        {
            std::ofstream out(_filename.ToCStr());
            out << mBuffer.GetString();
            out.close();
        }

    private:
        rapidjson::StringBuffer mBuffer;
    };

    class Serializer
    {
    public:
        Serializer() = default;
        virtual ~Serializer() = default;
        void Begin() { mArchive.StartArray(); }
        void End() { mArchive.EndArray(); }
        template < class Object > void SerializeObject(const Object& _object) { Serialize(mArchive, _object); }
        void WriteIntoFile(const core::CStr& _filename) const { mArchive.WriteIntoFile(_filename); }

    private:
        OutputArchive mArchive;
    };

    template< class Object > void Serialize(OutputArchive& _archive, const Object& _object);
}
