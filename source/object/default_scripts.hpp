#ifndef H_DEFAULT_SCRIPTS_HPP
#define H_DEFAULT_SCRIPTS_HPP

#include "object.hpp"

class spriterenderer : public script {  
public:
  std::string _name = "spriterenderer";

  const std::string& name() const { return _name; }

  void onStart ();
  void onUpdate(float);
  void onDraw  (float);
  void onExit  ();
};

#endif
