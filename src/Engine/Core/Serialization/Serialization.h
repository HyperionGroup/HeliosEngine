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
        InputArchive(const core::CStr& _filename)
        {
          std::ifstream t(_filename.c_str());
          std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
          if (Parse(str.c_str()).HasParseError())
          {
            LOG_ERROR_APPLICATION("Error opening %s", _filename.c_str());
          }
          assert(IsArray());
        }
        virtual ~InputArchive() = default;
    };

    typedef public rapidjson::Value InputArchiveNode;
    template< typename T > T Get(InputArchiveNode& _node, const char* _name, const T& _defValue = T());

    class OutputArchive : public rapidjson::PrettyWriter<rapidjson::StringBuffer>
    {
    public:
        OutputArchive( const core::CStr& _filename )
           : rapidjson::PrettyWriter<rapidjson::StringBuffer>(mBuffer)
           , mFilename(_filename)
        {
          StartArray();
        }
        virtual ~OutputArchive()
        {
          EndArray();
          std::ofstream out(mFilename.c_str());
          out << mBuffer.GetString();
          out.close();
        }
        template< class T >
        void Begin() 
        {
          StartObject();
          Key("type");
          String(typeid(T).name());
        }
        void End()   { EndObject();   }
        template< typename T > void Add(const char* _name, const T& _value, const T& _defValue = T() );
    private:
        rapidjson::StringBuffer mBuffer;
        core::CStr mFilename;
    };
}

#define SERIALIZABLE_OBJECT public: virtual void Serialize(serialization::OutputArchive& _archive); virtual void Deserialize(serialization::InputArchiveNode& _node);
