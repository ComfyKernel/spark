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

  std::vector<object>& world_children = world.children();

  while(win.isOpen() && _is_running) {
    onUpdate(0.f);

    for(unsigned int i=0; i<world_children.size(); ++i) {
      std::vector<script*>& child_scripts = world_children[i].scripts();
      
      for(unsigned int s=0; s<child_scripts.size(); ++s) {
	child_scripts[s]->onUpdate(0.f);
      }
    }

    onDraw  (0.f);

    for(unsigned int i=0; i<world_children.size(); ++i) {
      std::vector<script*>& child_scripts = world_children[i].scripts();
      
      for(unsigned int s=0; s<child_scripts.size(); ++s) {
	child_scripts[s]->onDraw(0.f);
      }
    }

    win.swap();
  }

  for(unsigned int i=0; i<world_children.size(); ++i) {
    std::vector<script*>& child_scripts = world_children[i].scripts();
    
    for(unsigned int s=0; s<child_scripts.size(); ++s) {
      child_scripts[s]->onExit();
    }
  }
  
  onExit();

  win.destroy();

  _is_running = false;

  return true;
}

void application::quit() {
  _is_running = false;
}
