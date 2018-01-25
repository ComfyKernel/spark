#ifndef H_RENDER_BUFFER_HPP
#define H_RENDER_BUFFER_HPP

#include "head.hpp"

#include <initializer_list>
#include <stdexcept>
#include <typeinfo>

enum buffer_type {
  BUFFER_VERTEX       = GL_ARRAY_BUFFER         ,
  BUFFER_ELEMENT      = GL_ELEMENT_ARRAY_BUFFER ,
  BUFFER_PIXEL_PACK   = GL_PIXEL_PACK_BUFFER    ,
  BUFFER_PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER  , };

enum buffer_draw_type {
  BUFFER_STATIC  = GL_STATIC_DRAW  ,
  BUFFER_STREAM  = GL_STREAM_DRAW  ,
  BUFFER_DYNAMIC = GL_DYNAMIC_DRAW , };

class buffer : public globject {
protected:
  buffer_type _type;
  buffer_draw_type _drawtype;
public:
  buffer();
  buffer(void*,size_t,buffer_type,buffer_draw_type);
  
  template<typename T>
  buffer(std::initializer_list<T> l, buffer_type t,buffer_draw_type d) {
    create_with_list(l,t,d);
  }

  template<typename T>
  buffer(std::initializer_list<T> l) {
    buffer_type  t=BUFFER_VERTEX;

    if(typeid(t) == typeid(float()) ||
       typeid(t) == typeid(double())) {
      t = BUFFER_VERTEX;
    } else if(typeid(t) == typeid(int()) ||
	      typeid(t) == typeid(unsigned int()) ||
	      typeid(t) == typeid(short()) ||
	      typeid(t) == typeid(unsigned short()) ||
	      typeid(t) == typeid(long()) ||
	      typeid(t) == typeid(unsigned long)) {
      t = BUFFER_ELEMENT;
    } else {
      throw std::runtime_error("[RENDER] Cannot decide buffers type!");
      return;
    }
    
    create_with_list(l,t,BUFFER_STATIC);
  }

  template<typename T>
  void create_with_list(std::initializer_list<T> l,
			buffer_type t,buffer_draw_type d) {
    T* data = (T*)operator new(l.size() * sizeof(T));
 
    int cnt=0;
    for(auto i : l) {
      data[cnt] = i;
      cnt++;
    }

    create(data, (l.size() * sizeof(T)), t, d);

    delete(data);
  }

  void create(void*,size_t,buffer_type,buffer_draw_type);
  void destroy();

  void bind() const;

  buffer_type      getType    () const;
  buffer_draw_type getDrawType() const; };

#endif
