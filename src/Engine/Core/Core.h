#pragma once

#include "EnumToString.h"
#include "Logger/Logger.h"
#include <string>
#include <im3d.h>
#include <im3d_math.h>

typedef Im3d::Vec2 Float2;
typedef Im3d::Vec3 Float3;
typedef Im3d::Vec4 Float4;

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

#define NOMINMAX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#include <Windows.h>

#define winAssert(e) HELIOSVERIFY_MSG(e, Im3d::GetPlatformErrorString(GetLastError()))

#define HELIOSUNUSED(x) do { (void)sizeof(x); } while(0)
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

namespace Im3d {
    const char* GetPlatformErrorString(DWORD _err);
}

#else
#error Platform not defined
#endif

#define ASSERT(expr)       { if(!expr ) { }

#pragma once

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

typedef intptr_t intptr;
typedef uintptr_t uintptr;
typedef wchar_t wchar;
typedef uint32_t bool32;