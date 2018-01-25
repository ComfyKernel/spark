#include "shader.hpp"
#include "head.hpp"

#include <iostream>
#include <fstream>
#include <vector>

// SHADER //

shader::shader() {
  _glid=0;
}

shader::shader(std::string name,shader_type type) {
  _glid=0;
  create(name,type);
}

bool shader::create(std::string name,shader_type type) {
  destroy();

  std::vector<char> data;

  std::ifstream file(name,std::ios::in);

  if(!file.is_open()) {
    std::cout<<"Failed to open file '"<<name<<"'\n";
  }

  char c;
  while(file.get(c)) {
    data.push_back(c);
  }

  int length=data.size();
  
  _glid=glCreateShader(type);

  const char* dat=&data[0];

  glShaderSource(_glid,1,&dat,&length);

  glCompileShader(_glid);

  GLint stat=0;
  glGetShaderiv(_glid,GL_COMPILE_STATUS,&stat);

  if(stat) return true;

  std::cout<<"Failed compiling shader '"<<name<<"'\n";
  GLint logLength=0;
  glGetShaderiv(_glid,GL_INFO_LOG_LENGTH,&logLength);

  GLchar* str=(GLchar*)operator new(logLength*sizeof(GLchar));
  glGetShaderInfoLog(_glid,logLength,NULL,str);

  std::cout<<"Reason:\n"<<str<<"\n";

  delete str;

  destroy();
  return false;
}

void shader::destroy() {
  if(!_glid) return;

  glDeleteShader(_glid);
  _glid=0;
}

shader_type shader::getType() const {
  return _type;
}

// SHADERPROGRAM //

shaderprogram::shaderprogram() {
  _glid = 0;
}

shaderprogram::shaderprogram(std::initializer_list<shader> shaders) {
  _glid = 0;
  create();
  link_list(shaders);
}

bool shaderprogram::create() {
  destroy();
  _glid = glCreateProgram();
  return true;
}

bool shaderprogram::link_list(std::initializer_list<shader> shaders) {
  for(auto i : shaders) {
    attach(i);
  }

  return link();
}

void shaderprogram::destroy() {
  if(!_glid) return;

  glDeleteProgram(_glid);
  _glid=0;
}

void shaderprogram::attach(shader shad) {
  glAttachShader(_glid,shad);
}

bool shaderprogram::link() {
  glLinkProgram(_glid);

  GLint status;
  glGetProgramiv(_glid,GL_LINK_STATUS,&status);

  if(status) return true;

  std::cout<<"Failed linking shader program!\n";

  GLint logLength=0;
  glGetProgramiv(_glid,GL_INFO_LOG_LENGTH,&logLength);

  GLchar* msg=(GLchar*)operator new((logLength+1)*sizeof(GLchar));
  glGetProgramInfoLog(_glid,logLength+1,NULL,msg);

  std::cout<<"Reason:\n"<<msg<<"\n";

  delete(msg);
  
  destroy();
  return false;
}
