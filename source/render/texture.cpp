#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>
#include <exception>

texture::texture() { }
texture::texture(const std::string& path) {
  load(path);
}

bool texture::create() {
  destroy();

  glGenTextures(1, &_glid);
}

bool texture::load(const std::string& path) {
  create();

  int w,h,d;

  unsigned char* data = stbi_load(path.c_str(),
				  &w, &h, &d,
				  STBI_rgb_alpha);

  if(data == nullptr) {
    throw std::runtime_error(std::string("Failed to load image '")+
			     path+std::string("'"));
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, _glid);

  glTexImage2D(GL_TEXTURE_2D, 0,
	       GL_RGBA8,
	       w, h, 0,
	       GL_RGBA,
	       GL_UNSIGNED_BYTE,
	       data);
  
  stbi_image_free(data);

  return true;
}

void texture::destroy() {
  if(!_glid) return;

  glDeleteTextures(1, &_glid);
  _glid = 0;
}
