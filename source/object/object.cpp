#include "object.hpp"
#include "../application/application.hpp"

#include <algorithm>
#include <iostream>
#include <exception>

object::object() { }

object::object(const std::string& n) : name(n) { }

object& object::parent() { return *__parent; }

void object::setParent(object* parent) {
  __parent = parent;
}

#define MAC_FITR(type,vecname,nvar)   \
  find_if(vecname.begin(),            \
          vecname.end(),	      \
          [&](const type& t) {        \
            return t.name == nvar;    \
          });

#define MAC_SITR(type,vecname,nvar)   \
  find_if(vecname.begin(),            \
          vecname.end(),	      \
          [&](const type* t) {        \
	    return t->name() == nvar; \
          });

void object::addChild(const object& o) {
  __children.push_back(o);
  
  object& child = __children[__children.size() - 1];
  child.setParent(this);
  child.__app = __app;
  child.__initialized = true;

  std::vector<script*>& scripts = child.scripts();
  for(unsigned int i=0; i<scripts.size(); ++i) {
    scripts[i]->parent = &child;
    scripts[i]->onStart();
  }
}

object& object::getChild(const std::string& n) {
  auto itr = MAC_FITR(object, __children, n);

  if(itr != __children.end()) {
    auto dst = std::distance(__children.begin(), itr);

    return __children[dst];
  }

  std::cout<<"Couldn't find object '"<<n<<"'\n";
}

bool object::delChild(const std::string& n) {
  auto itr = MAC_FITR(object, __children, n);

  if(itr != __children.end()) {
    __children.erase(itr);

    return true;
  }

  std::cout<<"Object not found '"<<n<<"'\n";
  return false;
}

void object::__addScript(script* scr) {
  std::cout<<"Adding script '"<<scr->name()<<"'\n";
  __scripts.push_back(scr);

  if(__app == nullptr) {
    throw std::runtime_error("APP Is not allowed to be NULL!");
    return;
  }

  if(__initialized) {    
    __scripts[__scripts.size() - 1]->parent = this;
    __scripts[__scripts.size() - 1]->onStart();

    if(__scripts[__scripts.size() - 1]->parent->app() == nullptr) {
      throw std::runtime_error("App is not allowed to be null!");
      return;
    }
  }
}

script* object::getScript(const std::string& n) {
  auto itr = MAC_SITR(script, __scripts, n);

  if(itr != __scripts.end()) {
    auto dst = std::distance(__scripts.begin(), itr);

    return __scripts[dst];
  }

  std::cout<<"Couldn't find script '"<<n<<"'\n";
}

bool object::delScript(const std::string& n) {
  auto itr = MAC_SITR(script, __scripts, n);

  if(itr != __scripts.end()) {
    __scripts[std::distance(__scripts.begin(),itr)]->onExit();
    delete __scripts[std::distance(__scripts.begin(), itr)];
    __scripts.erase(itr);

    return true;
  }

  std::cout<<"Script not found '"<<n<<"'\n";
  return false;
}

std::vector<object>&  object::children() { return __children; }
std::vector<script*>& object::scripts () { return __scripts;  }

application* object::app() { return __app; }

script::script() { }
