#ifndef H_DEFAULT_SCRIPTS_HPP
#define H_DEFAULT_SCRIPTS_HPP

#include "object.hpp"
#include "../render/shader.hpp"

class spriterenderer : public script {
protected:
  GLuint      _matid;
  std::string _name = "spriterenderer";
  
public:
  const shaderprogram& program;

  spriterenderer(const shaderprogram&);

  const std::string& name() const { return _name; }

  void onStart ();
  void onUpdate(float);
  void onDraw  (float);
  void onExit  ();
};

#endif
