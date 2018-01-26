#ifndef H_OBJECT_HPP
#define H_OBJECT_HPP

#include "../units/units.hpp"

#include <string>

class object {
protected:
  float3d __pos;
  float3d __rot;
  float3d __siz;

  object* __parent;
  
public:
  std::string name;
  
  const float3d& position() const;
  const float3d& rotation() const;
  const float3d& scale   () const;

  object&  parent        ();
  
  object();
  object(std::string);

  void translate(const float3d&);
  void rotate   (const float3d&);
  void scale    (const float3d&);

  void setParent(object& parent);
};

#endif
