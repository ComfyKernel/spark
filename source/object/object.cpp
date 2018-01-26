#include "object.hpp"

object::object() { }

object::object(std::string n) : name(n) { }

const float3d& object::position() const { return __pos; }
const float3d& object::rotation() const { return __rot; }
const float3d& object::scale   () const { return __siz; }

object& object::parent() { return *__parent; }

void object::translate(const float3d& pos) {
  __pos += pos;
}

void object::rotate   (const float3d& rot) {
  __rot += rot;
}

void object::scale    (const float3d& siz) {
  __siz += siz;
}
