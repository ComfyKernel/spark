#ifndef H_APPLICATION_HPP
#define H_APPLICATION_HPP

#include "../render/window.hpp"
#include "../object/object.hpp"

#include <glm/mat4x4.hpp>

class application {
protected:
  bool _is_running = false;

  glm::mat4 _orthoMatrix;
public:
  window win;
  object world;

  glm::mat4 getOrtho() const;
  
  application();

  bool run (uint2d pos, uint2d size, const std::string& name);
  void quit();

  virtual void onStart  () { }
  virtual void onExit   () { }
  
  virtual void onUpdate (float delta) { }
  virtual void onDraw   (float delta) { }

  virtual void onResize (uint2d size) { }
};

#endif
