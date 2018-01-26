#include "object.hpp"

#include <algorithm>
#include <iostream>

object::object() { }

object::object(const std::string& n) : name(n) { }

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

void object::setParent(object& parent) {
  __parent = &parent;
}

void object::addChild(const object& o) {
  __children.push_back(o);
}

object& object::getChild(const std::string& n) {
  auto itr = find_if(__children.begin(),
		     __children.end(),
		     [&](const object& o) {
		       return o.name == n;
		     });

  if(itr != __children.end()) {
    auto dst = std::distance(__children.begin(), itr);

    return __children[dst];
  }

  std::cout<<"Couldn't find object '"<<n<<"'\n";
}

bool object::delChild(const std::string& n) {
  auto itr = find_if(__children.begin(),
		     __children.end(),
		     [&](const object& o) {
		       return o.name == n;
		     });

  if(itr != __children.end()) {
    __children.erase(itr);

    return true;
  }

  std::cout<<"Object not found '"<<n<<"'\n";
  return false;
}
