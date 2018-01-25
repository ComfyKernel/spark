#ifndef H_TEXTURE_HPP
#define H_TEXTURE_HPP

#include "head.hpp"
#include <string>

class texture : public globject {
public:
  texture();
  texture(const std::string&);

  bool create();
  
  bool load(const std::string&);
  void destroy();
};

#endif
