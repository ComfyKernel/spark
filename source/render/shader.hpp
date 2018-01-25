#ifndef H_RENDER_SHADER_HPP
#define H_RENDER_SHADER_HPP

#include "head.hpp"

#include <string>
#include <initializer_list>

enum shader_type {
  SHADER_VERTEX   = GL_VERTEX_SHADER,
  SHADER_FRAGMENT = GL_FRAGMENT_SHADER, };

class shader : public globject {
protected:
  shader_type _type;
public:
  shader();
  shader(std::string,shader_type);

  bool create(std::string,shader_type);
  void destroy();

  shader_type getType() const; };

// SHADER PROGRAM //

class shaderprogram : public globject {
public:
  shaderprogram();
  shaderprogram(std::initializer_list<shader>);

  bool create();
  void destroy();

  bool link_list(std::initializer_list<shader>);

  void attach(shader);

  bool link(); };

#endif
