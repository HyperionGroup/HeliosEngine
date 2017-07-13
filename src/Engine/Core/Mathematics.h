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
  Float3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
  {
  }

  bool operator!=(const Float3& _other)const
  {
    return !(x == _other.x && y == _other.y && z == _other.z);
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
};