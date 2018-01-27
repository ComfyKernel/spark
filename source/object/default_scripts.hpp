#ifndef H_DEFAULT_SCRIPTS_HPP
#define H_DEFAULT_SCRIPTS_HPP

#include "object.hpp"

class meshfilter : public script {
public:
  std::string _name = "meshrenderer";

  const std::string& name() const { return _name; }

  void onStart() {

  }

  void onUpdate(float delta) {

  }

  void onDraw(float delta) {

  }

  void onExit() {

  }
}

#endif
