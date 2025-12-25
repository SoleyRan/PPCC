#ifndef MEMBER_CHECK_HPP_
#define MEMBER_CHECK_HPP_

#include <iostream>

#define DEFINE_MEMBER_CHECKER(member)                                                                                  \
  template <typename T, typename V = bool>                                                                             \
  struct has_##member : std::false_type                                                                                \
  {                                                                                                                    \
  };                                                                                                                   \
  template <typename T>                                                                                                \
  struct has_##member<                                                                                                 \
      T, typename std::enable_if<!std::is_same<decltype(std::declval<T>().member), void>::value, bool>::type>          \
      : std::true_type                                                                                                 \
  {                                                                                                                    \
  };

#define RS_HAS_MEMBER(C, member) has_##member<C>::value

#define DEFINE_MEMBER_FUNCTION_CHECKER(member)                                                                                  \
  template <typename T, typename V = bool>                                                                             \
  struct has_##member##_function : std::false_type                                                                                \
  {                                                                                                                    \
  };                                                                                                                   \
  template <typename T>                                                                                                \
  struct has_##member##_function<                                                                                                 \
      T, typename std::enable_if<!std::is_same<decltype(std::declval<T>().member()), void>::value, bool>::type>          \
      : std::true_type                                                                                                 \
  {                                                                                                                    \
  };


#define RS_HAS_MEMBER_FUNCTION(C, member) has_##member##_function<C>::value

namespace ppcc
{

DEFINE_MEMBER_CHECKER(x)
DEFINE_MEMBER_CHECKER(y)
DEFINE_MEMBER_CHECKER(z)
DEFINE_MEMBER_CHECKER(intensity)
DEFINE_MEMBER_CHECKER(ring)
DEFINE_MEMBER_CHECKER(stamp)

DEFINE_MEMBER_FUNCTION_CHECKER(x)
DEFINE_MEMBER_FUNCTION_CHECKER(y)
DEFINE_MEMBER_FUNCTION_CHECKER(z)
DEFINE_MEMBER_FUNCTION_CHECKER(intensity)
DEFINE_MEMBER_FUNCTION_CHECKER(ring)
DEFINE_MEMBER_FUNCTION_CHECKER(stamp)

//Set
template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, x) && !RS_HAS_MEMBER_FUNCTION(T_Point, x)>::type setX(T_Point& point, const float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, x)>::type setX(T_Point& point, const float& value)
{
    point.x = value;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, x)>::type setX(T_Point& point, const float& value)
{
    point.x(value);
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, y) && !RS_HAS_MEMBER_FUNCTION(T_Point, y)>::type setY(T_Point& point, const float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, y)>::type setY(T_Point& point, const float& value)
{
    point.y = value;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, y)>::type setY(T_Point& point, const float& value)
{
    point.y(value);
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, z) && !RS_HAS_MEMBER_FUNCTION(T_Point, z)>::type setZ(T_Point& point, const float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, z)>::type setZ(T_Point& point, const float& value)
{
    point.z = value;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, z)>::type setZ(T_Point& point, const float& value)
{
    point.z(value);
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, intensity) && !RS_HAS_MEMBER_FUNCTION(T_Point, intensity)>::type setIntensity(T_Point& point,
                                                                                      const uint8_t& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, intensity)>::type setIntensity(T_Point& point,
                                                                                     const uint8_t& value)
{
    point.intensity = value * 1e+3;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, intensity)>::type setIntensity(T_Point& point,
                                                                                     const uint8_t& value)
{
    point.intensity(value * 1e+3);
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, ring) && !RS_HAS_MEMBER_FUNCTION(T_Point, ring)>::type setRing(T_Point& point, const uint16_t& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, ring)>::type setRing(T_Point& point, const uint16_t& value)
{
    point.ring = value;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, ring)>::type setRing(T_Point& point, const uint16_t& value)
{
    point.ring(value);
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, stamp) && !RS_HAS_MEMBER_FUNCTION(T_Point, stamp)>::type setStamp(T_Point& point,
                                                                                      const double& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, stamp)>::type setStamp(T_Point& point,
                                                                                     const double& value)
{
    point.stamp = value;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, stamp)>::type setStamp(T_Point& point,
                                                                                     const double& value)
{
    point.stamp(value);
}


//Get
template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, x) && !RS_HAS_MEMBER_FUNCTION(T_Point, x)>::type getX(T_Point& point, float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, x)>::type getX(T_Point& point, float& value)
{
    value = point.x;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, x)>::type getX(T_Point& point, float& value)
{
    value = point.x();
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, y) && !RS_HAS_MEMBER_FUNCTION(T_Point, y)>::type getY(T_Point& point, float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, y)>::type getY(T_Point& point, float& value)
{
    value = point.y;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, y)>::type getY(T_Point& point, float& value)
{
    value = point.y();
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, z) && !RS_HAS_MEMBER_FUNCTION(T_Point, z)>::type getZ(T_Point& point, float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, z)>::type getZ(T_Point& point, float& value)
{
    value = point.z;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, z)>::type getZ(T_Point& point, float& value)
{
    value = point.z();
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, intensity) && !RS_HAS_MEMBER_FUNCTION(T_Point, intensity)>::type getIntensity(T_Point& point,
                                                                                      float& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, intensity)>::type getIntensity(T_Point& point,
                                                                                     float& value)
{
    value = point.intensity;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, intensity)>::type getIntensity(T_Point& point,
                                                                                     float& value)
{
    value = point.intensity();
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, ring) && !RS_HAS_MEMBER_FUNCTION(T_Point, ring)>::type getRing(T_Point& point, uint16_t& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, ring)>::type getRing(T_Point& point, uint16_t& value)
{
    value = point.ring;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, ring)>::type getRing(T_Point& point, uint16_t& value)
{
    value = point.ring();
}

template <typename T_Point>
inline typename std::enable_if<!RS_HAS_MEMBER(T_Point, stamp) && !RS_HAS_MEMBER_FUNCTION(T_Point, stamp)>::type getStamp(T_Point& point,
                                                                                      double& value)
{
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER(T_Point, stamp)>::type getStamp(T_Point& point,
                                                                                     double& value)
{
    value = point.stamp;
}

template <typename T_Point>
inline typename std::enable_if<RS_HAS_MEMBER_FUNCTION(T_Point, stamp)>::type getStamp(T_Point& point,
                                                                                     double& value)
{
    value = point.stamp();
}

}

#endif