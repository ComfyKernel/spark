#include "buffer.hpp"
#include "head.hpp"

#include <iostream>

buffer::buffer() {
  _glid=0;
}

buffer::buffer(void* data,size_t len,buffer_type type,buffer_draw_type drawtype) {
  _glid=0;
  create(data,len,type,drawtype);
}

void buffer::create(void* data,size_t len,buffer_type type,buffer_draw_type drawtype) {
  destroy();
  
  _type=type;
  _drawtype=drawtype;

  glGenBuffers(1,&_glid);

  glBindBuffer(_type,_glid);
  glBufferData(_type,len,data,_drawtype);
}

void buffer::destroy() {
  if(!_glid) return;
  
  glDeleteBuffers(1,&_glid);
  _glid=0;
}

void buffer::bind() const {
  glBindBuffer(_type,_glid);
}

buffer_type      buffer::getType    () const {
  return _type;
}

buffer_draw_type buffer::getDrawType() const {
  return _drawtype;
}
