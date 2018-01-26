#include "render/render.hpp"
#include "error/error.hpp"
#include "units/units.hpp"
#include "log/log.hpp"

#include <iostream>

int main(int argc,char *argv[]) {
  try {
    window win;

    if(!win.create(uint2d(0,0),uint2d(1280,720),"Spark")) {
      std::cout<<"Failed to create window!\n";
      return -1;
    }
    
    vao vobject;
    vobject.create();
    glBindVertexArray(vobject);
  
    shader fshad("assets/shaders/test.frag",SHADER_FRAGMENT);
    shader vshad("assets/shaders/test.vert",SHADER_VERTEX  );
    
    shaderprogram prog{vshad , fshad};
    
    glUseProgram(prog);

    GLint u_tex = glGetUniformLocation(prog, "tex");

    glActiveTexture(GL_TEXTURE0);
    
    texture tex("assets/textures/measure_wall.png");
    
    buffer vbuff({ -1.f,-1.f,0.f,
	            1.f,-1.f,0.f,
	           -0.f, 1.f,0.f },BUFFER_VERTEX ,BUFFER_STATIC);
    
    buffer ibuff({ 0,1,2 },BUFFER_ELEMENT,BUFFER_STATIC);
    
    glEnableVertexAttribArray(0);
    
    while(win.isOpen()) {
      event& e=win.pollEvents();
      
      if(e.status) {
	std::cout<<"Key pressed '"<<e.key<<"'\n";
      }
      
      glClearColor(0,0,0,1);
      glClear(GL_COLOR_BUFFER_BIT);
      
      glVertexAttribPointer(0,3,GL_FLOAT,false,0,(void*)0);
      
      glUniform1i(u_tex, 0);
      
      glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);
      
      win.swap();
    }
    
    win.destroy();
    
    return 0;
  } catch(std::exception &e) {
    errorwindow ewin("Spark Error", std::string("[Error] : ") + e.what());
  }
}
