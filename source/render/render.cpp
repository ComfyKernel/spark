#include "render.hpp"

#include <iostream>
#include <fstream>

#include <exception>

#include <vector>

// GLOBJECT //

globject::operator GLuint() {
  return _glid;
}

GLuint globject::glid() const {
  return _glid;
}

// VAO //

vao::vao() {
  _glid=0;
}

void vao::create() {
  destroy();
  
  glCreateVertexArrays(1,&_glid);
}

void vao::destroy() {
  if(!_glid) return;

  glDeleteVertexArrays(1,&_glid);
  _glid=0;
}
