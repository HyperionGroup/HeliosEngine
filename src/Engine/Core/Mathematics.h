#pragma once

struct Float2
{
  Float2() = default;
  float x, y;
  Float2(float _x, float _y)
    : x(_x), y(_y)
  {}
  bool operator!=(const Float2& _other)const
  {
    return !(x == _other.x && y == _other.y );
  }
};

struct Float3 {
  float x, y, z;
  Float3() = default;
  Float3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
  {
  }

  bool operator!=(const Float3& _other)const
  {
    return !(x == _other.x && y == _other.y && z == _other.z);
  }
};

struct Quaternion
{
  float x, y, z, w;
  Quaternion() = default;
  Quaternion(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
  {
  }
  bool operator!=(const Quaternion& _other) const
  {
    return !(x == _other.x && y == _other.y && z == _other.z && w == _other.w);
  }
};

struct Float4 {
  float x, y, z, w;
  Float4(float _x, float _y, float _z, float _w)
    : x(_x), y(_y), z(_z), w(_w)
  {
  }
  bool operator!=(const Float4& _other) const
  {
    return !(x == _other.x && y == _other.y && z == _other.z && w == _other.w);
  }
};

struct CColor {
  float r, g, b, a;
  CColor() = default;
  CColor(float _r, float _g, float _b, float _a)
    : r(_r), g(_g), b(_b), a(_a)
  {
  }
  bool operator!=(const CColor& _other)const
  {
    return !(r == _other.r && g == _other.g && b == _other.b && a == _other.a);
  }

  inline uint8_t FloatToByte(float fValue)
  {
    int i = static_cast<int>(0xff * fValue);
    if (i < 0)
      i = 0;
    else if (i > 0xff)
      i = 0xff;
    return static_cast<uint8_t>(i);
  }

  uint32_t GetUint32Argb()
  {
    return  (uint32_t)(FloatToByte(r) << 24) + (FloatToByte(g) << 16) + (FloatToByte(b) << 8) + FloatToByte(a);
  }
};

struct Transform
{

};