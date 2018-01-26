#include "application.hpp"

#include <iostream>
#include <exception>

application::application() {
  world.name = "world";
}

bool application::run(uint2d pos, uint2d size, const std::string& name) {
  if(_is_running) {
    throw std::runtime_error("Application already running! ABORT ABORT!");
    return false;
  }
  
  _is_running = true;

  if(!win.create(pos, size, name)) {
    throw std::runtime_error("Failed to create an application window!");
    return false;
  }

  onStart();

  while(win.isOpen() && _is_running) {
    onUpdate(0.f);

    onDraw  (0.f);
  }

  std::cout<<"Exiting\n";
  onExit();

  win.destroy();

  _is_running = false;

  return true;
}

void application::quit() {
  _is_running = false;
}
