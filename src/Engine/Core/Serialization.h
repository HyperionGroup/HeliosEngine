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


#include "Core/Logger/Logger.h"

namespace serialization
{
    typedef rapidjson::Document Archive;
    typedef rapidjson::Value Node;

    class InputArchive : public rapidjson::Document
    {
    public:
        InputArchive() = default;
        virtual ~InputArchive() = default;
        void ReadFromFile(const core::CStr& _filename)
        {
            std::ifstream t(_filename.ToCStr());
            std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            if (Parse(str.c_str()).HasParseError())
            {
                LOG_ERROR_APPLICATION("Error opening %s", _filename.ToCStr());
            }
            
            assert(IsArray());
        }
    };

    typedef public rapidjson::Value InputArchiveNode;
    template< typename T > T Get(InputArchiveNode& _node, const char* _name, const T& _defValue = T());

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

    class Deserializer
    {
    public:
        Deserializer( const core::CStr& _filename )
        {

        }
        virtual ~Deserializer() = default;
        template < class Object > void DerializeObject(const Object& _object) { Serialize(mArchive, _object); }

    private:
        OutputArchive mArchive;
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
    template< class Object > void Deserialize(InputArchiveNode& _node, Object& _object);
}
