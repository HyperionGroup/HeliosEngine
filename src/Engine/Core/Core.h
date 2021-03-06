#pragma once

#include "Utils/EnumToString.h"
#include "Logger/Logger.h"
#include "Utils/Containers.h"
#include "Str.h"
#include "Serialization/Serialization.h"
#include "Mathematics.h"

//#include <Delegate.h>
//#include <Signal.h>

// Compiler
#if defined(__GNUC__)
#define HELIOSCOMPILER_GNU
#elif defined(_MSC_VER)
#define HELIOSCOMPILER_MSVC
#else
#error im3d: Compiler not defined
#endif

// Platform 
#if defined(_WIN32) || defined(_WIN64)
// Windows
#define HELIOSPLATFORM_WIN

#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stddef.h>
#include <iostream>
#include <sys\stat.h>
#include <cstdio>
#include <fstream>
#include <memory>
#include <locale>         // std::locale, std::toupper

#define HELIOSUNUSED(x) x;
#ifdef HELIOSCOMPILER_MSVC
#define HELIOSBREAK() __debugbreak()
#else
#include <cstdlib>
#define HELIOSBREAK() abort()
#endif

#define HELIOSASSERT_MSG(e, msg, ...) \
	do { \
		if (!(e)) { \
            LOG_ERROR_APPLICATION( "ASSERT at %s:%d: %s", __FILE__, (int)__LINE__, #e ); \
			HELIOSBREAK(); \
		} \
	} while (0)

#undef  HELIOSASSERT
#define HELIOSASSERT(e)                 HELIOSASSERT_MSG(e, 0, 0)
#define HELIOSVERIFY_MSG(e, msg, ...)   HELIOSASSERT_MSG(e, msg, ## __VA_ARGS__)
#define HELIOSVERIFY(e)                 HELIOSVERIFY_MSG(e, 0, 0)

#ifndef __COUNTER__
#define __COUNTER__ __LINE__
#endif
#define HELIOSTOKEN_CONCATENATE_(_t0, _t1) _t0 ## _t1
#define HELIOSTOKEN_CONCATENATE(_t0, _t1)  HELIOSTOKEN_CONCATENATE_(_t0, _t1)
#define HELIOSUNIQUE_NAME(_base) HELIOSTOKEN_CONCATENATE(_base, __COUNTER__)
#define HELIOSSTRINGIFY_(_t) #_t
#define HELIOSSTRINGIFY(_t) HELIOSSTRINGIFY_(_t)

#define CHECKED_DELETE(ptr) if( ptr ) { delete ptr; ptr = nullptr; }
#define CHECKED_DELETE_ARRAY(arrayPtr) if( arrayPtr ) { delete[] arrayPtr; arrayPtr = nullptr; }
#define DISABLE_COPY_AND_ASSIGN(Class) private: \
Class(const Class &); Class &operator=(const Class &);

#else
#error Platform not defined
#endif

// Standard int typedefs
#include <stdint.h>
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef intptr_t iptr;
typedef uintptr_t uptr;
typedef wchar_t wchar;
typedef uint32_t bool32;

#define DECLARE_SPTR( class_name ) \
class class_name; \
typedef std::shared_ptr< class_name > class_name##Ptr;

#pragma warning( disable  : 4005 )  