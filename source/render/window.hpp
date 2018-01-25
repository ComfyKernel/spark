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
  void setPosition(const uint2d&);
  void setSize    (const uint2d&);

  const uint2d getPosition();
  const uint2d getSize();

  window();
  window(const uint2d&,
	 const uint2d&,
	 const std::string&);
  
  window(unsigned int,unsigned int,
	 unsigned int,unsigned int,
	 const std::string&);

  bool create(const uint2d&,
	      const uint2d&,
	      const std::string&);
  
  void destroy();

  event& pollEvents();

  bool makeCurrent();
  void swap();

  bool isOpen();
  void close ();

  void rename(const std::string&); };

#endif
