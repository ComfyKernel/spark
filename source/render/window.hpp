#ifndef H_RENDER_WINDOW_SINGLE
#define H_RENDER_WINDOW_SINGLE

#include "../units/units.hpp"
#include "event.hpp"

#include <string>

class window {
private:
  struct _windowIMPL;
  _windowIMPL* _impl;
public:
  void setPosition(uint2d);
  void setSize    (uint2d);

  uint2d getPosition();
  uint2d getSize();

  window();
  window(uint2d,uint2d,std::string);
  window(unsigned int,unsigned int,
	 unsigned int,unsigned int,std::string);

  bool create(uint2d,uint2d,std::string);
  void destroy();

  event& pollEvents();

  bool makeCurrent();
  void swap();

  bool isOpen();
  void close ();

  void rename(std::string); };

#endif
