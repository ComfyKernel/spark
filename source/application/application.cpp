#include "application.hpp"

#include <iostream>
#include <exception>

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 application::getOrtho() const {
  return _orthoMatrix;
}

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

  _orthoMatrix = glm::ortho(0.f, float(size.x), 0.f, float(size.y), 0.f, 100.f);

  world.__app = this;
  std::cout<<"APP: "<<this<<"\n";
  
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
	std::cout<<"on script : "<<child_scripts[s]->name()
		 <<" : on child : "<<world_children[i].name<<"\n";
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
