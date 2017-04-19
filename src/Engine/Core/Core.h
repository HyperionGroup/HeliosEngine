#pragma once

#include "EnumToString.h"
#include "Logger/Logger.h"
#include <string>
#include <im3d.h>
#include <im3d_math.h>

typedef Im3d::Vec2 Float2;
typedef Im3d::Vec3 Float3;
typedef Im3d::Vec4 Float4;

#define ASSERT(expr)       { if(!expr ) { LOG_ERROR_APPLICATION( "ASSERT at %s:%d: %s", __FILE__, (int)__LINE__, #expr ); } }

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