#ifndef _H_SERIALIZABLE_H_
#define _H_SERIALIZABLE_H_

#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/cereal.hpp>

#define SERIALIZABLE \
template <class Archive> void save(Archive & ar) const; \
template <class Archive> void load(Archive & ar); \

#endif // _H_SERIALIZABLE_H_