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
    typedef std::shared_ptr< rapidjson::PrettyWriter<rapidjson::StringBuffer> > OutputArchive;
    typedef rapidjson::Value Node;

    template< class Object > void Serialize(OutputArchive& _archive, const Object& _object);

    class Serializer
    {
    public:
        Serializer()
            : mArchive( std::make_shared< rapidjson::PrettyWriter<rapidjson::StringBuffer> >( mBuffer ) )
        {
        }

        virtual ~Serializer() = default;

        void Begin()
        {
            mArchive->StartArray();
        }

        void End()
        {
            mArchive->EndArray();
        }
        
        template < class Object > void SerializeObject(const Object& _object)
        {
            Serialize(mArchive, _object);
        }

        void WriteIntoFile(const core::CStr& _filename) const
        {
            std::ofstream out(_filename.ToCStr());
            out << mBuffer.GetString();
            out.close();
        }

    private:
        rapidjson::StringBuffer mBuffer;
        OutputArchive mArchive;
    };
}
