#ifndef _H_SERIALIZABLE_H_
#define _H_SERIALIZABLE_H_

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/base_class.hpp>

#define SERIALIZABLE \
public: \
template <class Archive> void save(Archive & ar) const; \
template <class Archive> void load(Archive & ar); \

#define SERIALIZABLE_SAVE_DECLARATION( class_name) \
template <class Archive> void class_name::save(Archive & ar) const

#define SERIALIZABLE_LOAD_DECLARATION( class_name) \
template <class Archive> void class_name::load(Archive & ar)

#define TO_ARCHIVE( name ) ar (cereal::make_nvp(#name, m##name) );
#define FROM_ARCHIVE( name ) ar (cereal::make_nvp(#name, m##name) );

#define TO_ARCHIVE_BINARY( name, bin, size ) ar.saveBinaryValue(bin, size, name);

#define TO_ARCHIVE_SPTR( name ) ar (cereal::make_nvp(#name, m##name.get()) );
#define FROM_ARCHIVE_SPTR( name ) ar (cereal::make_nvp(#name, m##name.get() ) );

#define FROM_ARCHIVE_ENUM_VARIABLE( enum_type, enum_name ) \
{\
    std::string l##enum_name; \
    ar(cereal::make_nvp(#enum_name, l##enum_name)); \
    EnumString< enum_type >::ToEnum( m##enum_name, l##enum_name); \
}

#define TO_ARCHIVE_ENUM_VARIABLE( enum_type, enum_name ) \
ar(cereal::make_nvp(#enum_name, EnumString< enum_type >::ToStr(m##enum_name)));

#define FROM_ARCHIVE_ENUM( enum_name ) \
{\
    std::string l##enum_name; \
    ar(cereal::make_nvp(#enum_name, l##enum_name)); \
    EnumString< enum_name >::ToEnum( m##enum_name, l##enum_name); \
}

#define TO_ARCHIVE_ENUM( enum_name ) \
ar(cereal::make_nvp(#enum_name, EnumString< enum_name >::ToStr(m##enum_name)));

#endif // _H_SERIALIZABLE_H_