#ifndef H_HEAD_RENDER_HPP
#define H_HEAD_RENDER_HPP

#define UNUSED(thing) do { (void)(thing); } while (0)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class globject {
protected:
  GLuint _glid;
public:
  operator GLuint();

  GLuint glid() const; };

#endif
