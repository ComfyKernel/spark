#ifndef H_SPRITEBATCH_HPP
#define H_SPRITEBATCH_HPP

#include "../../units/units.hpp"

namespace sprite {
  
  
  void start();
  void end  ();

  void draw(const int2d&   pos,
	    const int2d&  size,
	    const texture& tex);
  
  void draw(const int2d& tpos ,
	    const int2d& tsize,
	    const int2d& pos  ,
	    const int2d& size ,
	    const texture& tex);
};

#endif
