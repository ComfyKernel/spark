#include "application/application.hpp"
#include "comfyscript/comfyscript.hpp"
#include "object/default_scripts.hpp"
#include "object/object.hpp"
#include "render/render.hpp"
#include "error/error.hpp"
#include "units/units.hpp"
#include "log/log.hpp"

#include <iostream>

class testscript : public script {
public:
  std::string _name = "testscript";

  const std::string& name() const { return _name; }
  
  void onStart() {
    std::cout<<"Script started!\n";
  }
};

class testapp : public application {
public:
  vao    vobject;
  
  shader fshad;
  shader vshad;

  shaderprogram prog;

  cfs::scriptrunner tscript;
  
  void onStart() {
    world.addChild(object("testobject"));

    testscript t;
    world.getChild("testobject").addScript(t);

    spriterenderer spr;
    world.getChild("testobject").addScript(spr);
    
    tscript.load("assets/scripts/thing.cfs");

    tscript.interpret();
    tscript.run();
    
    vobject.create();
    glBindVertexArray(vobject);

    fshad = shader("assets/shaders/basic.frag", SHADER_FRAGMENT);
    vshad = shader("assets/shaders/basic.vert", SHADER_VERTEX  );

    prog = shaderprogram{fshad, vshad};

    glUseProgram(prog);

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
