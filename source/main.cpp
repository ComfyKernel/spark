#include "application/application.hpp"
#include "comfyscript/comfyscript.hpp"
#include "object/object.hpp"
#include "render/render.hpp"
#include "error/error.hpp"
#include "units/units.hpp"
#include "log/log.hpp"

#include <iostream>

class testapp : public application {
public:
  vao    vobject;
  
  shader fshad;
  shader vshad;

  shaderprogram prog;
  GLint uni_tex;

  texture tex;

  buffer vbuff;
  buffer ibuff;

  cfs::scriptrunner tscript;
  
  void onStart() {
    tscript.load("assets/scripts/thing.cfs");

    tscript.interpret();
    tscript.run();
    
    vobject.create();
    glBindVertexArray(vobject);

    fshad = shader("assets/shaders/test.frag", SHADER_FRAGMENT);
    vshad = shader("assets/shaders/test.vert", SHADER_VERTEX  );

    prog = shaderprogram{fshad, vshad};

    glUseProgram(prog);

    uni_tex = glGetUniformLocation(prog, "tex");

    glActiveTexture(GL_TEXTURE0);

    tex = texture("assets/textures/measure_wall.png");

    unsigned int indis[3] = {
      0, 1, 2
    };
    
    vbuff = buffer({
	  -1.f,-1.f,0.f,
	   1.f,-1.f,0.f,
	  -0.f, 1.f,0.f
	  }, BUFFER_VERTEX, BUFFER_STATIC);

    ibuff = buffer(indis, 3*sizeof(int), BUFFER_ELEMENT, BUFFER_STATIC);

    glEnableVertexAttribArray(0);
  }

  void onUpdate(float delta) {
    event& e = win.pollEvents();

    if(e.status) {
      std::cout<<"[Key Pressed] '"<<e.key<<"'\n";
    }
  }

  void onDraw(float delta) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER        , vbuff);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);

    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(uni_tex, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuff);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
    
    win.swap();
  }

  void onExit(float delta) {

  }
};

int main(int argc,char *argv[]) {
  try {
    testapp t;

    t.run(uint2d(0, 0), uint2d(1280, 720), "Test Application (Spark)");
    
  } catch(std::exception &e) {
    errorwindow ewin("Spark Error", std::string("[Error] : ") + e.what());
  }

  return 0;
}
